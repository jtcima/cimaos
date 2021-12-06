#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "cimaos.h"

int main(int argc, char** argv)
{
    print("CIMAOS v1.0.0\n");
    while(1)
    {
        print("> ");
        char buf[1024];
        cimaos_terminal_readline(buf, sizeof(buf), true);
        cimaos_process_load_start(buf);
        print("\n");
    }
    
    return 0;
}