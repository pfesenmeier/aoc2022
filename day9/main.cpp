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

    ~pos() {}

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

struct link {
    link(pos &first, pos &second) : first(first), second(second) {}

    pos &first;
    pos &second;

    bool dx(int dist) {
        return first.x == second.x + dist;
    };

    bool dy(int dist) {
        return first.y == second.y + dist;
    };
};

class rope {
    pos H = pos(0, 0);
    vector<pos> T;

    static bool nnn(link l) { return l.dx(+0) && l.dy(+2); };

    static bool nne(link l) { return l.dx(+1) && l.dy(+2); };

    static bool ne(link l) { return l.dx(+2) && l.dy(+2); };

    static bool ene(link l) { return l.dx(+2) && l.dy(+1); };

    static bool eee(link l) { return l.dx(+2) && l.dy(+0); };

    static bool ese(link l) { return l.dx(+2) && l.dy(-1); };

    static bool se(link l) { return l.dx(+2) && l.dy(-2); };

    static bool sse(link l) { return l.dx(+1) && l.dy(-2); };

    static bool sss(link l) { return l.dx(+0) && l.dy(-2); };

    static bool ssw(link l) { return l.dx(-1) && l.dy(-2); };

    static bool sw(link l) { return l.dx(-2) && l.dy(-2); };

    static bool wsw(link l) { return l.dx(-2) && l.dy(-1); };

    static bool www(link l) { return l.dx(-2) && l.dy(0); };

    static bool wnw(link l) { return l.dx(-2) && l.dy(+1); };

    static bool nw(link l) { return l.dx(-2) && l.dy(+2); };

    static bool nnw(link l) { return l.dx(-1) && l.dy(+2); };

    static bool ccc(link l) { return l.dx(+0) && l.dy(+0); };

    void change_T(pos &p, int x, int y) {
        p.x += x;
        p.y += y;
    }

    void change_H(int x, int y) {
        H.x += x;
        H.y += y;
    }

    void scrunch(link &l) {
        if (nnn(l)) change_T(l.second, 0, 1);
        if (nne(l)) change_T(l.second, 1, 1);
        if (ne(l)) change_T(l.second, 1, 1);
        if (ene(l)) change_T(l.second, 1, 1);
        if (eee(l)) change_T(l.second, 1, 0);
        if (ese(l)) change_T(l.second, 1, -1);
        if (se(l)) change_T(l.second, 1, -1);
        if (sse(l)) change_T(l.second, 1, -1);
        if (sss(l)) change_T(l.second, 0, -1);
        if (ssw(l)) change_T(l.second, -1, -1);
        if (sw(l)) change_T(l.second, -1, -1);
        if (wsw(l)) change_T(l.second, -1, -1);
        if (www(l)) change_T(l.second, -1, 0);
        if (wnw(l)) change_T(l.second, -1, 1);
        if (nw(l)) change_T(l.second, -1, 1);
        if (nnw(l)) change_T(l.second, -1, 1);
        if (ccc(l)) change_T(l.second, 0, 0);
    }

    void move_tail() {
        link neck{H, T[0]};
        scrunch(neck);

        int size = T.size() - 1;
        for (int i: views::iota(0, size)) {
            link l{T[i], T[i + 1]};
            scrunch(l);
        }
    };

public:
    int len;

    rope(pos initial, int length) : H(initial.x, initial.y), T(), len(length) {
        for (auto i: views::iota(0, length - 1)) {
            T.emplace_back(pos(initial.x, initial.y));
        }
    }

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

    tuple<int, int> tail(int name) {
        return T.at(name - 1).get();
    }
};

class grid {
    map<tuple<int, int>, bool> g;
    pos start;
public:
    rope r;

    grid(pos initial, int length) : g(), r(initial, length), start(initial.x, initial.y) {}

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
            g[r.tail(r.len - 1)] = true;

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
        auto h = r.head();
        for (auto i = 0; i > -5; i--) {
            for (auto j: views::iota(0, 6)) {
                if (tie(j, i) == h) {
                    cout << 'H';
                    continue;
                }

                for (auto k = 1; k < r.len; k++) {
                    auto t = r.tail(k);
                    if (tie(j, i) == t) {
                        cout << k;
                        goto cont;
                    }
                }

                if (tie(j, i) == start.get()) {
                    cout << 's';
                } else if (g[tie(j, i)]) {
                    cout << '#';
                } else {
                    cout << '_';
                }
                cont:;
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
    auto g = grid(pos(0, -4), 10);

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
    auto g = grid(pos(0, -4), 10);

    g.print();

    g.exec(cmd('R', 4));
    expect(g.r.tail(1), 3, -4);

    g.exec(cmd('U', 4));
    expect(g.r.tail(1), 4, -1);

    g.exec(cmd('L', 3));
    expect(g.r.tail(1), 2, 0);

    g.exec(cmd('D', 1));
    expect(g.r.tail(1), 2, 0);

    g.exec(cmd('R', 4));
    expect(g.r.tail(1), 4, -1);

    g.exec(cmd('D', 1));
    expect(g.r.tail(1), 4, -1);

    g.exec(cmd('L', 5));
    expect(g.r.tail(1), 1, -2);

    g.exec(cmd('R', 2));
    expect(g.r.tail(1), 1, -2);
}

int main() {
//    test1();
    part1();
}
