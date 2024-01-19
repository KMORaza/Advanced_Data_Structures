#include <iostream>
#include <cmath>
template <typename T>
class ScapegoatTree {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node* parent;
        Node(const T& k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr)
            : key(k), left(l), right(r), parent(p) {}
    };
    Node* root;
    int size;
    int maxSize; 
public:
    ScapegoatTree(double alpha = 0.75) : root(nullptr), size(0) {
        maxSize = alpha * pow(2, log2(1.0 * size + 1));
    }
    void insert(const T& key) {
        insert(key, root);
    }
    void remove(const T& key) {
        remove(key, root);
    }
    bool search(const T& key) const {
        return search(key, root);
    }
private:
    void insert(const T& key, Node*& currentNode) {
        if (currentNode == nullptr) {
            currentNode = new Node(key);
            ++size;
            if (size > maxSize) {
                rebuild(currentNode);
            }
        } else if (key < currentNode->key) {
            insert(key, currentNode->left);
        } else if (key > currentNode->key) {
            insert(key, currentNode->right);
        }
    }
    void remove(const T& key, Node*& currentNode) {
        if (currentNode == nullptr) {
            return;  
        }
        if (key < currentNode->key) {
            remove(key, currentNode->left);
        } else if (key > currentNode->key) {
            remove(key, currentNode->right);
        } else {
            if (currentNode->left == nullptr) {
                Node* temp = currentNode;
                currentNode = currentNode->right;
                delete temp;
            } else if (currentNode->right == nullptr) {
                Node* temp = currentNode;
                currentNode = currentNode->left;
                delete temp;
            } else {
                Node* successor = findMin(currentNode->right);
                currentNode->key = successor->key;
                remove(successor->key, currentNode->right);
            }
            --size;
        }
        if (size > maxSize * 2) {
            rebuild(currentNode);
        }
    }
    bool search(const T& key, const Node* currentNode) const {
        if (currentNode == nullptr) {
            return false;
        }
        if (key == currentNode->key) {
            return true;
        } else if (key < currentNode->key) {
            return search(key, currentNode->left);
        } else {
            return search(key, currentNode->right);
        }
    }
    Node* findMin(Node* currentNode) const {
        while (currentNode->left != nullptr) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }
    void rebuild(Node*& currentNode) {
        T* keys = new T[size];
        int index = 0;
        traverseInOrder(currentNode, keys, index);
        currentNode = buildBalancedTree(keys, 0, size - 1, nullptr);
        maxSize = 2 * size;
        delete[] keys;
    }
    void traverseInOrder(const Node* currentNode, T* keys, int& index) const {
        if (currentNode == nullptr) {
            return;
        }
        traverseInOrder(currentNode->left, keys, index);
        keys[index++] = currentNode->key;
        traverseInOrder(currentNode->right, keys, index);
    }
    Node* buildBalancedTree(const T* keys, int start, int end, Node* parent) {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;
        Node* newNode = new Node(keys[mid]);
        newNode->parent = parent;
        newNode->left = buildBalancedTree(keys, start, mid - 1, newNode);
        newNode->right = buildBalancedTree(keys, mid + 1, end, newNode);
        return newNode;
    }
};
int main() {
    ScapegoatTree<int> stree;
    stree.insert(3);
    stree.insert(1);
    stree.insert(4);
    stree.insert(2);
    stree.insert(5);
    std::cout << "Search for key 2: " << (stree.search(2) ? "Found" : "Not Found") << std::endl;
    stree.remove(2);
    std::cout << "Search for key 2: " << (stree.search(2) ? "Found" : "Not Found") << std::endl;
    return 0;
}
