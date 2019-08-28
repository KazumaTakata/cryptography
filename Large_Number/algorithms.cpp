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