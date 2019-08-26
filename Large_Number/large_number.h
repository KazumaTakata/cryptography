#ifndef HLARGENUM
#define HLARGENUM

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>

typedef struct LargeNumber
{
    int byteNum;
    unsigned char *number;
} LargeNumber;

void assignValue(char *number, LargeNumber largenumber);
char hex2int(char ch);
void initWithZero(LargeNumber *largenumber);

struct LargeNumber initLargeNumber(int bytenum)
{
    struct LargeNumber largenumber = (struct LargeNumber){
        bytenum,
        (unsigned char *)malloc(bytenum * sizeof(char))};
    return largenumber;
}

void assignValue(char *number, LargeNumber largenumber)
{
    initWithZero(&largenumber);
    for (int i = 0; i < strlen(number); i++)
    {
        char hex = number[strlen(number) - i - 1];
        int hexValue = hex2int(hex);
        int index = i / 2;
        int upper = (i % 2) * 4;
        largenumber.number[index] += hexValue << upper;
    }
}

struct LargeNumber initLargeNumberWithValue(char *number)
{
    int bytenum = (strlen(number) + 1) / 2;
    LargeNumber largenumber = initLargeNumber(bytenum);

    assignValue(number, largenumber);
    return largenumber;
}

void initWithZero(LargeNumber *largenumber)
{
    memset(largenumber->number, 0, largenumber->byteNum * sizeof(char));
}

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

void printLargeNumber(LargeNumber *largenumber)
{
    for (int i = 0; i < largenumber->byteNum; i++)
    {
        print_byte_as_bits(largenumber->number[largenumber->byteNum - i - 1]);
    }
}

#endif