#include <iostream>
#include <fstream>
#include <vector>
#include <string>

auto parse_file() {
    std::ifstream file { "/home/pfese/aoc2022/day2/input.txt" };

    if (!file.is_open()) {
        std::cout << "File not opened" << std::endl;
        exit(1);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

auto part_1() {
    int score = 0;
    for(auto line: parse_file()) {
        if (line == "A X") {
            // r @ s
            score += 3;
            score += 0;
        }
        else if (line == "A Y") {
            // r @ r
            score += 1;
            score += 3;
        }
        else if (line == "A Z") {
            // r @ p
            score += 2;
            score += 6;
        }
        else if (line == "B X") {
            // p @ r
            score += 1;
            score += 0;
        }
        else if (line == "B Y") {
            // p @ p
            score += 2;
            score += 3;
        }
        else if (line == "B Z") {
            // p @ s
            score += 3;
            score += 6;
        }
        else if (line == "C X") {
            // s @ p
            score += 2;
            score += 0;
        }
        else if (line == "C Y") {
            // s @ s
            score += 3;
            score += 3;
        }
        else if (line == "C Z") {
            // s @ r
            score += 1;
            score += 6;
        }
        else {
            std::cout << "error! no match!" << std::endl;
            std::cout << line << std::endl;
            exit(1);
        }
    }

    std::cout << "Score: " << score << std::endl;
}


int main() {
    part_1();

    return 0;
}
