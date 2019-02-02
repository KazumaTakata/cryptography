#include <stdio.h>

int LCG(int seed);

/* MODMULT(a,b,c,m,s) computes s*b mod m, provided that m=a*b+c and 0 <= c <
m. */

/* combinedLCG returns a pseudorandom real value in the range
* (0,1). It combines linear congruential generators with
* periods of 231-85 and 231-249, and has a period that is the
* product of these two prime numbers. */

int main()
{

    int x1 = 4;
    for (int i = 0; i < 20; i++)
    {
        x1 = LCG(x1);
        printf("%d\n", x1);
    }

    return 0;
}

int LCG(int seed)
{

    int a = 106;
    int b = 1283;
    int m = 6075;

    int x1 = (a * seed + b) % m;

    return x1;
}
