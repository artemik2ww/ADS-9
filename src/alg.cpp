// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include "tree.h"

void collectPermutations(Node* node, std::vector<char>& currentPath,
                         std::vector<std::vector<char>>& allPerms) {
    if (node == nullptr) return;

    if (node->val != '*') {
        currentPath.push_back(node->val);
    }

    if (node->children.empty() && node->val != '*') {
        allPerms.push_back(currentPath);
    } else {
        for (size_t i = 0; i < node->children.size(); ++i) {
            collectPermutations(node->children[i], currentPath, allPerms);
        }
    }

    if (node->val != '*') {
        currentPath.pop_back();
    }
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> allPerms;
    std::vector<char> currentPath;
    collectPermutations(tree.getRoot(), currentPath, allPerms);
    return allPerms;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<std::vector<char>> allPerms = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(allPerms.size())) {
        return std::vector<char>();
    }
    return allPerms[num - 1];
}

int calculateFactorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    std::vector<char> result;
    Node* current = tree.getRoot();

    if (current == nullptr || current->children.empty()) {
        return result;
    }

    int k = num - 1;
    int totalPerms = calculateFactorial(static_cast<int>(current->children.size()));

    if (k < 0 || k >= totalPerms) {
        return std::vector<char>();
    }

    while (!current->children.empty()) {
        int branchCount = static_cast<int>(current->children.size());
        int permsPerBranch = totalPerms / branchCount;

        int index = k / permsPerBranch;
        current = current->children[index];

        result.push_back(current->val);

        k = k % permsPerBranch;
        totalPerms = permsPerBranch;
    }

    return result;
}
