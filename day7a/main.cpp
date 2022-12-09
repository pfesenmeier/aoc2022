#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <optional>
#include <variant>
#include <fstream>
#include <ranges>

const int MAX = 100000;

using namespace std;

class dir;

class file {
public:
    explicit file(string name, int size) : name(std::move(name)), size(size) {}

    dir* parent;
    string name;
    int size;
};

class dir {
public:
    explicit dir(string name) : name(std::move(name)), contents(), size(0) {}

    string name;
    vector<shared_ptr<variant<dir, file>>> contents;
    dir* parent;
    int size;

    void add(variant<dir, file> node) {
        contents.push_back(move(make_unique<variant<dir, file>>(move(node))));
    }

    void print() {
        print_recurse();
    }

    void print_recurse(int depth = 0) {
        auto space = string(4 * depth, ' ');
        cout << space << name << '/' << " (" << size << ")" << endl;
        for (auto&& c: contents) {
            if (holds_alternative<file>(*c)) {
                cout << space << "    " << get<file>(*c).name;
                cout << " (" << get<file>(*c).size << ")" << endl;
            } else if (holds_alternative<dir>(*c)) {
                get<dir>(*c).print_recurse(depth + 1);
            }
        }
    }
};

int get_size(dir& d, int& answer) {
    int size = 0;
    for (auto c: d.contents) {
        if (holds_alternative<file>(*c)) {
            size += get<file>(*c).size;
        }

        if (holds_alternative<dir>(*c)) {
            size += get_size(get<dir>(*c), answer);
        }
    }
    d.size = size;

    if (size < MAX) {
        answer += size;
    }

    return size;
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
        return file{name, stoi(line.substr(0, space_pos))};
    }
    fail("Could not process line: " + line);
}

vector<string> open() {
    const string path = "../input.txt";
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
            cwd = cwd->parent;
        } else if (line.starts_with(CD_CMD)) {
            auto folder_name = line.substr(CD_CMD.length());

            for (auto c : cwd->contents) {
                if (std::holds_alternative<dir>(*c) && get<dir>(*c).name == folder_name) {
                    cwd = reinterpret_cast<dir*>(c.get());
                }
            }
        } else {
            auto node = parse_line(line);
            if (holds_alternative<file>(node)) {
                get<file>(node).parent = cwd;
            } else {
                get<dir>(node).parent = cwd;
            }

            cwd->contents.push_back(move(make_unique<variant<dir,file>>(move(node))));
        }

    }

    cwd = &home;


    auto check_if_small = [](dir d) {

        return false;
    };

    int answer = 0;
    get_size(home, answer);
//    int answer = 0;
//    for(auto child: cwd->contents) {
//        if (holds_alternative<dir>(*child)) {
//            auto size = get_size(get<dir>(*child));
//            get<dir>(*child).size = size;
//        }
//    }

    home.print();
    cout << "Answer: " << answer << endl;
}

int main() {
    make_tree();

    return 0;
};
