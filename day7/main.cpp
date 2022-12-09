#include <iostream>
#include <vector>
#include "library.h"
#include "dir.h"
#include <ranges>

using std::endl;
using std::cout;
using std::string;
using std::vector;

const string CD_CMD = "$ cd ";
auto skip_ls = [](const string &line) { return line != "$ ls"; };

int part1(auto lines) {
    file_browser explorer;

    // skip initial "cd / "
    auto ls = lines | std::views::drop(1) | std::views::filter(skip_ls);
    for (auto line: ls) {
        std::cout << "Line: " << line << std::endl;
        if (line.starts_with(CD_CMD)) {
            std::cout << "Moving" << std::endl;
            explorer.move(line.substr(CD_CMD.length()));
        } else {
            std::cout << "Adding" << std::endl;
            std::cout << "Length Before " << explorer.cwd->contents.size() << std::endl;
            explorer.add(line);
            std::cout << "Length After " << explorer.cwd->contents.size() << std::endl;
        };
    }



    std::cout << "Begin Sum" << std::endl;
    int answer = explorer.sum_small_folders();
    std::cout<< "a length " << std::get<dir>(*explorer.home->contents[0]).contents.size() << std::endl;
    std::cout << "Complete!" << std::endl;
    std::cout << "Answer: " << answer << std::endl;
    return answer;
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
