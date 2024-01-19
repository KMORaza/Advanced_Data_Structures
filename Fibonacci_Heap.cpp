#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <unordered_map>
class FibonacciNode {
public:
    int key;
    int degree;
    bool marked;
    FibonacciNode* parent;
    FibonacciNode* child;
    FibonacciNode* prev;
    FibonacciNode* next;
    FibonacciNode(int k) : key(k), degree(0), marked(false),
                          parent(nullptr), child(nullptr),
                          prev(this), next(this) {}
};
class FibonacciHeap {
private:
    FibonacciNode* minNode;
    int numOfNodes;
public:
    FibonacciHeap() : minNode(nullptr), numOfNodes(0) {}
    bool isEmpty() const {
        return minNode == nullptr;
    }
    void insert(int key) {
        FibonacciNode* newNode = new FibonacciNode(key);
        if (minNode == nullptr) {
            minNode = newNode;
        } else {
            mergeLists(minNode, newNode);
            if (newNode->key < minNode->key) {
                minNode = newNode;
            }
        }
        numOfNodes++;
    }
    int getMin() const {
        if (isEmpty()) {
            std::cerr << "Error: Heap is empty\n";
            return std::numeric_limits<int>::max();
        }
        return minNode->key;
    }
    int extractMin() {
        FibonacciNode* oldMin = minNode;
        if (oldMin != nullptr) {
            if (oldMin->child != nullptr) {
                FibonacciNode* child = oldMin->child;
                do {
                    FibonacciNode* nextChild = child->next;
                    minNode->prev->next = child;
                    child->prev = minNode->prev;
                    minNode->prev = child;
                    child->next = minNode;
                    child->parent = nullptr;
                    child = nextChild;
                } while (child != oldMin->child);
            }
            removeNode(oldMin);
            if (oldMin == oldMin->next) {
                minNode = nullptr;
            } else {
                minNode = oldMin->next;
                consolidate();
            }
            numOfNodes--;
        }
        return oldMin->key;
    }
    void decreaseKey(FibonacciNode* node, int newKey) {
        if (newKey > node->key) {
            std::cerr << "Error: New key is greater than current key\n";
            return;
        }
        node->key = newKey;
        FibonacciNode* parent = node->parent;
        if (parent != nullptr && node->key < parent->key) {
            cut(node, parent);
            cascadingCut(parent);
        }
        if (node->key < minNode->key) {
            minNode = node;
        }
    }
    void deleteNode(FibonacciNode* node) {
        decreaseKey(node, std::numeric_limits<int>::min());
        extractMin();
    }
    void printHeap() {
        if (isEmpty()) {
            std::cout << "Heap is empty\n";
            return;
        }
        std::cout << "Fibonacci Heap: ";
        FibonacciNode* current = minNode;
        do {
            std::cout << current->key << " ";
            current = current->next;
        } while (current != minNode);
        std::cout << "\n";
    }
private:
    void mergeLists(FibonacciNode* root1, FibonacciNode* root2) {
        FibonacciNode* temp1 = root1->next;
        root1->next = root2->next;
        root2->next->prev = root1;
        root2->next = temp1;
        temp1->prev = root2;
    }
    void removeNode(FibonacciNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = node;
        node->next = node;
    }
    void link(FibonacciNode* child, FibonacciNode* parent) {
        removeNode(child);
        child->marked = false;
        child->parent = parent;
        if (parent->child == nullptr) {
            parent->child = child;
        } else {
            mergeLists(parent->child, child);
        }
        parent->degree++;
    }
    void consolidate() {
        int maxDegree = static_cast<int>(log2(numOfNodes)) + 1;
        std::vector<FibonacciNode*> degreeTable(maxDegree, nullptr);
        FibonacciNode* current = minNode;
        std::unordered_map<FibonacciNode*, bool> visited;
        do {
            FibonacciNode* nextNode = current->next;
            int degree = current->degree;
            while (degreeTable[degree] != nullptr) {
                FibonacciNode* other = degreeTable[degree];
                if (current->key > other->key) {
                    std::swap(current, other);
                }
                link(other, current);
                degreeTable[degree] = nullptr;
                degree++;
            }
            degreeTable[degree] = current;
            current = nextNode;
        } while (current != minNode);
        minNode = nullptr;
        for (int i = 0; i < maxDegree; ++i) {
            if (degreeTable[i] != nullptr) {
                if (minNode == nullptr) {
                    minNode = degreeTable[i];
                } else {
                    mergeLists(minNode, degreeTable[i]);
                    if (degreeTable[i]->key < minNode->key) {
                        minNode = degreeTable[i];
                    }
                }
            }
        }
    }
    void cut(FibonacciNode* child, FibonacciNode* parent) {
        removeNode(child);
        parent->degree--;
        if (parent->child == child) {
            parent->child = (child->next == child) ? nullptr : child->next;
        }
        child->parent = nullptr;
        child->marked = false;
        mergeLists(minNode, child);
    }
    void cascadingCut(FibonacciNode* node) {
        FibonacciNode* parent = node->parent;
        if (parent != nullptr) {
            if (!node->marked) {
                node->marked = true;
            } else {
                cut(node, parent);
                cascadingCut(parent);
            }
        }
    }
};
int main() {
    FibonacciHeap fibHeap;
    fibHeap.insert(3);
    fibHeap.insert(8);
    fibHeap.insert(2);
    fibHeap.insert(5);
    fibHeap.printHeap();
    std::cout << "Min: " << fibHeap.getMin() << "\n";
    std::cout << "Extracted Min: " << fibHeap.extractMin() << "\n";
    fibHeap.printHeap();
    fibHeap.decreaseKey(fibHeap.minNode->next, 1);
    fibHeap.printHeap();
    fibHeap.deleteNode(fibHeap.minNode->next);
    fibHeap.printHeap();
    return 0;
}
