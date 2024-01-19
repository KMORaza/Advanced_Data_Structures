#include <iostream>
#include <vector>
#include <stack>
struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;
    Node(int k, int p) : key(k), priority(p), left(nullptr), right(nullptr) {}
};
class CartesianTree {
private:
    Node* root;
public:
    CartesianTree() : root(nullptr) {}
    void insert(int key) {
        root = insertRecursive(root, key);
    }
    void inOrderTraversal() const {
        std::cout << "Cartesian Tree (In-Order): ";
        inOrderTraversalRecursive(root);
        std::cout << std::endl;
    }
    void preOrderTraversal() const {
        std::cout << "Cartesian Tree (Pre-Order): ";
        preOrderTraversalRecursive(root);
        std::cout << std::endl;
    }
    void postOrderTraversal() const {
        std::cout << "Cartesian Tree (Post-Order): ";
        postOrderTraversalRecursive(root);
        std::cout << std::endl;
    }
private:
    Node* insertRecursive(Node* root, int key) {
        if (root == nullptr) {
            return new Node(key, rand());
        }
        if (key < root->key) {
            root->left = insertRecursive(root->left, key);
        } else {
            Node* split;
            splitNode(root, key, split, root->right);
            root = split;
        }
        return root;
    }
    void splitNode(Node* root, int key, Node*& left, Node*& right) {
        if (root == nullptr) {
            left = right = nullptr;
        } else if (key < root->key) {
            splitNode(root->left, key, left, root->left);
            right = root;
        } else {
            splitNode(root->right, key, root->right, right);
            left = root;
        }
    }
    void inOrderTraversalRecursive(const Node* root) const {
        if (root) {
            inOrderTraversalRecursive(root->left);
            std::cout << root->key << " ";
            inOrderTraversalRecursive(root->right);
        }
    }
    void preOrderTraversalRecursive(const Node* root) const {
        if (root) {
            std::cout << root->key << " ";
            preOrderTraversalRecursive(root->left);
            preOrderTraversalRecursive(root->right);
        }
    }
    void postOrderTraversalRecursive(const Node* root) const {
        if (root) {
            postOrderTraversalRecursive(root->left);
            postOrderTraversalRecursive(root->right);
            std::cout << root->key << " ";
        }
    }
};
int main() {
    CartesianTree cartesianTree;
    cartesianTree.insert(3);
    cartesianTree.insert(1);
    cartesianTree.insert(4);
    cartesianTree.insert(2);
    cartesianTree.insert(5);
    cartesianTree.inOrderTraversal();
    cartesianTree.preOrderTraversal();
    cartesianTree.postOrderTraversal();
    return 0;
}
