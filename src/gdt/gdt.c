#include "gdt.h"
#include "kernel.h"


void encodeGdtEntry(uint8_t* target, struct gdt_structured source)
{
    if ((source.limit > 65536) && ((source.limit & 0xFFF) != 0xFFF))
    {
        panic("encodeGdtEntry: Invalid argument\n");
    } 

    target[6] = 0x40;
    if(source.limit > 65536)
    {
        source.limit = source.limit >> 12;
        target[6] = 0xC0;
    }
    //encodes the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] |= (source.limit >> 16) & 0x0F;

    //encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >>8) & 0XFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    target[5] = source.type;
}

void gdt_structured_to_gdt(struct gdt_entry* gdt, struct gdt_structured* structured_gdt, int total_entries)
{
    for (int i = 0; i < total_entries; i++)
    {
        encodeGdtEntry((uint8_t*)&gdt[i], structured_gdt[i]);
    }
}

/*
 29. Segment Registers in Protected Mode

Segment registers are called selectors when operating in protected mode.

In protected mode, segment registers simply point to data structures called segment descriptors 
that contain the information needed to access a physical memory location. 
*/