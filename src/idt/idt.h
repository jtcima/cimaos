#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_desc
{
    uint16_t offset_1; //offset bits 0 - 15 (interrupt address lower 16 bits)
    uint16_t selector; //selectors in our gdt
    uint8_t zero; //does nothing, set to zero
    uint8_t type_attr; //Descriptor type and attribute
    uint16_t offset_2; //offset bits 16-31 (interrupt address higher 16 bits)

}__attribute__((packed));

struct idtr_desc //a structure point to our idt
{
    uint16_t limit; //size of discriptor table -1
    uint32_t base; //base address of the start of the idt
}__attribute__((packed));

void idt_init();
void enable_interrupts();
void disable_interrupts();


#endif
