#include "large_number.h"

LargeNumber add(LargeNumber large1, LargeNumber large2)
{
    int largeByteNum;
    int smallByteNum;
    LargeNumber largenumber;
    LargeNumber newlargenumber = initLargeNumber(largeByteNum + 1);
    if (large1.byteNum > large2.byteNum)
    {
        largeByteNum = large1.byteNum;
        smallByteNum = large2.byteNum;
        largenumber = large1;
    }
    else
    {
        largeByteNum = large2.byteNum;
        smallByteNum = large1.byteNum;
        largenumber = large2;
    }

    bool carry = false;
    for (int i = 0; i < largeByteNum; i++)
    {

        int sum;
        if (i < smallByteNum)
        {
            sum = large1.number[i] + large2.number[i];
        }
        else
        {
            sum = largenumber.number[i];
        }

        if (carry)
        {
            sum++;
        }

        if (sum >= 1 << 8)
        {
            carry = true;
        }
        else
        {
            carry = false;
        }
        int mask = (1 << 8) - 1;
        newlargenumber.number[i] = (unsigned char)(mask & sum);
    }

    return newlargenumber;
}

int main()
{
    char *value1 = "40";
    char *value2 = "12";
    LargeNumber num = initLargeNumberWithValue(value1);
    LargeNumber num2 = initLargeNumberWithValue(value2);

    LargeNumber num3 = add(num, num2);

    printLargeNumber(&num);
    printf("\n");
    printLargeNumber(&num2);
    printf("\n");
    printLargeNumber(&num3);

    return 0;
}