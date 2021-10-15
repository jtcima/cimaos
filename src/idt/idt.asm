section .asm

extern int21h_handler
extern no_interrupt_handler
extern isr80h_handler
global int21h
global idt_load
global no_interrupt
global enable_interrupts
global disable_interrupts
global isr80h_wrapper

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]

    pop ebp
    ret


int21h:
    pushad
    call int21h_handler
    popad
    iret

no_interrupt:
    pushad
    call no_interrupt_handler
    popad
    iret

isr80h_wrapper:
    ;interrupt frame_start
    ;the below registers are already pushed to us by the processor upon entry the interrupt
    ;uint32_t ip
    ;uint32_t cs
    ;uint32_t flags
    ;uint32_t sp
    ;uinte32_t ss
    ;pushes the general pirpose registers to the stack
    pushad

    ;interrupt fram end

    ;push the stack pointer so that we can access to the interrupt frame later
    push esp
    ; eax holds the command and push it to the stack for isr80_h handler
    push eax
    call isr80h_handler
    mov dword[tmp_res], eax
    add esp, 8

    ;restore general purpose registers for user land
    popad

    mov eax, [tmp_res]
    iretd

section .data
;inside here is stored the return result from isr80h_handler
tmp_res: dd 0


