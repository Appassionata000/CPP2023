#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    string a = "1+2i", b = "1+3i";
    istringstream sa(a), sb(b);
    ostringstream out;

    int ra, ia, rb, ib;
    char buff;
    // only read integer values to get the real and imaginary part of
    // of the original complex number
    sa >> ra >> buff >> ia >> buff;
    sb >> rb >> buff >> ib >> buff;

    out << ra + rb << '+' << ia + ib << 'i';

    // final result in string format
    string result = out.str();

    std::cout << result << std::endl;
}