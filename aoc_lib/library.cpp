#include "library.h"

#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::string;
using std::endl;
using std::cout;

vector<string> open(string path) {
    std::ifstream input { path };

    if (!input.is_open()) {
        cout << "Failed to open input file: " << path << endl;
        exit(1);
    }

    vector<string> lines;
    for(string line; getline(input, line);) {
        lines.push_back(line);
    }

    return lines;
}

int print_result(int actual, int expected) {
    if (expected == actual) {
        cout << "pass" << endl;
        return 0;
    } else {
        cout << "fail" << endl;
        cout << "  Expected : " << expected << endl;
        cout << "  Actual   : " << actual << endl;
        return 1;
    }
}
