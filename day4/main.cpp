#include <iostream>
#include <fstream>
#include <vector>

auto open() {
    std::ifstream file{"/home/pfese/aoc2022/day4/input.txt"};

    if (!file.is_open()) {
        std::cerr << "file did not open";
        exit(1);
    }

    std::vector<std::string> lines;
    std::string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

void add_nums(std::string range, std::vector<int> *nums) {
    int dash = range.find('-');

    nums->push_back(stoi(range.substr(0, dash)));
    nums->push_back(stoi(range.substr(dash + 1)));
}

int part_1() {
    auto lines = open();

    int answer = 0;

    for (auto line: lines) {
        std::vector<int> nums;

        auto comma_pos = line.find(',');
        std::string first_range = line.substr(0, comma_pos);
        std::string second_range = line.substr(comma_pos + 1);

        std::cout << "first range: " << first_range << std::endl;
        std::cout << "second range: " << second_range << std::endl;

        add_nums(first_range, &nums);
        add_nums(second_range, &nums);

        for (auto num: nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        if (nums[0] <= nums[2] && nums[1] >= nums[3]) {
            std::cout << "Left Contains Right ^^" << std::endl;
            answer += 1;
        } else if (nums[2] <= nums[0] && nums[3] >= nums[1]) {
            std::cout << "Right Contains Left ^^" << std::endl;
            answer += 1;
        }
    }

    std::cout << "Answer: " << answer << std::endl;
    return 0;
}

void part2() {
    auto lines = open();

    int answer = 0;

    for (auto line: lines) {
        std::vector<int> nums;

        auto comma_pos = line.find(',');
        std::string first_range = line.substr(0, comma_pos);
        std::string second_range = line.substr(comma_pos + 1);

        std::cout << "first range: " << first_range << std::endl;
        std::cout << "second range: " << second_range << std::endl;

        add_nums(first_range, &nums);
        add_nums(second_range, &nums);

        for (auto num: nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        auto within_first_range = [nums](int num) {
            return num >= nums[0] && num <= nums[1];
        };

        // check either digit of first within second range
        // check either digit of secend within first range
        if (nums[0] >= nums[2] && nums[0] <= nums[3]) {
            std::cout << "first num within second range ^^" << std::endl;
            answer += 1;
        } else if (nums[1] >= nums[2] && nums[1] <= nums[3]) {
            std::cout << "second num within second range ^^" << std::endl;
            answer += 1;
        } else if (within_first_range(nums[2])) {
            std::cout << "third num within first range ^^" << std::endl;
            answer += 1;
        } else if (within_first_range(nums[3])) {
            std::cout << "fourth num within first range ^^" << std::endl;
            answer += 1;
        }
    }

    std::cout << "Answer: " << answer << std::endl;
}

int main() {
    part2();
}
