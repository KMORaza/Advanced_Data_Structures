#include <iostream>
#include <cstdlib>
#include <ctime>
template <typename T>
class ImplicitTreap {
private:
    struct Node {
        T key;
        int priority;
        int size; 
        Node* left;
        Node* right;
        Node(const T& k, int prio)
            : key(k), priority(prio), size(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
public:
    ImplicitTreap() : root(nullptr) {
        srand(static_cast<unsigned>(time(nullptr)));
    }
    void insert(int index, const T& key) {
        int randPriority = rand(); 
        Node* newNode = new Node(key, randPriority);
        root = insertAtIndex(index, newNode, root);
    }
    void erase(int index) {
        root = eraseAtIndex(index, root);
    }
    T get(int index) const {
        Node* node = getNodeAtIndex(index, root);
        return (node != nullptr) ? node->key : T();
    }
    void split(int index, ImplicitTreap& leftTreap, ImplicitTreap& rightTreap) {
        Node* left = nullptr;
        Node* right = nullptr;
        splitAtIndex(index, root, left, right);
        leftTreap.root = left;
        rightTreap.root = right;
    }
    void merge(ImplicitTreap& otherTreap) {
        root = mergeTrees(root, otherTreap.root);
        otherTreap.root = nullptr; 
    }
    void printInOrder() const {
        printInOrder(root);
        std::cout << std::endl;
    }
private:
    Node* insertAtIndex(int index, Node* newNode, Node* currentRoot) {
        if (currentRoot == nullptr) {
            return newNode;
        }
        int leftSize = getSize(currentRoot->left);
        if (index <= leftSize) {
            currentRoot->left = insertAtIndex(index, newNode, currentRoot->left);
            currentRoot = rotateRight(currentRoot);
        } else {
            currentRoot->right = insertAtIndex(index - leftSize - 1, newNode, currentRoot->right);
            currentRoot = rotateLeft(currentRoot);
        }
        updateSize(currentRoot);
        return currentRoot;
    }
    Node* eraseAtIndex(int index, Node* currentRoot) {
        if (currentRoot == nullptr) {
            return nullptr;
        }
        int leftSize = getSize(currentRoot->left);
        if (index < leftSize) {
            currentRoot->left = eraseAtIndex(index, currentRoot->left);
        } else if (index > leftSize) {
            currentRoot->right = eraseAtIndex(index - leftSize - 1, currentRoot->right);
        } else {
            Node* temp = currentRoot;
            currentRoot = mergeTrees(currentRoot->left, currentRoot->right);
            delete temp;
        }
        if (currentRoot != nullptr) {
            updateSize(currentRoot);
        }
        return currentRoot;
    }
    Node* getNodeAtIndex(int index, Node* currentRoot) const {
        if (currentRoot == nullptr) {
            return nullptr;
        }
        int leftSize = getSize(currentRoot->left);
        if (index < leftSize) {
            return getNodeAtIndex(index, currentRoot->left);
        } else if (index > leftSize) {
            return getNodeAtIndex(index - leftSize - 1, currentRoot->right);
        } else {
            return currentRoot;
        }
    }
    void splitAtIndex(int index, Node* currentRoot, Node*& left, Node*& right) {
        if (currentRoot == nullptr) {
            left = nullptr;
            right = nullptr;
        } else {
            int leftSize = getSize(currentRoot->left);

            if (index <= leftSize) {
                splitAtIndex(index, currentRoot->left, left, currentRoot->left);
                right = currentRoot;
            } else {
                splitAtIndex(index - leftSize - 1, currentRoot->right, currentRoot->right, right);
                left = currentRoot;
            }
            updateSize(currentRoot);
        }
    }
    Node* mergeTrees(Node* leftRoot, Node* rightRoot) {
        if (leftRoot == nullptr) {
            return rightRoot;
        }
        if (rightRoot == nullptr) {
            return leftRoot;
        }
        if (leftRoot->priority > rightRoot->priority) {
            leftRoot->right = mergeTrees(leftRoot->right, rightRoot);
            updateSize(leftRoot);
            return leftRoot;
        } else {
            rightRoot->left = mergeTrees(leftRoot, rightRoot->left);
            updateSize(rightRoot);
            return rightRoot;
        }
    }
    void printInOrder(Node* currentRoot) const {
        if (currentRoot != nullptr) {
            printInOrder(currentRoot->left);
            std::cout << currentRoot->key << " ";
            printInOrder(currentRoot->right);
        }
    }
    int getSize(Node* node) const {
        return (node != nullptr) ? node->size : 0;
    }
    void updateSize(Node* node) {
        if (node != nullptr) {
            node->size = getSize(node->left) + getSize(node->right) + 1;
        }
    }
    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateSize(node);
        updateSize(newRoot);
        return newRoot;
    }
    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateSize(node);
        updateSize(newRoot);
        return newRoot;
    }
};
int main() {
    ImplicitTreap<int> treap;
    treap.insert(0, 10);
    treap.insert(1, 20);
    treap.insert(2, 30);
    treap.insert(1, 25);
    treap.printInOrder(); 
    treap.erase(1);
    treap.printInOrder(); 
    ImplicitTreap<int> treap2;
    treap2.insert(0, 15);
    treap2.insert(1, 35);
    treap.merge(treap2);
    treap.printInOrder(); 
    return 0;
}
