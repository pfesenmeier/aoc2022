#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <ranges>
#include <set>
#include <list>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::endl;

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

void printv(auto foo) {
    for (auto f: foo)
        cout << f;
    cout << endl;
}

int part1_iter(string buffer) {
    namespace views = std::views;
    namespace ranges = std::ranges;
    using std::back_inserter;

    const int PCKT_LEN = 4;

    // index = 0
    int index = 0;
    // drop view index
    for(auto window : buffer | views::slide(PCKT_LEN) ) {
        string next_four_copy;
        ranges::copy_n(window.begin(), PCKT_LEN, back_inserter(next_four_copy));

        ranges::sort(next_four_copy);

        string unique;
        ranges::unique_copy(next_four_copy.begin(), next_four_copy.end(), back_inserter(unique));

        if (unique.size() == PCKT_LEN) {
            return index + PCKT_LEN;
        }

        index++;
    }

    return -1;
}

int part1(string buffer) {
    for (auto index = 0; index < buffer.length(); index++) {
        std::set<char> bset{buffer[index], buffer[index + 1], buffer[index + 2], buffer[index + 3]};

        if (bset.size() == 4) {
            return index + 4;
        }
    }

    return -1;
}

int part2(string buffer) {
    const int MSG_LENGTH = 14;
    for (auto index = 0; index < buffer.length(); index++) {
        std::set<char> bset{};
        for (auto i = 0; i < MSG_LENGTH; i++) {
            bset.insert(buffer[index + i]);
        }

        if (bset.size() == MSG_LENGTH) {
            return index + MSG_LENGTH;
        }
    }

    return -1;
}

void test1(auto part1) {
    vector<std::tuple<string, int>> cases = {
            {"mjqjpqmgbljsphdztnvjfqwrcgsmlb",    7},
            {"bvwbjplbgvbhsrlpgdmjqwftvncz",      5},
            {"nppdvjthqldpwncqszvftbrmjlhg",      6},
            {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10},
            {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw",  11}
    };

    for (auto test_case: cases) {
        auto [buffer, answer] = test_case;
        print_result(part1(buffer), answer);
    }
};

void test2() {
    vector<std::tuple<string, int>> cases = {
            {"mjqjpqmgbljsphdztnvjfqwrcgsmlb",    19},
            {"bvwbjplbgvbhsrlpgdmjqwftvncz",      23},
            {"nppdvjthqldpwncqszvftbrmjlhg",      23},
            {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 29},
            {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw",  26}
    };

    for (auto test_case: cases) {
        auto [buffer, answer] = test_case;
        print_result(part2(buffer), answer);
    }
};

int main() {
    cout << "part1\n";
    test1(part1);
    cout << "part1 with ranges\n";
    test1(part1_iter);
//    test2();
//    std::ifstream input{"../input.txt"};
//    string line;
//    getline(input, line);
//    string l = line;
//
//    auto answer = part2(l);
//    cout << answer << endl;
//
    return 0;
}
