#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <ranges>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::list;


auto open() {
    std:: ifstream file { "../input.txt" };

    if (!file.is_open()) {
      cout << "File did not open" << endl;
      exit(1);
    }

    vector<string> lines;
    string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

void print(auto caption, auto thing) {
    cout << caption << thing << endl;
}

int main() {
    auto lines = open();

    auto num_stacks = (lines[0].length() + 1) / 4;

    print("Number of stacks: ", num_stacks);

    // initialize stacks
    vector<list<char>> stacks;
    for (auto i = 0; i < num_stacks; i++) {
        list<char> stack;
        stacks.push_back(stack);
    }

    // parse map
    for(auto line: lines) {
        // reached end of map
        if (line[1] == '1') {
            break;
        }

        for (auto i = 1;  i < line.length(); i += 4) {
            auto stack_number = (i - 1) / 4;
            print("Current in stack number: ", stack_number);

            if (!(line[i] == ' ')) {
                stacks[stack_number].push_front(line[i]);
            }
        }
    }


    // parse moves
    vector<vector<int>> moves;
    for (auto line: lines) {
        vector<int> move;

        auto try_push = [line](vector<int>& move, int begin, int end = -1) {
            string segment;

            if (end == -1) {
                segment = line.substr(begin);
            } else {
                segment = line.substr(begin, end - begin);
            }

            int num;
            try {
                num = std::stoi(segment);
                move.push_back(num);
            } catch (std::invalid_argument e) {
            };
        };

        print("Line: ", line);
        if (line[0] == 'm') {
            string space = " ";
            auto begin = 0;
            auto end = 0;
            while (end = line.find(space, begin)) {
                if (end == std::string::npos) {
                    try_push(move, begin);
                    break;
                }

                try_push(move, begin, end - begin);

                begin = end + 1;
            }

            cout << "Move: ";
            for (const auto m: move) {
                std::cout << m << " ";
            }
            cout << endl;

            moves.push_back(move);
        }
    }

    // execute moves
    for (auto move: moves) {
        for (auto i = 0; i < move[0]; i++) {
            auto from_stack = &stacks[move[1] - 1];
            auto to_stack = &stacks[move[2] - 1];
            auto box = from_stack->back();
            to_stack->push_back(box);
            from_stack->pop_back();
        }
    }


    // print results
    for (auto i = 0; auto stack: stacks) {
        cout << "Box " << i << " : ";
        i += 1;
        for (auto box: stack) {
            cout << box;
        }
        cout << endl;
    }

    // calculate answer
    string answer;
    for(auto stack: stacks) {
        auto box = stack.back();
        answer += box;
    }

    cout << "Answer" << endl;
    cout << answer << endl;
    return 0;
}
