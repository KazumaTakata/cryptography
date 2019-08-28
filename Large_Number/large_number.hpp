#ifndef HLARGENUM
#define HLARGENUM

#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
#include <string>

using namespace std;

class LargeNumber
{
public:
    int byteNum;
    unsigned char *number;
    string debugStr;
    LargeNumber(int byteNum);
    LargeNumber(string number);
    LargeNumber();
    LargeNumber initLargeNumber(int bytenum);

    void assignValue(string number);
    void initWithZero();
    void printLargeNumber();
    void printLargeNumber(int zeroPadding);
    void printInt32();
    void debug();
    void initLargeNumberWithValue(string number);
    // allocate one more byte
    void expand();
    void leftShift();
    LargeNumber newCopy();
    void setCopy(LargeNumber &largenumber);

    LargeNumber
    operator+(LargeNumber &Operand);
    LargeNumber operator-(LargeNumber &Operand);
    LargeNumber operator*(LargeNumber &Operand);
    LargeNumber operator/(LargeNumber &Operand);

    LargeNumber operator<<(int i);
    void operator+=(LargeNumber &Operand);
};

#endif