#include "large_number.hpp"

using namespace std;

int main()
{
    LargeNumber num("333");

    LargeNumber num2("1100");
    LargeNumber num3 = num * num2;

    num.printInt32();
    num2.printInt32();
    num3.printInt32();

    return 0;
}