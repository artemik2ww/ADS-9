// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "tree.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::vector<std::vector<char>> perms = getAllPerms(tree);
    for (size_t i = 0; i < perms.size(); ++i) {
        std::cout << i + 1 << ": ";
        for (size_t j = 0; j < perms[i].size(); ++j) {
            std::cout << perms[i][j];
        }
        std::cout << std::endl;
    }

    std::vector<char> p1 = getPerm1(tree, 2);
    std::vector<char> p2 = getPerm2(tree, 2);

    for (char c : p1) std::cout << c;
    for (char c : p2) std::cout << c;
    std::cout << std::endl;

    return 0;
}
