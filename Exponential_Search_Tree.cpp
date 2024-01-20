#include <iostream>
#include <vector>
using namespace std;
class ESTNode {
public:
    int key;
    int size;
    ESTNode* left;
    ESTNode* right;
    ESTNode(int k) : key(k), size(1), left(nullptr), right(nullptr) {}
};
class ExponentialSearchTree {
private:
    ESTNode* root;
    void updateSize(ESTNode* node) {
        if (node != nullptr) {
            node->size = 1 + getSize(node->left) + getSize(node->right);
        }
    }
    int getSize(ESTNode* node) const {
        return (node != nullptr) ? node->size : 0;
    }
    ESTNode* rotateRight(ESTNode* y) {
        ESTNode* x = y->left;
        y->left = x->right;
        x->right = y;
        updateSize(y);
        updateSize(x);
        return x;
    }
    ESTNode* rotateLeft(ESTNode* x) {
        ESTNode* y = x->right;
        x->right = y->left;
        y->left = x;
        updateSize(x);
        updateSize(y);
        return y;
    }
    ESTNode* insert(ESTNode* root, int key) {
        if (root == nullptr) {
            return new ESTNode(key);
        }
        if (key < root->key) {
            root->left = insert(root->left, key);
            root = rotateRight(root);
        } else {
            root->right = insert(root->right, key);
            root = rotateLeft(root);
        }
        return root;
    }
    ESTNode* deleteNode(ESTNode* root, int key) {
        if (root == nullptr) {
            return root;
        }
        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                ESTNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                ESTNode* temp = root->left;
                delete root;
                return temp;
            }
            if (getSize(root->left) > getSize(root->right)) {
                root = rotateRight(root);
                root->right = deleteNode(root->right, key);
            } else {
                root = rotateLeft(root);
                root->left = deleteNode(root->left, key);
            }
        }
        return root;
    }
    ESTNode* search(ESTNode* root, int key) const {
        if (root == nullptr || root->key == key) {
            return root;
        }
        if (key < root->key) {
            return search(root->left, key);
        } else {
            return search(root->right, key);
        }
    }
    void inOrderTraversal(ESTNode* root) const {
        if (root != nullptr) {
            inOrderTraversal(root->left);
            cout << root->key << " ";
            inOrderTraversal(root->right);
        }
    }
    void preOrderTraversal(ESTNode* root) const {
        if (root != nullptr) {
            cout << root->key << " ";
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
        }
    }
    void postOrderTraversal(ESTNode* root) const {
        if (root != nullptr) {
            postOrderTraversal(root->left);
            postOrderTraversal(root->right);
            cout << root->key << " ";
        }
    }
public:
    ExponentialSearchTree() : root(nullptr) {}
    void insert(int key) {
        root = insert(root, key);
    }
    void deleteNode(int key) {
        root = deleteNode(root, key);
    }
    ESTNode* search(int key) const {
        return search(root, key);
    }
    void inOrderTraversal() const {
        inOrderTraversal(root);
        cout << endl;
    }
    void preOrderTraversal() const {
        preOrderTraversal(root);
        cout << endl;
    }
    void postOrderTraversal() const {
        postOrderTraversal(root);
        cout << endl;
    }
};
int main() {
    ExponentialSearchTree est;
    est.insert(50);
    est.insert(30);
    est.insert(70);
    est.insert(20);
    est.insert(40);
    est.insert(60);
    est.insert(80);
    cout << "In-order traversal: ";
    est.inOrderTraversal();
    cout << "Pre-order traversal: ";
    est.preOrderTraversal();
    cout << "Post-order traversal: ";
    est.postOrderTraversal();
    cout << "Searching for key 40: ";
    ESTNode* result = est.search(40);
    if (result != nullptr) {
        cout << "Found!" << endl;
    } else {
        cout << "Not Found!" << endl;
    }
    est.deleteNode(40);
    cout << "After deleting key 40:" << endl;
    cout << "In-order traversal: ";
    est.inOrderTraversal();
    cout << "Pre-order traversal: ";
    est.preOrderTraversal();
    cout << "Post-order traversal: ";
    est.postOrderTraversal();
    return 0;
}
