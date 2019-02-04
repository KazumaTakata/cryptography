#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
void printBits(size_t const size, void const *const ptr);
void readFileData(int *array, char *filename);
int circlerBit(int c);
int64_t combineInt(int c, int d);
int64_t bitPermutation64bit(char *filename, int64_t message, int inDim, int outDim);
struct keyAndSeed keyGeneration(int64_t seed, int shift_time);
void fillWithKey(struct keyAndSeed *keyandseed, int64_t seed);
char sbox(int64_t k0_e_r0, int index);
int sboxes(int64_t k0_e_r0);
int bitPermutation32bit(char *filename, int message, int inDim, int outDim);
struct RandL DesRound(struct RandL *randl, int64_t key);

struct keyAndSeed
{
    int64_t key;
    int64_t seed;
};

struct RandL
{
    int r;
    int l;
};

int main()
{
    int64_t message = 0b0000000100100011010001010110011110001001101010111100110111101111;
    int64_t source = 0b0001001100110100010101110111100110011011101111001101111111110001;
    int64_t ans = 0b0000000011110000110011001010101011110101010101100110011110001111;
    int64_t key1_ans = 0b000110110000001011101111111111000111000001110010;
    int64_t key2_ans = 0b011110011010111011011001110110111100100111100101;
    int64_t ip_ans = 0b1100110000000000110011001111111111110000101010101111000010101010;
    int64_t e_r0_ans = 0b011110100001010101010101011110100001010101010101;
    int64_t k0_e_r0_ans = 0b011000010001011110111010100001100110010100100111;

    int mask = 0b00001111111111111111111111111111;

    char *filename = "pc-1.txt";

    int64_t ans1 = bitPermutation64bit(filename, source, 64, 56);
    assert(ans == ans1);

    struct keyAndSeed keyandseeds[16];
    fillWithKey(keyandseeds, ans1);
    assert(keyandseeds[0].key == key1_ans);

    filename = "ip.txt";
    int64_t ipmessage = bitPermutation64bit(filename, message, 64, 64);

    assert(ipmessage == ip_ans);

    int r0 = ipmessage;
    int l0 = ipmessage >> 32;
    int l1 = r0;

    struct RandL randl = {r0, l0};

    for (int i = 0; i < 16; i++)
    {
        randl = DesRound(&randl, keyandseeds[i].key);
    }

    int64_t rl16 = ((int64_t)randl.r << 32) + randl.l;

    filename = "ip-1.txt";

    int64_t ip_1 = bitPermutation64bit(filename, rl16, 64, 64);

    printBits(sizeof(ip_1), &ip_1);
}

struct RandL DesRound(struct RandL *randl, int64_t key)
{
    int r0 = randl->r;
    int l0 = randl->l;
    int l1 = r0;

    char *filename = "e-bit.txt";

    int64_t e_r0 = bitPermutation64bit(filename, r0, 32, 48);

    int64_t k0_e_r0 = key ^ e_r0;

    int tmp = sboxes(k0_e_r0);

    filename = "p.txt";
    int f = bitPermutation32bit(filename, tmp, 32, 32);

    int r1 = f ^ l0;

    struct RandL ans = {r1, l1};

    return ans;
}

int sboxes(int64_t k0_e_r0)
{
    int result = 0;
    for (int i = 1; i < 9; i++)
    {
        int tmp = sbox(k0_e_r0, i);
        result += tmp << (4 * (8 - i));
    }

    return result;
}

char sbox(int64_t k0_e_r0, int index)
{
    int bits[6] = {0};
    for (int i = 0; i < 6; i++)
    {
        int64_t mask = (int64_t)1 << ((8 - index) * 6 + 5 - i);
        if (mask & k0_e_r0)
        {
            bits[i] = 1;
        }
        else
        {
            bits[i] = 0;
        }
    }
    int row = 2 * bits[0] + bits[5];
    int col = 8 * bits[1] + 4 * bits[2] + bits[3] * 2 + bits[4];

    char filename[10];
    sprintf(filename, "s%d.txt", index);

    int Array[64] = {0};
    readFileData(Array, filename);
    char ele = Array[row * 16 + col];

    return ele;
}

void fillWithKey(struct keyAndSeed *keyandseed, int64_t seed)
{

    int shiftarray[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    for (int i = 0; i < 16; i++)
    {
        struct keyAndSeed key = keyGeneration(seed, shiftarray[i]);
        keyandseed[i] = key;
        seed = key.seed;
    }
}

struct keyAndSeed keyGeneration(int64_t seed, int shift_time)
{
    int mask = 0b00001111111111111111111111111111;
    int d0 = (int)seed & mask;
    int c0 = (int)(seed >> 28) & mask;

    int c1 = c0;
    int d1 = d0;
    for (int i = 0; i < shift_time; i++)
    {
        c1 = circlerBit(c1);
        d1 = circlerBit(d1);
    }

    int64_t c1d1 = combineInt(c1, d1);

    char *filename = "pc-2.txt";

    int64_t key = bitPermutation64bit(filename, c1d1, 56, 48);
    struct keyAndSeed keyandseed = {key, c1d1};

    return keyandseed;
}

int64_t
bitPermutation64bit(char *filename, int64_t message, int inDim, int outDim)
{

    int *bitpermArray = malloc(sizeof(int) * outDim);
    readFileData(bitpermArray, filename);

    int64_t result = 0;
    for (int i = 0; i < outDim; i++)
    {
        result <<= 1;
        if (message & ((int64_t)1 << (inDim - bitpermArray[i])))
        {
            result |= 1;
        }
    }

    free(bitpermArray);

    return result;
}

int bitPermutation32bit(char *filename, int message, int inDim, int outDim)
{

    int *bitpermArray = malloc(sizeof(int) * outDim);
    readFileData(bitpermArray, filename);

    int64_t result = 0;
    for (int i = 0; i < outDim; i++)
    {
        result <<= 1;
        if (message & (1 << (inDim - bitpermArray[i])))
        {
            result |= 1;
        }
    }

    free(bitpermArray);

    return result;
}

int64_t combineInt(int c, int d)
{
    int64_t result = (int64_t)c << 28;
    result += d;

    return result;
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
            if (c == '0' && c1 == '0')
            {
                array[index] = 0;
                index++;
                c1 = '0';
                c10 = '0';
            }
            else
            {
                c10 = c1;
                c1 = c;
            }
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