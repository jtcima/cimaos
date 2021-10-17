#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/memory.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "string/string.h"
#include "task/task.h"
#include "task/process.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
#include "fs/file.h"
#include "gdt/gdt.h"
#include "config.h"
#include "task/tss.h"
#include "status.h"
#include "isr80h/isr80h.h"
#include "keyboard/keyboard.h"


uint16_t* video_mem = 0; 
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char color)
{
    return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, char color)
{
    video_mem[(y*VGA_WIDTH) + x] = terminal_make_char(c, color);
}

void terminal_writechar(char c, char color)
{
    if(c == '\n')
    {
        terminal_col = 0;
        terminal_row += 1; 
        return;      
    }
    terminal_putchar(terminal_col, terminal_row, c, color);
    terminal_col += 1;
    if(terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }

}

void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    for(int y = 0; y < VGA_HEIGHT; y++)
    {
        for(int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        terminal_writechar(str[i], 15);
    }
}

static struct paging_4gb_chunk* kernel_chunk = 0;

void panic(const char* msg)
{
    print(msg);
    while(1) {}
}

void kernel_page()
{
    kernel_registers();
    paging_switch(kernel_chunk);
}

struct tss tss;
struct gdt_entry gdt_real[CIMAOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[CIMAOS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},  //null segemnt
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a}, //kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92}, //kernel data segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8}, //user code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2}, //user data segment
    {.base = (uint32_t)&tss, .limit = sizeof(tss), .type = 0xE9} //TSS segment

};


void kernel_main()
{
    
    terminal_initialize();

    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, CIMAOS_TOTAL_GDT_SEGMENTS);
    //load the gdt
    gdt_load(gdt_real, sizeof(gdt_real));

    //initialize the heap
    kheap_init();

    //initialize file systems
    fs_init();
    
    //search and initialize the disks
    disk_search_init();

    //initialize idt
    idt_init();
    
    //setup the tss
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;

    //load the tss
    tss_load(0x28);

    //set up paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    //swtich to paging kernel paging chunk
    paging_switch(kernel_chunk);

    
    //enable paging
    enable_paging();

    //register the kernel commands
    isr80h_register_commands();

    keyboard_init(); //initialize system keyboard
    struct process* process = 0;
    int res = process_load("0:/blank.bin", &process);
    if (res != CIMAOS_ALL_OK)
    {
        panic("failed to load blank.bin\n");
    }

    task_run_first_ever_task();

    //enable the system interrupt
    //enable_interrupts();
/*
    struct disk_stream* stream = diskstreamer_new(0);
    diskstreamer_seek(stream, 0x201);
    unsigned char c = 0;
    diskstreamer_read(stream, &c, 1);  
*/
/*  
    int fd = fopen("0:/hello.txt", "r");
    if(fd)
    {
        struct file_stat s;
        fstat(fd, &s);
        fclose(fd);

        print("closed\n");

    }
*/
    while(1){}


}