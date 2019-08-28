#include "large_number.hpp"
#include "util.hpp"

void LargeNumber::printLargeNumber(int zeroPadding)
{
    for (int i = 0; i < zeroPadding; i++)
    {
        print_byte_as_bits(0);
    }
    for (int i = 0; i < this->byteNum; i++)
    {
        print_byte_as_bits(this->number[this->byteNum - i - 1]);
    }
    printf("\n");
}
void LargeNumber::printLargeNumber()
{
    for (int i = 0; i < this->byteNum; i++)
    {
        print_byte_as_bits(this->number[this->byteNum - i - 1]);
    }
    printf("\n");
}

void LargeNumber::printInt32()
{
    int sum = 0;
    for (int i = 0; i < this->byteNum; i++)
    {
        sum += this->number[i] * (1 << (8 * i));
    }

    printf("%d\n", sum);
}

void LargeNumber::debug()
{
    this->debugStr = "";
    for (int i = 0; i < this->byteNum; i++)
    {
        char val = this->number[this->byteNum - i - 1];
        for (int j = 7; 0 <= j; j--)
        {
            this->debugStr += val & (1 << j) ? '1' : '0';
        }
    }
}

void LargeNumber::assignValue(string number)
{
    for (int i = 0; i < number.size(); i++)
    {
        char hex = number[number.size() - i - 1];
        int hexValue = hex2int(hex);
        int index = i / 2;
        int upper = (i % 2) * 4;
        this->number[index] += hexValue << upper;
    }
}

LargeNumber::LargeNumber(int byteNum)
{
    this->byteNum = byteNum;
    this->number = (unsigned char *)calloc(byteNum, sizeof(char));
};

LargeNumber::LargeNumber(string number)
{
    int byteNum = (number.size() + 1) / 2;
    this->byteNum = byteNum;
    this->number = (unsigned char *)calloc(byteNum, sizeof(char));
    assignValue(number);
}

LargeNumber::LargeNumber(){};

bool LargeNumber::operator>(LargeNumber &Operand)
{
    if (this->byteNum > Operand.byteNum)
    {
        return true;
    }
    else if (this->byteNum < Operand.byteNum)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < this->byteNum; i++)
        {
            if (this->number[this->byteNum - i - 1] > Operand.number[this->byteNum - i - 1])
            {
                return true;
            }
            else if (this->number[this->byteNum - i - 1] < Operand.number[this->byteNum - i - 1])
            {
                return false;
            }
            else
            {
            }
        }
    }

    // if equal
    return false;
}

bool LargeNumber::operator<(LargeNumber &Operand)
{
    return Operand > *this;
}

LargeNumber LargeNumber::operator/(LargeNumber &Operand)
{

    string answer = "";
    LargeNumber divider = Operand.newCopy();
    LargeNumber remain = this->newCopy();
    divider.debug();
    Operand.debug();
    remain.debug();
    while (remain > divider)
    {
        divider.leftShift();
        divider.debug();
    }

    do
    {
        divider.rightShift();
        while (remain < divider && divider > Operand)
        {
            divider.rightShift();
            divider.debug();
            answer += '0';
        }

        answer += '1';
        remain -= divider;
        remain.debug();
    } while (remain > Operand);

    int size = (answer.size() - 1) / 4 + 1;

    LargeNumber newlargenumber(size);
    for (int i = 0; i < size; i++)
    {
        unsigned char sum = 0;
        for (int j = 0; j < 8; j++)
        {
            if (answer[j + i * 8] == '1')
            {
                sum += 1 << j;
            }
        }
        newlargenumber.number[i] = sum;
    }

    return newlargenumber;
}

LargeNumber LargeNumber::operator%(LargeNumber &Operand)
{

    string answer = "";
    LargeNumber divider = Operand.newCopy();
    LargeNumber remain = this->newCopy();
    divider.debug();
    Operand.debug();
    remain.debug();
    while (remain > divider)
    {
        divider.leftShift();
        divider.debug();
    }

    do
    {
        divider.rightShift();
        while (remain < divider && divider > Operand)
        {
            divider.rightShift();
            divider.debug();
            answer += '0';
        }

        answer += '1';
        remain -= divider;
        remain.debug();
    } while (remain > Operand);

    int size = (answer.size() - 1) / 4 + 1;

    LargeNumber newlargenumber(size);
    for (int i = 0; i < size; i++)
    {
        unsigned char sum = 0;
        for (int j = 0; j < 8; j++)
        {
            if (answer[j + i * 8] == '1')
            {
                sum += 1 << j;
            }
        }
        newlargenumber.number[i] = sum;
    }

    return remain;
}

LargeNumber LargeNumber::operator-(LargeNumber &Operand)
{

    LargeNumber newlargenumber(this->byteNum);

    bool borrow = false;
    for (int i = 0; i < this->byteNum; i++)
    {

        int diff;
        if (i < Operand.byteNum)
        {
            diff = this->number[i] - Operand.number[i];
        }
        else
        {
            diff = this->number[i];
        }

        if (borrow)
        {
            diff--;
        }

        if (diff < 0)
        {
            borrow = true;
            diff += 1 << 8;
        }
        else
        {
            borrow = false;
        }

        newlargenumber.number[i] = (unsigned char)diff;
    }

    newlargenumber.shrinkZero();

    return newlargenumber;
}

