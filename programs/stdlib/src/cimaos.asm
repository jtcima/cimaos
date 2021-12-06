[BITS 32]

section .asm

global print:function
global cimaos_getkey:function
global cimaos_malloc:function
global cimaos_free:function
global cimaos_putchar:function
global cimaos_process_load_start:function
print:
    push ebp
    mov ebp, esp
    push dword[ebp+8] 
    mov eax, 1; command print
    int 0x80
    add esp, 4
    pop ebp
    ret

cimaos_getkey:
    push ebp
    mov ebp, esp
    mov eax, 2; command getkey
    int 0x80
    pop ebp
    ret

;void putchar(char c)
cimaos_putchar:
    push ebp
    mov ebp, esp
    mov eax, 3 ;command putchar
    push dword [ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

; void* cimaos_malloc(size_t size)
cimaos_malloc:
    push ebp
    mov ebp, esp
    mov eax, 4 ;command malloc
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

; void cimaos_free(void* ptr)
cimaos_free:
    push ebp
    mov ebp, esp
    mov eax, 5 ; command free
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

;void cimaos_process_load_start(const char* filename)
cimaos_process_load_start:
    push ebp
    mov ebp, esp
    mov eax, 6 ; command 6 process load start
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret