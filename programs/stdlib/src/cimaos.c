#include "cimaos.h"

int cimaos_getkeyblock()
{
    int val = 0;
    
    do
    {
        val = cimaos_getkey();
    } while(val == 0);
    return val;
}

void cimaos_terminal_readline(char* out, int max, bool output_while_typing)
{
    int i = 0;
    for (i = 0; i < max - 1; i++)
    {
        char key = cimaos_getkeyblock();
        //carriage return means we have read the line
        if (key == 13)
        {
            break;
        }

        if(output_while_typing)
        {
            cimaos_putchar(key);
        }

        //backspace
        if (key == 0x08 && i >=1)
        {
            out[i-1] = 0x00;
            //-2 because we will +1 when we go to the continue
            i -=2;
            continue;
        }

        out[i] = key;
    }

    //add the null terminator
    out[i] = 0x00;
}