void LargeNumber::operator-=(LargeNumber &Operand)
{

    bool borrow = false;
    for (int i = 0; i < this->byteNum; i++)
    {

        int diff;
        if (i < Operand.byteNum)
        {
            diff = this->number[i] - Operand.number[i];
        }
        else
        {
            diff = this->number[i];
        }

        if (borrow)
        {
            diff--;
        }

        if (diff < 0)
        {
            borrow = true;
            diff += 1 << 8;
        }
        else
        {
            borrow = false;
        }

        this->number[i] = (unsigned char)diff;
    }

    this->shrinkZero();
}

void LargeNumber::shrinkZero()
{
    int index = this->byteNum - 1;
    while (this->number[index] == 0 && index > 0)
    {
        this->shrink();
        index--;
    }
}

LargeNumber LargeNumber::operator+(LargeNumber &Operand)
{
    int largeByteNum;
    int smallByteNum;
    LargeNumber *largenumber;
    if (this->byteNum > Operand.byteNum)
    {
        largeByteNum = this->byteNum;
        smallByteNum = Operand.byteNum;
        largenumber = this;
    }
    else
    {
        largeByteNum = Operand.byteNum;
        smallByteNum = this->byteNum;
        largenumber = &Operand;
    }

    LargeNumber newlargenumber(largeByteNum);

    bool carry = false;
    for (int i = 0; i < largeByteNum; i++)
    {

        int sum;
        if (i < smallByteNum)
        {
            sum = this->number[i] + Operand.number[i];
        }
        else
        {
            sum = largenumber->number[i];
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

    if (carry)
    {
        newlargenumber.expand();
    }

    return newlargenumber;
}

void LargeNumber::operator+=(LargeNumber &Operand)
{
    LargeNumber newOperand = Operand.newCopy();
    newOperand.debug();
    if (this->byteNum < Operand.byteNum)
    {
        LargeNumber tmp = this->newCopy();
        this->setCopy(newOperand);
        free(newOperand.number);
        newOperand = tmp;
    }
    this->debug();
    newOperand.debug();

    bool carry = false;
    for (int i = 0; i < this->byteNum; i++)
    {

        int sum;
        if (i < newOperand.byteNum)
        {
            sum = this->number[i] + newOperand.number[i];
        }
        else
        {
            sum = this->number[i];
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
        this->number[i] = (unsigned char)(mask & sum);
    }

    if (carry)
    {
        expand();
    }
}

void LargeNumber::leftShift()
{
    bool carry = false;
    bool pastCarry = false;
    for (int i = 0; i < this->byteNum; i++)
    {

        unsigned char tmp = this->number[i];

        if (tmp >= 1 << 7)
        {
            carry = true;
        }
        else
        {
            carry = false;
        }

        tmp = tmp << 1;

        if (pastCarry)
        {
            tmp += 1;
        }

        pastCarry = carry;

        this->number[i] = tmp;
    }

    if (carry)
    {
        expand();
    }
}

void LargeNumber::rightShift()
{
    bool carry = false;
    bool pastCarry = false;
    for (int i = 0; i < this->byteNum; i++)
    {

        unsigned char tmp = this->number[this->byteNum - i - 1];

        if (tmp & 1)
        {
            carry = true;
        }
        else
        {
            carry = false;
        }

        tmp = tmp >> 1;

        if (pastCarry)
        {
            tmp += 1 << 7;
        }

        pastCarry = carry;

        this->number[this->byteNum - i - 1] = tmp;
    }

    if (this->number[this->byteNum - 1] == 0)
    {
        this->shrink();
    }
}

void LargeNumber::expand()
{
    unsigned char *tmp = this->number;
    this->byteNum++;
    this->number = (unsigned char *)calloc(this->byteNum, sizeof(unsigned char));
    memcpy(this->number, tmp, (this->byteNum - 1) * sizeof(unsigned char));
    this->number[this->byteNum - 1] = 0x01;
    free(tmp);
}

void LargeNumber::shrink()
{
    unsigned char *tmp = this->number;
    this->byteNum--;
    this->number = (unsigned char *)calloc(this->byteNum, sizeof(unsigned char));
    memcpy(this->number, tmp, (this->byteNum) * sizeof(unsigned char));
    free(tmp);
}

void LargeNumber::setCopy(LargeNumber &largenumber)
{
    free(this->number);
    this->byteNum = largenumber.byteNum;
    this->number = (unsigned char *)calloc(largenumber.byteNum, sizeof(unsigned char));
    memcpy(this->number, largenumber.number, (largenumber.byteNum) * sizeof(unsigned char));
}

LargeNumber LargeNumber::newCopy()
{
    LargeNumber newlargenumber(this->byteNum);
    for (int i = 0; i < this->byteNum; i++)
    {
        newlargenumber.number[i] = this->number[i];
    }

    return newlargenumber;
}

LargeNumber LargeNumber::operator*(LargeNumber &Operand)
{
    LargeNumber largenumber;
    LargeNumber smallnumber;
    if (this->byteNum > Operand.byteNum)
    {
        largenumber = *this;
        smallnumber = Operand;
    }
    else
    {
        largenumber = Operand;
        smallnumber = *this;
    }

    LargeNumber tmplargenumber = largenumber.newCopy();

    LargeNumber newlargenumber(largenumber.byteNum);

    for (int i = 0; i < smallnumber.byteNum; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            smallnumber.debug();
            if (smallnumber.number[i] & (1 << j))
            {
                newlargenumber += tmplargenumber;
                newlargenumber.debug();
            }
            tmplargenumber.leftShift();
            tmplargenumber.debug();
        }
    }

    return newlargenumber;
}