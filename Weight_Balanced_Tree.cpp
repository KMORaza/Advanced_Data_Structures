#include <iostream>
#include <cstdlib>
class WeightBalancedTree {
private:
    struct Node {
        int key;
        int priority;
        Node* left;
        Node* right;
        Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    Node* insertRecursive(Node* root, int key) {
        if (root == nullptr) {
            return new Node(key);
        }
        if (key < root->key) {
            root->left = insertRecursive(root->left, key);
            if (root->left->priority > root->priority) {
                root = rotateRight(root);
            }
        } else {
            root->right = insertRecursive(root->right, key);
            if (root->right->priority > root->priority) {
                root = rotateLeft(root);
            }
        }
        return root;
    }
    Node* deleteRecursive(Node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (key < root->key) {
            root->left = deleteRecursive(root->left, key);
        } else if (key > root->key) {
            root->right = deleteRecursive(root->right, key);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            if (root->left->priority > root->right->priority) {
                root = rotateRight(root);
                root->right = deleteRecursive(root->right, key);
            } else {
                root = rotateLeft(root);
                root->left = deleteRecursive(root->left, key);
            }
        }
        return root;
    }
    void inOrderTraversal(Node* root) {
        if (root) {
            inOrderTraversal(root->left);
            std::cout << root->key << " ";
            inOrderTraversal(root->right);
        }
    }
    void preOrderTraversal(Node* root) {
        if (root) {
            std::cout << root->key << " ";
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
        }
    }
    void postOrderTraversal(Node* root) {
        if (root) {
            postOrderTraversal(root->left);
            postOrderTraversal(root->right);
            std::cout << root->key << " ";
        }
    }
public:
    WeightBalancedTree() : root(nullptr) {}
    void insert(int key) {
        root = insertRecursive(root, key);
    }
    void remove(int key) {
        root = deleteRecursive(root, key);
    }
    void inOrder() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
    void preOrder() {
        preOrderTraversal(root);
        std::cout << std::endl;
    }
    void postOrder() {
        postOrderTraversal(root);
        std::cout << std::endl;
    }
};
int main() {
    WeightBalancedTree wbt;
    wbt.insert(10);
    wbt.insert(5);
    wbt.insert(15);
    wbt.insert(2);
    wbt.insert(7);
    wbt.insert(12);
    wbt.insert(20);
    std::cout << "In-order traversal: ";
    wbt.inOrder();
    std::cout << "Pre-order traversal: ";
    wbt.preOrder();
    std::cout << "Post-order traversal: ";
    wbt.postOrder();
    wbt.remove(5);
    std::cout << "After removing 5:" << std::endl;
    std::cout << "In-order traversal: ";
    wbt.inOrder();
    return 0;
}
