#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ranges>
#include <numeric>
#include <iostream>

std::vector<std::string> read_lines() {
    std::ifstream file {"/home/pfese/aoc2020/day1/file.txt" };

    if (!file.is_open()) {
        std::cerr << "Could not open file file" << std::endl;
        exit(1);
    }

    std::vector<std::string> lines;
    std::string line;

    while(std::getline(file, line)) {
        lines.push_back(line);
    };

    return lines;
}

int part_1() {
    auto data = read_lines();
    auto input = data | std::views::split(std::string{}) | std::views::transform([](const auto& elf) -> uint64_t {
        auto to_unsigned = [](const auto& in){ return std::stoull(in); };
        auto rng = elf | std::views::transform(to_unsigned);
        return std::reduce(rng.start(), rng.end());
    });

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
