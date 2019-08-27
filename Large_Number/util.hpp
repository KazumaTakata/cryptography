#ifndef HUTIL
#define HUTIL

#include "stdio.h"

void print_byte_as_bits(char val)
{
    for (int i = 7; 0 <= i; i--)
    {
        printf("%c", (val & (1 << i)) ? '1' : '0');
    }
}

char hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

#endif