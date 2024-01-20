#include <iostream>
#include <cassert>
class TopTree {
private:
    struct Node {
        int key;
        Node* parent;
        Node* left;
        Node* right;

        Node(int k) : key(k), parent(nullptr), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* link(Node* x, int k, Node* y) {
        Node* newNode = new Node(k);
        newNode->left = x;
        newNode->right = y;
        if (x != nullptr) x->parent = newNode;
        if (y != nullptr) y->parent = newNode;
        return newNode;
    }
    std::pair<Node*, Node*> split(Node* x, int k) {
        if (x == nullptr) {
            return {nullptr, nullptr};
        }
        if (x->key <= k) {
            auto [left, right] = split(x->right, k);
            x->right = left;
            if (left != nullptr) left->parent = x;
            return {x, right};
        } else {
            auto [left, right] = split(x->left, k);
            x->left = right;
            if (right != nullptr) right->parent = x;
            return {left, x};
        }
    }
    Node* join(Node* x, Node* y) {
        if (x == nullptr) return y;
        if (y == nullptr) return x;
        while (x->right != nullptr) {
            x = x->right;
        }
        return link(x, y->key, y->left);
    }
public:
    TopTree() : root(nullptr) {}
    void insert(int k) {
        auto [left, right] = split(root, k);
        root = link(left, k, right);
    }
    void remove(int k) {
        auto [left, right] = split(root, k);
        auto [mid, _] = split(right, k + 1);
        root = join(left, mid);
    }
    void inOrderTraversal(Node* x) {
        if (x != nullptr) {
            inOrderTraversal(x->left);
            std::cout << x->key << " ";
            inOrderTraversal(x->right);
        }
    }
    void inOrder() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
};
int main() {
    TopTree topTree;
    topTree.insert(10);
    topTree.insert(5);
    topTree.insert(15);
    topTree.insert(2);
    topTree.insert(7);
    std::cout << "Top Tree: ";
    topTree.inOrder();
    topTree.remove(5);
    std::cout << "After removing 5: ";
    topTree.inOrder();
    return 0;
}
