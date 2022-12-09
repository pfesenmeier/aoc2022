#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <optional>
#include <variant>
#include <fstream>
#include <ranges>

using namespace std;


class file {
public:
    explicit file(string name) : name(std::move(name)) {}

    string name;
};

class dir {
public:
    explicit dir(string name) : name(std::move(name)), contents() {}

    string name;
    vector<shared_ptr<variant<dir, file>>> contents;

    void add(variant<dir, file> node) {
        contents.push_back(move(make_unique<variant<dir, file>>(move(node))));
    }

    void print() {
        print_recurse();
    }

    void print_recurse(int depth = 0) {
        auto space = string(4 * depth, ' ');
        cout << space << name << '/' << endl;
        for (auto&& c: contents) {
            if (holds_alternative<file>(*c)) {
                cout << space << "    " << get<file>(*c).name << endl;
            } else if (holds_alternative<dir>(*c)) {
                get<dir>(*c).print_recurse(depth + 1);
            }
        }
    }
};

void fail (string msg){
    cout << msg << endl;
    exit(1);
};

variant <dir, file> parse_line(string line) {
    int space_pos = line.find(' ');
    std::string name = line.substr(space_pos + 1);

    if (line[0] == 'd') {
        return dir{name};
    } else if (std::isdigit(line[0])) {
        auto size = stoi(line.substr(0, space_pos));

//      stoi(line.substr(0, space_pos))
        return file{name};
    }
    fail("Could not process line: " + line);
}

vector<string> open() {
    const string path = "../tinput.txt";
    ifstream input { path };
    if (!input.is_open()) fail("could not open: " + path);

    vector<string> lines;

    for(string line; getline(input, line);) {
        lines.push_back(line);
    }

    return lines;
}

auto make_tree() {
    auto lines = open();

    dir home{""};
    dir* cwd = &home;

    // skip initial "cd / "
    auto skip_ls = [](const string &line) { return line != "$ ls"; };
    const string CD_CMD = "$ cd ";
    const string GO_BACK = "$ cd ..";

    for (auto line: lines | std::views::drop(1) | std::views::filter(skip_ls)) {
        if (line == GO_BACK) {
            continue;
        }

        if (line.starts_with(CD_CMD)) {
            auto folder_name = line.substr(CD_CMD.length());

            for (auto c : cwd->contents) {
                if (std::holds_alternative<dir>(*c) && get<dir>(*c).name == folder_name) {
                    cwd = reinterpret_cast<dir*>(c.get());
                }
            }
        } else {
            auto node = parse_line(line);

            cwd->contents.push_back(move(make_unique<variant<dir,file>>(move(node))));
        }

    }
    home.print();
}

int main() {
    make_tree();

    return 0;
};
