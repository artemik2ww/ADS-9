// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

struct Node {
    char val;
    std::vector<Node*> children;

    explicit Node(char c) : val(c) {}
};

class PMTree {
 private:
    Node* root;

    void buildTree(Node* currentNode, std::vector<char> remainingChars) {
        if (remainingChars.empty()) {
            return;
        }

        for (size_t i = 0; i < remainingChars.size(); ++i) {
            Node* child = new Node(remainingChars[i]);
            currentNode->children.push_back(child);

            std::vector<char> nextRemaining;
            for (size_t j = 0; j < remainingChars.size(); ++j) {
                if (i != j) {
                    nextRemaining.push_back(remainingChars[j]);
                }
            }
            buildTree(child, nextRemaining);
        }
    }

    void clearTree(Node* node) {
        if (node == nullptr) return;
        for (size_t i = 0; i < node->children.size(); ++i) {
            clearTree(node->children[i]);
        }
        delete node;
    }

 public:
    explicit PMTree(std::vector<char> in) {
        for (size_t i = 0; i < in.size(); ++i) {
            for (size_t j = i + 1; j < in.size(); ++j) {
                if (in[i] > in[j]) {
                    char temp = in[i];
                    in[i] = in[j];
                    in[j] = temp;
                }
            }
        }

        root = new Node('*');
        buildTree(root, in);
    }

    ~PMTree() {
        clearTree(root);
    }

    Node* getRoot() const {
        return root;
    }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
