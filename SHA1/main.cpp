#include <iostream>
#include <vector>
#include <string>
#include "printBit.hpp"
#include "round.hpp"

using namespace std;

u_int32_t H0 = 0x67452301;
u_int32_t H1 = 0xEFCDAB89;
u_int32_t H2 = 0x98BADCFE;
u_int32_t H3 = 0x10325476;
u_int32_t H4 = 0xC3D2E1F0;

int main()
{
    string message = "abc";
    int64_t messageBitSize = message.size() * 8;
    int paddingLength = (448 - messageBitSize - 1) % 512;
    int blocksize = ((message.size() + 64) / 512) + 1;

    vector<vector<u_int32_t>> blocks;
    int messageIndex = 0;
    bool allEnd = false;
    int endIndex = 0;

    for (int blockIndex = 0; blockIndex < blocksize; blockIndex++)
    {
        vector<u_int32_t> block512;
        for (int chunkIndex = 0; chunkIndex < 16; chunkIndex++)
        {
            u_int32_t chunk32 = 0;
            for (int i = 3; i >= 0; i--)
            {
                if (message.size() > messageIndex)
                {
                    u_int32_t tmp = message[messageIndex];
                    tmp = tmp << (i * 8);
                    chunk32 += tmp;

                    messageIndex++;
                }
                else
                {
                    allEnd = true;
                    endIndex = i;
                    break;
                }
            }
            block512.push_back(chunk32);
            if (allEnd)
            {
                break;
            }
        }
        blocks.push_back(block512);
        if (allEnd)
        {
            break;
        }
    }

    int blocksLastIndex = blocks.size() - 1;
    int block512LastIndex = blocks[blocksLastIndex].size() - 1;

    u_int32_t one = 1 << ((endIndex + 1) * 8 - 1);

    // bin(one);
    SHOW(unsigned int, one);

    if (endIndex != 3)
    {
        SHOW(unsigned int, blocks[blocksLastIndex][block512LastIndex]);
        blocks[blocksLastIndex][block512LastIndex] += one;
        SHOW(unsigned int, blocks[blocksLastIndex][block512LastIndex]);

        int remainingZero = 7 + (endIndex * 8);
        paddingLength -= remainingZero;
        int paddingchunk32Length = paddingLength / 32;

        for (int i = 0; i < paddingchunk32Length; i++)
        {
            blocks[blocksLastIndex].push_back(0);
        }

        SHOW(u_int64_t, messageBitSize);
        u_int32_t size1 = (u_int32_t)(messageBitSize >> 32);
        u_int32_t size2 = (u_int32_t)((messageBitSize << 32) >> 32);
        SHOW(int, size1);
        SHOW(int, size2);

        blocks[blocksLastIndex].push_back(size1);
        blocks[blocksLastIndex].push_back(size2);
        printf("%d", blocks[blocksLastIndex].size());
    }
    else
    {
    }

    u_int32_t words[80];
    for (int i = 0; i < 80; i++)
    {
        if (i < 16)
        {
            words[i] = blocks[0][i];
        }
        else
        {
            u_int32_t tmpWord = words[i - 16] ^ words[i - 14] ^ words[i - 8] ^ words[i - 3];
            words[i] = (tmpWord << 1) | (tmpWord >> (32 - 1));
        }
    }
    Registers registers;
    registers.A = H0;
    registers.B = H1;
    registers.C = H2;
    registers.D = H3;
    registers.E = H4;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            registers = round(registers, (Round)i, words[j + i * 20]);
        }
    }

    registers.A += H0;
    registers.B += H1;
    registers.C += H2;
    registers.D += H3;
    registers.E += H4;

    SHOW(u_int32_t, registers.A);

    return 0;
}
