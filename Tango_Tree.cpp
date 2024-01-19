#include <iostream>
class TangoTreeNode {
public:
    int key;
    TangoTreeNode* left;
    TangoTreeNode* right;
    int size; 
    TangoTreeNode(int k) : key(k), left(nullptr), right(nullptr), size(1) {}
};
class TangoTree {
private:
    TangoTreeNode* root;
public:
    TangoTree() : root(nullptr) {}
    void insert(int key) {
        root = insertRecursive(root, key);
    }
    bool search(int key) const {
        return searchRecursive(root, key);
    }
    void inOrderTraversal() const {
        std::cout << "In-order traversal: ";
        inOrderTraversalRecursive(root);
        std::cout << std::endl;
    }
    void preOrderTraversal() const {
        std::cout << "Pre-order traversal: ";
        preOrderTraversalRecursive(root);
        std::cout << std::endl;
    }
    void postOrderTraversal() const {
        std::cout << "Post-order traversal: ";
        postOrderTraversalRecursive(root);
        std::cout << std::endl;
    }
private:
    TangoTreeNode* insertRecursive(TangoTreeNode* node, int key) {
        if (node == nullptr) {
            return new TangoTreeNode(key);
        }
        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        } else {
            node->right = insertRecursive(node->right, key);
        }
        updateSize(node);
        return balance(node);
    }
    bool searchRecursive(TangoTreeNode* node, int key) const {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return searchRecursive(node->left, key);
        } else {
            return searchRecursive(node->right, key);
        }
    }
    void inOrderTraversalRecursive(const TangoTreeNode* node) const {
        if (node) {
            inOrderTraversalRecursive(node->left);
            std::cout << node->key << " ";
            inOrderTraversalRecursive(node->right);
        }
    }
    void preOrderTraversalRecursive(const TangoTreeNode* node) const {
        if (node) {
            std::cout << node->key << " ";
            preOrderTraversalRecursive(node->left);
            preOrderTraversalRecursive(node->right);
        }
    }
    void postOrderTraversalRecursive(const TangoTreeNode* node) const {
        if (node) {
            postOrderTraversalRecursive(node->left);
            postOrderTraversalRecursive(node->right);
            std::cout << node->key << " ";
        }
    }
    void updateSize(TangoTreeNode* node) {
        if (node) {
            node->size = 1;
            if (node->left) {
                node->size += node->left->size;
            }
            if (node->right) {
                node->size += node->right->size;
            }
        }
    }
    TangoTreeNode* balance(TangoTreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (getSize(node->left) > 2 * getSize(node->right)) {
            if (getSize(node->left->left) < getSize(node->left->right)) {
                node->left = rotateLeft(node->left);
            }
            node = rotateRight(node);
        } else if (getSize(node->right) > 2 * getSize(node->left)) {
            if (getSize(node->right->right) < getSize(node->right->left)) {
                node->right = rotateRight(node->right);
            }
            node = rotateLeft(node);
        }
        return node;
    }
    TangoTreeNode* rotateRight(TangoTreeNode* node) {
        TangoTreeNode* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateSize(node);
        updateSize(newRoot);
        return newRoot;
    }
    TangoTreeNode* rotateLeft(TangoTreeNode* node) {
        TangoTreeNode* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateSize(node);
        updateSize(newRoot);
        return newRoot;
    }
    int getSize(const TangoTreeNode* node) const {
        return (node ? node->size : 0);
    }
};
int main() {
    TangoTree tangoTree;
    tangoTree.insert(3);
    tangoTree.insert(1);
    tangoTree.insert(4);
    tangoTree.insert(2);
    tangoTree.insert(5);
    tangoTree.inOrderTraversal();
    tangoTree.preOrderTraversal();
    tangoTree.postOrderTraversal();
    int keyToSearch = 2;
    if (tangoTree.search(keyToSearch)) {
        std::cout << "Key " << keyToSearch << " found.\n";
    } else {
        std::cout << "Key " << keyToSearch << " not found.\n";
    }
    return 0;
}
