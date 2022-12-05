#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

int part_2() {
    std::ifstream input("/home/pfese/aoc2022/day1/part1.txt");

    if (!input.is_open()) {
        std::cerr << "Failed to open input" << std::endl;
    }

    std::string line;
    int current = 0;
    std::vector<int> top3 = { 0, 0, 0 };

    while (std::getline(input, line)) {
        if (line == "") {
            std::cout << "Current: " << current << std::endl;

            for(auto i = 0; i < 3; i++) {
                if (current > top3[i]) {
                    top3[i] = current;
                    std::sort(top3.begin(), top3.end());
                    break;
                }
            }

            current = 0;
        } else {
            int number;
            std::stringstream(line) >> number;

            current += number;
        }
    }

    return top3[0] + top3[1] + top3[2];
}

int foo() {
    return 42;
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    EXPECT_EQ(part_2(), 45000);

// Expect two strings not to be equal.
// EXPECT_STRNE("hello", "world");
}
