#include <iostream>
#include <fstream>
#include <vector>
#include <ranges>
#include <iterator>

auto open() {
    std::ifstream file("/home/pfese/aoc2022/day3/input.txt");

    if (!file.is_open()) {
        std::cout << "Did not open input file" << std::endl;
        exit(1);
    }

    std::vector<std::string> lines;
    std::string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

class Number {
   int value;
public:
   Number(int v): value(v) {}
   int square() { return value * 2; }
};

class Codes {
    int number;
    std::string name;
public:
    Codes(int num, std:: string str): number(num), name(str) {}
    std::string to_string() { return name + " " + std::to_string(number); };
};

int calc_score(char c) {
    int i = c;

    if (i > 90) {
        return i - 96;
        // lowercase
    } else {
        return i - 38;
        // uppercase
    }
}

void part1() {
    auto file = open();

    auto priority = 0;
    for (auto line: file) {
        auto length = line.length();
        int mid = length / 2;

        auto second = line.substr(mid);


        for (auto i = 0; i < mid; i++) {
            if (second.contains(line[i])) {
                std::cout << "Found dup: " << line[i] << std::endl;

                char l = line[i];
                int p = calc_score(l);

                priority += p;

                std::cout << "Score: " << p << std::endl;

                break;
            }
        }
    }

    std::cout << "Total Score: " << priority << std::endl;
}

void part2() {
    auto file = open();

    auto priority = 0;
    auto nth = 0;
    for (auto i = 0; i < file.size(); i++) {
        auto line = file[i];

        if (nth == 0) {
            for (char c: line) {
                if (file[i + 1].contains(c) && file[i+ 2].contains(c)) {
                    std::cout << "All three have: " << c << std::endl;

                    priority += calc_score(c);

                    break;
                }
            }

        }

        nth = (nth + 1) % 3;
    }

    std::cout << "Total Score: " << priority << std::endl;
}

int main() {
    part2();

    return 0;
}
