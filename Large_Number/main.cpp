#include "large_number.hpp"

using namespace std;

int main()
{
    LargeNumber num("42a3");

    LargeNumber num2("783");

    LargeNumber num3 = num.Euclid(num2);

    LargeNumber random = LargeNumber::randomLargeNumber(4);

    num.printInt32();
    num2.printInt32();
    num3.printInt32();

   
    return 0;
}