
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


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
    int n;
    puts("enter: ");
    scanf("%d", &n);
    int arra[n];
    for(int i = 0; i < n; i++)
    {
        arra[i] = i;
        printf("%d\n", arra[i]);
    }
    //printf("%u", sizeof(struct registers));
    
}