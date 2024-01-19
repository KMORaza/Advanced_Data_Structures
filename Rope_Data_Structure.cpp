#include <iostream>
#include <string>
#include <vector>
class RopeNode {
public:
    char data;
    int weight;
    RopeNode* left;
    RopeNode* right;
    RopeNode(char c) : data(c), weight(1), left(nullptr), right(nullptr) {}
};
class Rope {
private:
    RopeNode* root;
    RopeNode* concatenate(RopeNode* left, RopeNode* right) {
        if (!left) return right;
        if (!right) return left;
        int totalWeight = left->weight + right->weight;
        if (rand() % totalWeight < left->weight) {
            left->right = concatenate(left->right, right);
            updateWeight(left);
            return left;
        } else {
            right->left = concatenate(left, right->left);
            updateWeight(right);
            return right;
        }
    }
    RopeNode* insert(RopeNode* node, char c, int index) {
        if (!node) {
            return new RopeNode(c);
        }
        int leftWeight = node->left ? node->left->weight : 0;
        if (index <= leftWeight) {
            node->left = insert(node->left, c, index);
        } else {
            node->right = insert(node->right, c, index - leftWeight - 1);
        }
        updateWeight(node);
        return node;
    }
    RopeNode* remove(RopeNode* node, int index) {
        if (!node) {
            return nullptr;
        }
        int leftWeight = node->left ? node->left->weight : 0;
        if (index < leftWeight) {
            node->left = remove(node->left, index);
        } else if (index > leftWeight) {
            node->right = remove(node->right, index - leftWeight - 1);
        } else {
            RopeNode* temp = concatenate(node->left, node->right);
            delete node;
            return temp;
        }
        updateWeight(node);
        return node;
    }
    void updateWeight(RopeNode* node) {
        node->weight = 1 + (node->left ? node->left->weight : 0) + (node->right ? node->right->weight : 0);
    }
    char atIndex(RopeNode* node, int index) const {
        if (!node) {
            throw std::out_of_range("Index out of range");
        }
        int leftWeight = node->left ? node->left->weight : 0;
        if (index < leftWeight) {
            return atIndex(node->left, index);
        } else if (index > leftWeight) {
            return atIndex(node->right, index - leftWeight - 1);
        } else {
            return node->data;
        }
    }
    void print(RopeNode* node) const {
        if (node) {
            print(node->left);
            std::cout << node->data;
            print(node->right);
        }
    }
public:
    Rope() : root(nullptr) {}
    void insert(char c, int index) {
        root = insert(root, c, index);
    }
    void remove(int index) {
        root = remove(root, index);
    }
    char atIndex(int index) const {
        return atIndex(root, index);
    }
    void concatenate(const Rope& other) {
        root = concatenate(root, other.root);
    }
    void print() const {
        print(root);
        std::cout << std::endl;
    }
};
int main() {
    Rope rope;
    rope.insert('a', 0);
    rope.insert('b', 1);
    rope.insert('c', 2);
    std::cout << "Rope after insertion: ";
    rope.print();
    rope.remove(1);
    std::cout << "Rope after removal: ";
    rope.print();
    rope.insert('d', 1);
    rope.insert('e', 2);
    std::cout << "Rope after more insertions: ";
    rope.print(); 
    return 0;
}
