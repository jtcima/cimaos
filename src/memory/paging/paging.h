#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define PAGING_CACHE_DISABLED   0b00010000
#define PAGING_WRITE_THROUGH    0b00001000
#define PAGING_ACCESS_FROM_ALL  0b00000100 //both user and supervisor can access the page
#define PAGING_IS_WRITABLE      0b00000010
#define PAGING_IS_PRESENT       0b00000001

#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024
#define PAGING_PAGE_SIZE 4096

struct paging_4gb_chunk
{
    uint32_t* directory_entry;

};

uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk);
struct paging_4gb_chunk* paging_new_4gb(uint8_t flags);
void paging_switch(struct paging_4gb_chunk* directory);
void enable_paging();
bool paging_is_aligned(void* addr);
int paging_set(uint32_t* directory, void* virt_addr, uint32_t val);
void paging_free_4gb(struct paging_4gb_chunk* chunk);
int paging_map_to(struct paging_4gb_chunk* directory, void* virt, void* phys_addr, void* phys_addr_end, int flag);
int paging_map_range(struct paging_4gb_chunk* directory, void* virt, void* phys, int count, int flags);
int paging_map(struct paging_4gb_chunk* directory, void* virt, void* phys, int flags);
void* paging_align_address(void* ptr);
uint32_t paging_get(uint32_t* directory, void* virt);

#endif