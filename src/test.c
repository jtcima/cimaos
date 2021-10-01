
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

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

    int a = 1;
    char b[] = "dfsdssddfd";
    char* p = "hello";
    char**p1= &p;
    char ptr[20];
    func(ptr, p);
    printf("%s", p1);
    
    

    
    
}