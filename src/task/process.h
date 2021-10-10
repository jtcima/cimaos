#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "config.h"
#include "task.h"
struct process
{
    uint16_t id; //process id
    char filename[CIMAOS_MAX_PATH];

    struct task* task; //the main process task
    void* allocations[CIMAOS_MAX_PROGRAMS_MEMORY_ALLOCATIONS]; //the memory malloc allocations of the process

    void* ptr; //the physical pointer to the process memory

    void* stack; //the physical pointer to the stack memory

    uint32_t size; //the size of the data pointed to by 'ptr'
};

int process_load_for_slot(const char* filename, struct process** process, int process_slot);
int process_load(const char* filename, struct process** process);


#endif