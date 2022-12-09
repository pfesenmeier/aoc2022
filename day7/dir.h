//
// Created by pfese on 12/7/2022.
//

#ifndef DAY7_DIR_H
#define DAY7_DIR_H

#include <utility>
#include <variant>
#include <vector>
#include <string>
#include <memory>

struct file {
public:
    file(int s, std::string n) : size(s), name(std::move(n)) {}

    int size;
    std::string name;
};

class dir {
public:
    dir(std::string n, std::shared_ptr<dir> p) : name(std::move(n)), size_contents(0), parent(p) {
        std::vector<std::unique_ptr<std::variant<dir, file>>> c;
        contents = c;
    };

    void add(std::variant<dir, file> n);

    std::shared_ptr<dir> find_folder(std::string n);

    std::string name;

    int get_size();
    std::shared_ptr<dir> get_parent();
//    int sum_small_folders();

    static std::variant<dir, file> parse(std::string line, std::shared_ptr<dir> d);
    std::vector<std::unique_ptr<std::variant<dir, file>>> contents;
    int size_contents;
    std::shared_ptr<dir> parent;
private:
};

class file_browser {
public:
    file_browser() : tree("/", nullptr), cwd(&tree), home(&tree) {};
    void move(std::string path);
    void add(std::string node);
    int sum_small_folders();
    dir tree;
    std::shared_ptr<dir> cwd;
    std::shared_ptr<dir> home;
private:
};

#endif //DAY7_DIR_H
