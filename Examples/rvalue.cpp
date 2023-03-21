#include<iostream>
#include<string>

void foo(const std::string& str)
{
    std::cout << str << std::endl;
}

int main()
{
    foo(std::string{"Hello"});

    return 0;
}