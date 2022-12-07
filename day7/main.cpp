#include <iostream>
#include <vector>
#include "library.h"

using std::endl;
using std::cout;
using std::string;
using std::vector;

int part1(auto lines) {
    return 42;
}


int main() {
    string path = "/home/pfese/aoc2022/day7/";
    auto test_input = open(path + "tinput.txt");
    auto input = open(path + "input.txt");

    cout << "Testing Part 1" << endl;
    if (print_result(part1(test_input), 95437)) exit(1);
    cout << endl;

    cout << "Answering Part 1" << endl;
    cout << part1(input) << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
