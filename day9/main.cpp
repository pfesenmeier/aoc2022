#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ranges>


using namespace std;

struct cmd {
    cmd(char dir, int amt) : dir(dir), amt(amt) {}

    char dir;
    int amt;

    void print() {
        cout << "== " << dir << " " << amt << " ==" << endl;
        cout << endl;
    }
};

struct pos {
    pos(int x, int y) : x(x), y(y) {}

    int x;
    int y;

    void set(int x, int y) {
        x = x;
        y = y;
    }

    tuple<int, int> get() {
        return {x, y};
    }
};

class rope {
    pos H = pos(0, 0);
    pos T = pos(0, 0);

    bool dx(int dist) {
        if (dist == 0) {
            return H.x == T.x;
        }
        return H.x == T.x + dist;
    };

    bool dy(int dist) {
        if (dist == 0) {
            return H.y == T.y;
        }
        return H.y == T.y + dist;
    };

    bool nnn() { return dx(+0) && dy(+2); };

    bool nne() { return dx(+1) && dy(+2); };

    bool ene() { return dx(+2) && dy(+1); };

    bool eee() { return dx(+2) && dy(+0); };

    bool ese() { return dx(+2) && dy(-1); };

    bool sse() { return dx(+1) && dy(-2); };

    bool sss() { return dx(+0) && dy(-2); };

    bool ssw() { return dx(-1) && dy(-2); };

    bool wsw() { return dx(-2) && dy(-1); };

    bool www() { return dx(-2) && dy(0); };

    bool wnw() { return dx(-2) && dy(+1); };

    bool nnw() { return dx(-1) && dy(+2); };

    bool ccc() { return dx(+0) && dy(+0); };

    void change_T(int x, int y) {
        T.x += x;
        T.y += y;
    }

    void change_H(int x, int y) {
        H.x += x;
        H.y += y;
    }

    void move_tail() {
        if (nnn()) change_T(0, 1);
        if (nne()) change_T(1, 1);
        if (ene()) change_T(1, 1);
        if (eee()) change_T(1, 0);
        if (ese()) change_T(1, -1);
        if (sse()) change_T(1, -1);
        if (sss()) change_T(0, -1);
        if (ssw()) change_T(-1, -1);
        if (wsw()) change_T(-1, -1);
        if (www()) change_T(-1, 0);
        if (wnw()) change_T(-1, 1);
        if (nnw()) change_T(-1, 1);
        if (ccc()) change_T(0, 0);
    };

public:
    rope(int x, int y) : H(x, y), T(x, y) {}

    void left() {
        change_H(-1, 0);
        move_tail();
    }

    void right() {
        change_H(1, 0);
        move_tail();
    };

    void up() {
        change_H(0, 1);
        move_tail();
    };

    void down() {
        change_H(0, -1);
        move_tail();
    };

    tuple<int, int> head() {
        return H.get();
    }

    tuple<int, int> tail() {
        return T.get();
    }
};

class grid {
    map<tuple<int, int>, bool> g;
    int x = 0;
    int y = 0;
    pos start;
public:
    rope r;

    grid(int x, int y) : g(), r(x, y), start(x, y) {}

    void exec(cmd c) {
        c.print();
        for (int i: views::iota(0, c.amt)) {
            switch (c.dir) {
                case 'R':
                    r.right();
                    break;
                case 'L':
                    r.left();
                    break;
                case 'U':
                    r.up();
                    break;
                case 'D':
                    r.down();
                    break;
            }
            g[r.tail()] = true;
            print();
        }

    }

    void solve1() {
        auto answer = 0;
        for (auto const &[_, visited]: g) {
            if (visited) answer += 1;
        }
        cout << "Answer to part 1: " << endl;
        cout << answer << endl;
    }

    void print() {
        auto t = r.tail();
        auto h = r.head();
        for (auto i = 0; i > -5; i--) {
            for (auto j: views::iota(0, 6)) {
                if (tie(j, i) == h) {
                    cout << 'H';
                } else if (tie(j, i) == t) {
                    cout << 'T';
                } else if (tie(j, i) == start.get()) {
                    cout << 's';
                } else if (g[tie(j, i)]) {
                    cout << '#';
                } else {
                    cout << '_';

                }
            }
            cout << endl;
        }
        cout << endl;
    };
};

vector<cmd> open(bool test) {
    auto path = test ? "../tinput.txt" : "../input.txt";
    std::ifstream input{path};
    if (!input.is_open()) {
        cout << "Could not open: " << path << endl;
        exit(1);
    }

    vector<cmd> lines;
    for (string line; getline(input, line);) {
        lines.push_back(cmd(line[0], stoi(line.substr(2))));
    }

    return lines;
}

void part1() {
    auto cmds = open(false);
    auto g = grid(0, -4);

    g.print();
    for (auto cmd: cmds) {
        cmd.print();
        g.exec(cmd);
    }

    g.solve1();
}

void expect(tuple<int, int> p, int x, int y) {
    int px;
    int py;
    tie(px, py) = p;
    if (tie(x, y) != p) {
        cout << "Expected: " << x << ", " << y << endl;
        cout << "Received: " << px << ", " << py << endl;
        exit(1);
    }
}

void test1() {
    auto g = grid(0, -4);

    g.print();

    g.exec(cmd('R', 4));
    expect(g.r.tail(), 3, -4);

    g.exec(cmd('U', 4));
    expect(g.r.tail(), 4, -1);

    g.exec(cmd('L', 3));
    expect(g.r.tail(), 2, 0);

    g.exec(cmd('D', 1));
    expect(g.r.tail(), 2, 0);

    g.exec(cmd('R', 4));
    expect(g.r.tail(), 4, -1);

    g.exec(cmd('D', 1));
    expect(g.r.tail(), 4, -1);

    g.exec(cmd('L', 5));
    expect(g.r.tail(), 1, -2);

    g.exec(cmd('R', 2));
    expect(g.r.tail(), 1, -2);
}

int main() {
//    test1();
   part1();
}
