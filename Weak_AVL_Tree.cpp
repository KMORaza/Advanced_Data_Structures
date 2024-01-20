#include <iostream>
#include <algorithm>
class WeakAVLTree {
private:
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;
        Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    int getHeight(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }
    void updateHeight(Node* node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }
    int getBalanceFactor(Node* node) {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }
    Node* balance(Node* node) {
        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }
    Node* insertRecursive(Node* root, int key) {
        if (root == nullptr) {
            return new Node(key);
        }
        if (key < root->key) {
            root->left = insertRecursive(root->left, key);
        } else if (key > root->key) {
            root->right = insertRecursive(root->right, key);
        } else {
            return root;
        }
        return balance(root);
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
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = (root->left != nullptr) ? root->left : root->right;
                delete root;
                return temp;
            } else {
                Node* temp = findMin(root->right);
                root->key = temp->key;
                root->right = deleteRecursive(root->right, temp->key);
            }
        }
        return balance(root);
    }
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node* searchRecursive(Node* root, int key) {
        if (root == nullptr || root->key == key) {
            return root;
        }
        if (key < root->key) {
            return searchRecursive(root->left, key);
        }
        return searchRecursive(root->right, key);
    }
    void inOrderTraversal(Node* root) {
        if (root) {
            inOrderTraversal(root->left);
            std::cout << root->key << " ";
            inOrderTraversal(root->right);
        }
    }
public:
    WeakAVLTree() : root(nullptr) {}
    void insert(int key) {
        root = insertRecursive(root, key);
    }
    void remove(int key) {
        root = deleteRecursive(root, key);
    }
    bool search(int key) {
        return (searchRecursive(root, key) != nullptr);
    }
    void inOrder() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
};
int main() {
    WeakAVLTree wavl;
    wavl.insert(10);
    wavl.insert(5);
    wavl.insert(15);
    wavl.insert(2);
    wavl.insert(7);
    std::cout << "Weak AVL Tree (in-order): ";
    wavl.inOrder();
    wavl.remove(5);
    std::cout << "After removing 5 (in-order): ";
    wavl.inOrder();
    std::cout << "Search for key 7: " << (wavl.search(7) ? "Found" : "Not Found") << std::endl;
    return 0;
}
