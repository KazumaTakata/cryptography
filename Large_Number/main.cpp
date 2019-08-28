#include "large_number.hpp"

using namespace std;

int main()
{
    LargeNumber num("30200");

    LargeNumber num2("10004328");

    num.printInt32();
    num2.printInt32();
    LargeNumber num3 = num2 % num;
    num.printInt32();
    num2.printInt32();
    num3.printInt32();

    return 0;
}