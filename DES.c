#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
void printBits(size_t const size, void const *const ptr);
void readFileData(int *array, char *filename);
int circlerBit(int c);

int main()
{

    // char sample[] = "fe";
    // for (int i = 0; i < strlen(sample); i++)
    // {
    //     sample[i] = sample[i] << 2;
    //     printf("%02x ", (unsigned char)sample[i]);
    // }
    // printf("\n");
    int64_t source = 0b0001001100110100010101110111100110011011101111001101111111110001;
    int64_t ans = 0b0000000011110000110011001010101011110101010101100110011110001111;
    int mask = 0b00001111111111111111111111111111;
    // int64_t source = 0b1101000000100111110001001111100010101000101011011101111010111001;
    // int64_t e = (int64_t)1 << 63;
    // if (source & e)
    // {
    //     printf("1");
    // }

    int array[56] = {0};

    // readFileData(array, "pc-1.txt");

    // int64_t result = 0;
    // for (int i = 0; i < 56; i++)
    // {
    //     result <<= 1;
    //     if (source & ((int64_t)1 << (64 - array[i])))
    //     {
    //         printf("1");
    //         result |= 1;
    //     }
    //     else
    //     {
    //         printf("0");
    //     }
    // }
    // assert(ans == result);
    // printBits(sizeof(result), &result);

    int d0 = (int)ans & mask;
    int c0 = (int)(ans >> 28) & mask;
    printBits(sizeof(c0), &c0);
    printBits(sizeof(d0), &d0);

    int c1 = circlerBit(c0);
    printBits(sizeof(c1), &c1);

    int d1 = circlerBit(d0);
    printBits(sizeof(d1), &d1);
}

int circlerBit(int c)
{
    int mask = 0b00001111111111111111111111111111;
    int c1;
    if (c & (1 << 27))
    {
        c1 = ((c << 1) & mask) | 1;
    }
    else
    {
        c1 = ((c << 1) & mask);
    }
    return c1;
}

void readFileData(int *array, char *filename)
{
    FILE *fo;
    fo = fopen(filename, "rb");
    char c;
    char c1 = '0';
    char c10 = '0';
    int index = 0;

    while ((c = getc(fo)) != EOF)
    {
        if (isdigit(c))
        {
            c10 = c1;
            c1 = c;
        }
        else
        {
            if (c1 != '0' || c10 != '0')
            {
                int d = c1 - '0' + 10 * (c10 - '0');
                array[index] = d;
                index++;
                c1 = '0';
                c10 = '0';
            }
        }
    }
    int d = c1 - '0' + 10 * (c10 - '0');
    array[index] = d;
    fclose(fo);
}

void printBits(size_t const size, void const *const ptr)
{
    unsigned char *b = (unsigned char *)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}