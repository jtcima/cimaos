#ifndef DISK_H
#define DISK_H

#include "fs/file.h"

typedef unsigned int CIMAOS_DISK_TYPE;

//represents a real physical hard disk
#define CIMAOS_DISK_TYPE_REAL 0

struct disk
{
    CIMAOS_DISK_TYPE type;
    int sector_size;

    //id of the disk
    int id;

    struct filesystem* filesystem;

    // the private data of our filesystem
    void* fs_private;
};


void disk_search_init();
struct disk* disk_get(int index);
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf);

#endif