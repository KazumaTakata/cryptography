#include <iostream>

u_int32_t K1 = 0x5A827999;
u_int32_t K2 = 0x6ED9EBA1;
u_int32_t K3 = 0x8F1BBCDC;
u_int32_t K4 = 0xCA62C1D6;

u_int32_t f1(u_int32_t B, u_int32_t C, u_int32_t D)
{
    return (B & C) | (~B & D);
}
u_int32_t f2(u_int32_t B, u_int32_t C, u_int32_t D)
{
    return (B ^ C ^ D);
}
u_int32_t f3(u_int32_t B, u_int32_t C, u_int32_t D)
{
    return (B & C) | (B & D) | (C & D);
}
u_int32_t f4(u_int32_t B, u_int32_t C, u_int32_t D)
{
    return (B ^ C ^ D);
}

typedef struct Registers
{
    u_int32_t A;
    u_int32_t B;
    u_int32_t C;
    u_int32_t D;
    u_int32_t E;
} Registers;

enum Round
{
    ONE,
    TWO,
    THREE,
    FOURE,
};

u_int32_t leftRotate(u_int32_t n, unsigned int d)
{
    return (n << d) | (n >> (32 - d));
}

Registers round(Registers registers, Round rou, u_int32_t word)
{
    Registers newregisters;
    u_int32_t tmp;
    switch (rou)
    {
    case ONE:
        tmp = f1(registers.B, registers.C, registers.D) + K1;
        break;
    case TWO:
        tmp = f2(registers.B, registers.C, registers.D) + K2;
        break;
    case THREE:
        tmp = f3(registers.B, registers.C, registers.D) + K3;
        break;
    case FOURE:
        tmp = f4(registers.B, registers.C, registers.D) + K4;
        break;
    default:
        break;
    }

    newregisters.A = registers.E + tmp + leftRotate(registers.A, 5) + word;
    newregisters.B = registers.A;
    newregisters.C = leftRotate(registers.B, 30);
    newregisters.D = registers.C;
    newregisters.E = registers.D;

    return newregisters;
}