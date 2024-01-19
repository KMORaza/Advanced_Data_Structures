#include <iostream>
#include <cstdlib>
template <typename Key, typename Priority>
struct Node {
    Key key;
    Priority priority;
    Node* left;
    Node* right;
    Node(const Key& k, const Priority& p) : key(k), priority(p), left(nullptr), right(nullptr) {}
};
template <typename Key, typename Priority>
class Treap {
public:
    Treap() : root(nullptr) {}
    void insert(const Key& key, const Priority& priority) {
        root = insertNode(root, new Node<Key, Priority>(key, priority));
    }
    void remove(const Key& key) {
        root = removeNode(root, key);
    }
    bool search(const Key& key) const {
        return searchNode(root, key);
    }
    void update(const Key& key, const Priority& newPriority) {
        root = removeNode(root, key);
        root = insertNode(root, new Node<Key, Priority>(key, newPriority));
    }
    void inOrderTraversal() const {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
    void preOrderTraversal() const {
        preOrderTraversal(root);
        std::cout << std::endl;
    }
    void postOrderTraversal() const {
        postOrderTraversal(root);
        std::cout << std::endl;
    }
private:
    Node<Key, Priority>* root;
    Node<Key, Priority>* rotateRight(Node<Key, Priority>* y) {
        Node<Key, Priority>* x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }
    Node<Key, Priority>* rotateLeft(Node<Key, Priority>* x) {
        Node<Key, Priority>* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    Node<Key, Priority>* insertNode(Node<Key, Priority>* root, Node<Key, Priority>* newNode) {
        if (root == nullptr) {
            return newNode;
        }
        if (newNode->key < root->key) {
            root->left = insertNode(root->left, newNode);
            if (root->left->priority > root->priority) {
                root = rotateRight(root);
            }
        } else {
            root->right = insertNode(root->right, newNode);
            if (root->right->priority > root->priority) {
                root = rotateLeft(root);
            }
        }
        return root;
    }
    Node<Key, Priority>* removeNode(Node<Key, Priority>* root, const Key& key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (key < root->key) {
            root->left = removeNode(root->left, key);
        } else if (key > root->key) {
            root->right = removeNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                Node<Key, Priority>* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node<Key, Priority>* temp = root->left;
                delete root;
                return temp;
            }
            if (root->left->priority > root->right->priority) {
                root = rotateRight(root);
                root->right = removeNode(root->right, key);
            } else {
                root = rotateLeft(root);
                root->left = removeNode(root->left, key);
            }
        }
        return root;
    }
    bool searchNode(const Node<Key, Priority>* root, const Key& key) const {
        if (root == nullptr) {
            return false;
        }
        if (key < root->key) {
            return searchNode(root->left, key);
        } else if (key > root->key) {
            return searchNode(root->right, key);
        } else {
            return true;
        }
    }
    void inOrderTraversal(const Node<Key, Priority>* root) const {
        if (root != nullptr) {
            inOrderTraversal(root->left);
            std::cout << "(" << root->key << ", " << root->priority << ") ";
            inOrderTraversal(root->right);
        }
    }
    void preOrderTraversal(const Node<Key, Priority>* root) const {
        if (root != nullptr) {
            std::cout << "(" << root->key << ", " << root->priority << ") ";
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
        }
    }
    void postOrderTraversal(const Node<Key, Priority>* root) const {
        if (root != nullptr) {
            postOrderTraversal(root->left);
            postOrderTraversal(root->right);
            std::cout << "(" << root->key << ", " << root->priority << ") ";
        }
    }
};
int main() {
    Treap<int, int> treap;
    treap.insert(5, 10);
    treap.insert(3, 5);
    treap.insert(8, 15);
    treap.insert(2, 7);
    treap.insert(7, 12);
    std::cout << "In-Order Traversal: ";
    treap.inOrderTraversal();
    std::cout << "Pre-Order Traversal: ";
    treap.preOrderTraversal();
    std::cout << "Post-Order Traversal: ";
    treap.postOrderTraversal();
    int keyToSearch = 3;
    std::cout << "Search for key " << keyToSearch << ": " << (treap.search(keyToSearch) ? "Found" : "Not Found") << std::endl;
    int keyToDelete = 5;
    treap.remove(keyToDelete);
    std::cout << "After deleting key " << keyToDelete << ": ";
    treap.inOrderTraversal();
    int keyToUpdate = 8;
    int newPriority = 20;
    treap.update(keyToUpdate, newPriority);
    std::cout << "After updating priority of key " << keyToUpdate << ": ";
    treap.inOrderTraversal();
    return 0;
}
