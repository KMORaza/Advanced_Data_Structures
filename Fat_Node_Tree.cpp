#include <iostream>
class FatNode {
public:
    int key;
    int size; 
    FatNode* left;
    FatNode* right;
    FatNode(int k) : key(k), size(1), left(nullptr), right(nullptr) {}
};
class FatNodeTree {
private:
    FatNode* root;
    FatNode* insert(FatNode* node, int key) {
        if (!node) {
            return new FatNode(key);
        }
        node->size++;
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }
        return node;
    }
    int kthSmallest(FatNode* node, int k) const {
        if (!node) {
            return -1; 
        }
        int leftSize = (node->left) ? node->left->size : 0;
        if (k == leftSize + 1) {
            return node->key; 
        } else if (k <= leftSize) {
            return kthSmallest(node->left, k);
        } else {
            return kthSmallest(node->right, k - leftSize - 1);
        }
    }
    int rank(FatNode* node, int key) const {
        if (!node) {
            return -1; 
        }
        if (key == node->key) {
            return (node->left) ? node->left->size + 1 : 1; 
        } else if (key < node->key) {
            return rank(node->left, key);
        } else {
            int rightRank = rank(node->right, key);
            return (rightRank != -1) ? rightRank + ((node->left) ? node->left->size + 1 : 1) : -1;
        }
    }
public:
    FatNodeTree() : root(nullptr) {}
    void insert(int key) {
        root = insert(root, key);
    }
    int kthSmallest(int k) const {
        return kthSmallest(root, k);
    }
    int rank(int key) const {
        return rank(root, key);
    }
};
int main() {
    FatNodeTree fatNodeTree;
    fatNodeTree.insert(50);
    fatNodeTree.insert(30);
    fatNodeTree.insert(70);
    fatNodeTree.insert(20);
    fatNodeTree.insert(40);
    fatNodeTree.insert(60);
    fatNodeTree.insert(80);
    std::cout << "3rd smallest element: " << fatNodeTree.kthSmallest(3) << std::endl;
    std::cout << "Rank of 40: " << fatNodeTree.rank(40) << std::endl;
    return 0;
}
