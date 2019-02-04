#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>

struct LargeNumber
{
    int byteNum;
    unsigned char *number;
};

struct LargeNumber initLargeNumber(int bytenum)
{
    struct LargeNumber largenumber = (struct LargeNumber){
        bytenum,
        malloc(sizeof(char) * bytenum)};

    return largenumber;
}

void assignValue(char *number)
{
}

int main()
{
    struct LargeNumber num = initLargeNumber(8);
    printf("%c", num.number[0]);
    return 0;
}