#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "string/string.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
#include "fs/file.h"


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

void kernel_main()
{
    
    terminal_initialize();
    print("Hello World\ntest\n");
    
    //initialize the heap
    kheap_init();

    //initialize file systems
    fs_init();
    
    //search and initialize the disks
    disk_search_init();

    //initialize idt
    idt_init();
    
    //set up paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    //swtich to paging kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    
    //enable paging
    enable_paging();
    

    //enable the system interrupt
    enable_interrupts();
/*
    struct disk_stream* stream = diskstreamer_new(0);
    diskstreamer_seek(stream, 0x201);
    unsigned char c = 0;
    diskstreamer_read(stream, &c, 1);  
*/  
    int fd = fopen("0:/hello.txt", "r");
    if(fd)
    {
        print("we opened\n");
    }
    while(1){}


}