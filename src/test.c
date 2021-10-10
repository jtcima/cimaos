
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
extern void tss_load(int a);
char* func(char* dest, const char* src)
{
    
    char** res = &dest;
    printf("%p %p", res, dest);
    while(*src != 0)
    {
        *dest = *src;   
        src += 1;
        dest += 1;
    }

    return *res;
}

struct test
{
    uint32_t a;
    uint8_t b;
};

struct complete
{
    uint32_t c;
};

struct registers
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    uint32_t ip;
    uint32_t cs;
    uint32_t flags;
    uint32_t esp;
    uint32_t ss;
};
void print_print(int a)
{
    int b = 10;
    int c = 80;
    
    if(a)
    {
        printf("worked\n");
    }
}

int main()
{
/*
    int a =1;
    int* pa = &a;
    int** ppa = &pa;
    printf("%p %p %p %p %p\n", &a, pa, &pa, ppa, &ppa);
    
    char *array = "hello";
    char* p = array;
    char** ptr = &array;
    printf("%p\n", array);
    printf("%p\n", p);*/
    /*void changeptr(char** y)
    {
        printf("%p\n", *y);
        *y+=2;
        printf("%p\n", *y);      
    }*/
/*
    changeptr(ptr);
    printf("%s", array);*/
/*
    int a = 1;
    char b[] = "dfsdssddfd";
    char* p = "hello";
    char**p1= &p;
    char ptr[20];
    func(ptr, p);
    printf("%s", p1);
 */

    printf("%u", sizeof(struct registers));
    
}