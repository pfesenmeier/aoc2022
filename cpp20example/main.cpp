#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>

int main()
{
    auto foo = std::string { "move 1 from 2 to 1" };

    auto bar = foo.find(' ');

    std::cout << bar << std::endl;
}