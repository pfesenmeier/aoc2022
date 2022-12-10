#include <iostream>
#include <vector>
#include <optional>
#include <list>
#include <ranges>
#include <fstream>

using namespace std;

const string NOOP = "noop";
const string ADDX = "addx";
string PATH = "";

class signal {
private:
    signal(int value, int duration) : value(value), duration(duration) {}

public:
    int value;
    int duration;

    static signal noop() {
        return signal(0, 1);
    };

    static signal addx(int value) {
        return signal(value, 2);
    }

    bool execute() {
        duration--;

        if (duration == 0) {
            return true;
        }

        return false;
    }

    int get() {
        return value;
    }

    string to_string() {
        if (value == 0) {
            return NOOP;
        }
        return ADDX + " " + std::to_string(value);
    }

    static signal parse(string s) {
        if (s == "noop") {
            return signal::noop();
        }

        auto space = s.find(' ');
        auto value = s.substr(space + 1);
        return signal::addx(stoi(value));
    }
};

class signal_detector {
    int answer = 0;

    bool is_important(int cycle) {
        return (cycle - 20) % 40 == 0;
    }

public:
    signal_detector() {}

    void scan(int cycle, int value) {
        if (is_important(cycle)) {
            cout << "Cycle " << std::to_string(cycle) << " value: " << value << endl;
            answer += cycle * value;
            cout << "Answer is now: " << answer << endl;
        }
    }

    int get() {
        return answer;
    }
};

struct coord {
    int row;
    int col;

    coord(int row, int col) : row(row), col(col) {}
};

class screen_state {
    int regX;
    int cycle;

public:
    screen_state(int cycle, int regX) : regX(regX), cycle(cycle) {}

    coord get_coord() {
        int row = (cycle - 1) / 40;
        int col = (cycle - 1) % 40;
        return coord(row, col);
    }

    bool on_sprite() {
        int col = (cycle - 1) % 40;
        int max = regX + 1;
        int min = regX - 1;
        return col >= min && col <= max;
    }
};

class crt {
    array<array<bool, 40>, 6> pixels;

    char print_c(bool on_sprite) {
        return on_sprite ? '#' : '_';
    }

    void push(coord loc, bool on_sprite) {
        cout << "Adding '" << print_c(on_sprite) << "' in row " << to_string(loc.row) << ", col " << to_string(loc.col) << endl;
        pixels.at(loc.row).at(loc.col) = on_sprite;
    }

    void print() {
        cout << endl;
        for (auto row: pixels) {
            for (auto pixel: row) {
                cout << print_c(pixel);
            }
            cout << endl;
        }
        cout << endl;
    }

    bool is_visible(coord c) {
        if (c.row >= pixels.size()) {
            cout << "Warning: did not print because row " << c.row << " does not exist" << endl;
            return false;
        }
        if (c.col >= pixels.at(0).size()) {
            cout << "Warning: did not print because column " << c.col << " does not exist" << endl;
            return false;
        }
        return true;
    }

public:
    crt() : pixels() {}

    void draw(int cycle, int regX) {
        screen_state s{cycle, regX};

        if(is_visible(s.get_coord())) {
            push(s.get_coord(), s.on_sprite());
            print();
        }
    }
};


class circuit {
    list<signal> stack;
    optional<signal> current = nullopt;
    signal_detector detector;
    crt tube;
    int registerX = 1;
    int i = 1;

    void start_cycle() {
        cout << "  Starting cycle " << i << endl;

        if (!current) {
            auto next = stack.front();
            stack.pop_front();
            current = next;
            cout << "    Executing " << current->to_string() << endl;
        } else {
            cout << "    Still executing " << current->to_string() << endl;
        }
    };

    void end_cycle() {
        cout << "  Ending cycle " << i << endl;

        if (current->execute()) {
            cout << "    Finished " << current->to_string() << endl;

            auto value = current->get();
            registerX += value;

            if (value > 0) {
                cout << "    X is now " << registerX << endl;
            } else {
                cout << "    X is still " << registerX << endl;
            }

            current.reset();
        } else {
            cout << "    X is still " << registerX << endl;
        }
        i++;
    };

    bool is_running() {
        return !stack.empty() || current.has_value();
    }

public:
    circuit(auto stack) : stack(stack), detector(), tube() {}

    void print_answer() {
        cout << "Answer: " << std::to_string(detector.get()) << endl;
    }

    bool cycle() {
        cout << std::to_string(i) << endl;

        start_cycle();
        cout << "    During cycle " << std::to_string(i) << " X is " << registerX << endl;

        detector.scan(i, registerX);
        tube.draw(i, registerX);

        end_cycle();

        return is_running();
    }
};

auto open() {
    ifstream input{PATH};
    if (!input.is_open()) {
        cout << "no file" << endl;
        exit(1);
    }

    list<signal> lines;

    for (string line; getline(input, line);) {
        lines.emplace_back(signal::parse(line));
    }

    return lines;
}

void part1() {
    circuit c{open()};

    while (c.cycle()) {}
    c.print_answer();
}

int main(int argc, char *argv[]) {
    PATH = argv[1];

    part1();

    return 0;
}
