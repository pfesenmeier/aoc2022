#include <ostream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void fail(const string &output) {
    cout << output << endl;
    exit(1);

}

void print_woods(auto woods) {
    for (auto row: woods) {
        for (auto tree: row) {
            cout << tree;
        }
        cout << endl;
    }
}

void part2() {
    ifstream input{"../input.txt"};
    if (!input.is_open()) fail("no file");

    vector<vector<int>> woods;

    for (string line; getline(input, line);) {
        vector<int> row;
        for (char tree: line) {
            row.push_back(tree - '0');
        }
        woods.push_back(row);
    }

    auto wwidth = woods[0].size();
    auto wlength = woods.size();

    auto get_tree = [woods](auto x, auto y) {
        return woods[y][x];
    };

    auto vert_score = [woods, wlength, get_tree](auto x, auto y) {
        auto tree_height = get_tree(x, y);

        int top = 0;
        for (auto i = y - 1; i > -1; i--) {
            auto neighbor_height = get_tree(x, i);
            if (neighbor_height < tree_height) {
                top++;
            } else {
                top++;
                break;
            }
        }

        auto bottom = 0;
        for (auto i = y + 1; i < wlength; i++) {
            bottom++;
            if (get_tree(x, i) >= tree_height) {
                break;
            }
        }

        return top * bottom;
    };

    auto horiz_score = [woods, wwidth, get_tree](auto x, auto y) {
        auto tree_height = get_tree(x, y);

        int left = 0;
        if (x > 0) {
            for (auto i = x - 1; i > -1; i--) {
                left++;
                if (get_tree(i, y) >= tree_height) {
                    break;
                }
            }
        }

        int right = 0;
        if (x < wwidth - 1) {
            for (auto i = x + 1; i < wwidth; i++) {
                right++;
                if (get_tree(i, y) >= tree_height) {
                    break;
                }
            }
        }

        return left * right;
    };

    auto check = [horiz_score, vert_score](auto x, auto y) {
        return horiz_score(x, y) * vert_score(x, y);
    };

    auto answer = 0;
    for (auto i = 0; i < wlength; i++) {
        for (auto j = 0; j < wwidth; j++) {
            int score = check(j, i);

            if (score > answer) {
                answer = score;
            }
        }
    }

    cout << answer << endl;
}

void part1() {
    ifstream input{"../input.txt"};
    if (!input.is_open()) fail("no file");

    vector<vector<int>> woods;

    for (string line; getline(input, line);) {
        vector<int> row;
        for (char tree: line) {
            row.push_back(tree - '0');
        }
        woods.push_back(row);
    }

    print_woods(woods);


    auto wwidth = woods[0].size();
    auto wlength = woods.size();

    auto get_tree = [woods](auto x, auto y) {
        return woods[y][x];
    };

    auto check_vert = [woods, wlength, get_tree](auto x, auto y) {
        auto tree_height = get_tree(x, y);

        auto top = true;
        for (auto i = 0; i < y; i++) {
            if (get_tree(x, i) >= tree_height) {
                top = false;
            }
        }

        auto bottom = true;
        for (auto i = y + 1; i < wlength; i++) {
            if (get_tree(x, i) >= tree_height) {
                bottom = false;
            }
        }

        return top || bottom;
    };

    auto check_horiz = [woods, wwidth, get_tree](auto x, auto y) {
        auto tree_height = get_tree(x, y);

        bool left = true;
        for (auto i = 0; i < x; i++) {
            if (get_tree(i, y) >= tree_height) {
                left = false;
            }
        }

        bool right = true;
        for (auto i = x + 1; i < wwidth; i++) {
            if (get_tree(i, y) >= tree_height) {
                right = false;
            }
        }

        return left || right;
    };

    auto check = [check_horiz, check_vert](auto x, auto y) {
        return check_horiz(x, y) || check_vert(x, y);
    };

    vector<vector<char>> viz_map;
    auto answer = 0;
    for (auto i = 0; i < wlength; i++) {
        vector<char> viz_row;
        for (auto j = 0; j < wwidth; j++) {
            if (check(j, i)) {
                viz_row.push_back('X');
                answer += 1;
            } else {
                viz_row.push_back('_');
            }
        }
        viz_map.push_back(viz_row);
    }

    print_woods(viz_map);
    cout << answer << endl;
}

int main() {
    part1();
    part2();

    return 0;
}
