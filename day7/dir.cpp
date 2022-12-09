//
// Created by pfese on 12/7/2022.
//

#include "dir.h"
#include <string>
#include <iostream>
#include <ranges>
#include <numeric>
#include <memory>

constexpr int MAX_SIZE = 100000;

int dir::get_size() {
//    if (size_contents) {
//        return size_contents;
//    }
    std::cout << "Name: " << name << std::endl;
    std::cout << "Contents length: " << contents.size() << std::endl;

    int size2 = 0;
    for (auto& node: contents) {
        if (std::holds_alternative<file>(*node)) {
            auto f = get<file>(*node);
            size2 += get<file>(*node).size;
        } else if (std::holds_alternative<dir>(*node)) {
            auto d = get<dir>(*node);
            int s = d.get_size();
            std::cout << "    Size of dir " << d.name << " : " << s << std::endl;
            size2 += s;
        } else {
            std::cout << "Could not parse content\n";
            exit(1);
        }
    }

    std::cout << "aggregate " << name << ": " << size2 << std::endl;

    return size2;
}

void dir::add(std::variant <dir, file> n) {
    std::cout << "Add. Name: " << name << std::endl;
    std::cout << "Before contents length: " << contents.size() << std::endl;
    auto ptr = std::make_unique<std::variant<dir,file>>(n);
    this->contents.push_back(std::move(ptr));
    std::cout << "After contents length: " << contents.size() << std::endl;
}

std::variant <dir, file> dir::parse(std::string line, std::shared_ptr <dir> d) {
    int space_pos = line.find(' ');
    std::string name = line.substr(space_pos + 1);

    if (line[0] == 'd') {
        return dir{name, d};
    } else if (std::isdigit(line[0])) {
        std::cout << "Name" << name << std::endl;
        auto size = stoi(line.substr(0, space_pos));
        std::cout << "Size: " << size << std::endl;

        std::cout << "Line: " << line << std::endl;
        return file{stoi(line.substr(0, space_pos)), name};
    }
    std::cout << "Could not process line: " << line << std::endl;

    exit(1);
}

std::shared_ptr <dir> dir::get_parent() {
    auto p = parent;
    return p;
}

std::shared_ptr <dir> dir::find_folder(std::string n) {
    for (auto& node: contents) {
        if (std::holds_alternative<dir>(*node) && get<dir>(*node).name == n) {
            return std::make_unique<dir>(get<dir>(*node));
        }
    }

    std::cout << "Could not find folder: " << n << std::endl;
    exit(1);

    return nullptr;
}

//int dir::sum_small_folders() {
//    std::vector<int> small_sizes;
//    for (auto node: contents) {
//        if(std::holds_alternative<dir>(node)) {
//            int size_n = get<dir>(node).get_size();
//            if(size_n < MAX_SIZE) {
//                small_sizes.push_back(size_n);
//            }
//        }
//    }
//
//    return std::accumulate(small_sizes.begin(), small_sizes.end(), 0);
//}

void file_browser::move(std::string path) {
    if (path == "..") {
        auto p = cwd->get_parent();
        cwd.swap(p);
    } else {
        auto next = cwd->find_folder(path);

        if (next == nullptr) {
            std::cout << "Asked to move into nonexistent folder : " << path << std::endl;
            exit(1);
        }

        cwd.swap(next);
    }
}

void file_browser::add(std::string line) {
    auto node = dir::parse(line, cwd);
    std::cout << "Before: " << cwd->contents.size() << std::endl;
    cwd->add(std::move(node));
    std::cout << "After: " << cwd->contents.size() << std::endl;
}

int file_browser::sum_small_folders() {
    std::vector<int> small_sizes;

    auto home_size = home->get_size();

//    for (auto node: home->contents) {
//        if(std::holds_alternative<dir>(node)) {
//            int size_n = get<dir>(node).get_size();
//            if(size_n < MAX_SIZE) {
//                small_sizes.push_back(size_n);
//            }
//        }
//    }

//    return std::accumulate(small_sizes.begin(), small_sizes.end(), 0);
    return home_size;
}
