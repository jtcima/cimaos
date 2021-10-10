[BITS 32]
global _start
global kernel_registers
extern kernel_main

CODE_SEL equ 0x08
DATA_SEL equ 0x10

_start:
    mov ax, DATA_SEL
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ;enable the A20 line
    in al, 0x92
    or al, 2
    out 0x92, al

    ;remap the master PIC
    mov al, 00010001b ;put PIC in initialization mode
    out 0x20, al ;tell mater PIC
    
    mov al, 0x20 ; interrupt 0x20 is where master ISR should start
    out 0x21, al

    mov al, 00000001b
    out 0x21, al
    ;end of remap master PIC

    call kernel_main
    jmp $

kernel_registers:
    mov ax, 10
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
    ret


times 512- ($ - $$) db 0