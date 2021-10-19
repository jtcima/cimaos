#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10
#define USER_DATA_SEGMENT 0x23
#define USER_CODE_SEGMENT 0x1b
#define CIMAOS_TOTAL_INTERRUPTS 512
#define CIMAOS_HEAP_SIZE_BYTES 104857600 //100MB heap size
#define CIMAOS_HEAP_BLOCK_SIZE 4096
#define CIMAOS_HEAP_ADDRESS 0x01000000
#define CIMAOS_HEAP_TABLE_ADDRESS 0x00007E00

#define CIMAOS_SECTOR_SIZE 512

#define CIMAOS_MAX_FILESYSTEMS 12
#define CIMAOS_MAX_FILE_DESCRIPTORS 512

#define CIMAOS_MAX_PATH 108

#define CIMAOS_TOTAL_GDT_SEGMENTS 6

#define CIMAOS_PROGRAM_VIRTUAL_ADDRESS 0x400000

#define CIMAOS_USER_PROGRAM_STACK_SIZE 1024 * 16
#define CIMAOS_PROGRAM_VIRTUAL_STACK_ADDRESS_START 0x3FF000
#define CIMAOS_PROGRAM_VIRTUAL_STACK_ADDRESS_END CIMAOS_PROGRAM_VIRTUAL_STACK_ADDRESS_START - CIMAOS_USER_PROGRAM_STACK_SIZE

#define CIMAOS_MAX_PROGRAMS_MEMORY_ALLOCATIONS 1024

#define CIMAOS_MAX_PROCESSES 12

#define CIMAOS_MAX_ISR80H_COMMANDS 1024

#define CIMAOS_KEYBOARD_BUFFER_SIZE 1024


#endif