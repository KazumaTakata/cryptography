#include "large_number.hpp"

LargeNumber LargeNumber::Euclid(LargeNumber &Operand)
{
    LargeNumber r1;
    LargeNumber r0;
    LargeNumber r2;
    LargeNumber zero("0");
    if (*this > Operand)
    {
        r0 = *this;
        r1 = Operand;
    }
    else
    {
        r1 = *this;
        r0 = Operand;
    }

    do
    {
        r2 = r0 % r1;
        r2.debug();
        r1.debug();
        r0.debug();
        r0 = r1;
        r1 = r2;

    } while (r2 != zero);

    return r0;
}

LargeNumber LargeNumber::randomLargeNumber(int byteSize)
{

    LargeNumber newlargenumber = LargeNumber(byteSize);
    srand(time(NULL));

    for (int j = 0; j < byteSize; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            double r = ((double)rand() / (RAND_MAX));
            if (r > 0.5)
            {
                newlargenumber.number[j] += 1 << i;
            }
        }
    }

    return newlargenumber;
}

LargeNumber LargeNumber::ModularExponent(LargeNumber power, LargeNumber modulo)
{
    LargeNumber r = this->newCopy();
    bool start = false;
    for (int i = power.byteNum - 1; i >= 0; i--)
    {
        for (int j = 7; j > 0; j--)
        {
            if (power.number[i] & 1 << j)
            {
                start = true;
                r = (r * r) % modulo;
                r = r * *this;
            }
            else
            {
                if (start)
                {
                    r = (r * r) % modulo;
                }
            }
        }
    }

    return r;
}