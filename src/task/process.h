#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "config.h"
#include "task.h"

#define PROCESS_FILETYPE_ELF 0
#define PROCESS_FILETYPE_BINARY 1

typedef unsigned char PROCESS_FILETYPE;
struct process
{
    uint16_t id; //process id
    char filename[CIMAOS_MAX_PATH];

    struct task* task; //the main process task
    void* allocations[CIMAOS_MAX_PROGRAMS_MEMORY_ALLOCATIONS]; //the memory malloc allocations of the process

    PROCESS_FILETYPE filetype;

    union 
    {
        void* ptr; //the physical pointer to the process memory
        struct elf_file* elf_file;
    }; 

    void* stack; //the physical pointer to the stack memory

    uint32_t size; //the size of the data pointed to by 'ptr'

    struct keyboard_buffer
    {
        char buffer[CIMAOS_KEYBOARD_BUFFER_SIZE];
        int tail;
        int head;
    }keyboard;
};

int process_load_for_slot(const char* filename, struct process** process, int process_slot);
int process_load(const char* filename, struct process** process);
struct process* process_current();
int process_load_switch(const char* filename, struct process** process);
int process_switch(struct process* process);

#endif