#ifndef CIMAOS_H
#define CIMAOS_H
#include <stddef.h>
#include <stdbool.h>

void print(const char* message);
int cimaos_getkey();

void* cimaos_malloc(size_t size);
void cimaos_free(void* ptr);
void cimaos_putchar(char c);
int cimaos_getkeyblock();
void cimaos_terminal_readline(char* out, int max, bool output_while_typing);
void cimaos_process_load_start(const char* filename);

#endif