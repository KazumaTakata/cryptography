#include "large_number.hpp"

using namespace std;

int main()
{
    LargeNumber num("300");

    LargeNumber num2("1100");
    LargeNumber num3 = num * num2;

    num.printLargeNumber();
    num2.printLargeNumber();
    num3.printLargeNumber();

    // num.printLargeNumber();
    // printf("\n");
    // num2.printLargeNumber();
    // printf("\n");
    // num3.printLargeNumber();

    return 0;
}