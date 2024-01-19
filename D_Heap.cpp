#include <iostream>
#include <vector>
#include <limits>
template <int D>
class DHeap {
private:
    struct DHeapNode {
        int key;
        std::vector<DHeapNode*> children;
        DHeapNode(int k) : key(k) {}
    };
    DHeapNode* root;
public:
    DHeap() : root(nullptr) {}
    bool isEmpty() const {
        return root == nullptr;
    }
    void insert(int key) {
        DHeapNode* newNode = new DHeapNode(key);
        root = merge(root, newNode);
    }
    int getMin() const {
        if (isEmpty()) {
            std::cerr << "Error: Heap is empty\n";
            return -1;
        }
        return root->key;
    }
    int extractMin() {
        if (isEmpty()) {
            std::cerr << "Error: Heap is empty\n";
            return -1; 
        }
        int minValue = root->key;
        DHeapNode* oldRoot = root;
        if (root->children.empty()) {
            delete root;
            root = nullptr;
        } else {
            root = mergePairs(root->children);
            delete oldRoot;
        }
        return minValue;
    }
    void decreaseKey(DHeapNode* node, int newKey) {
        if (newKey > node->key) {
            std::cerr << "Error: New key is greater than current key\n";
            return;
        }
        node->key = newKey;
        if (!node->children.empty()) {
            DHeapNode* minChild = *(node->children.begin());
            if (minChild->key < newKey) {
                node->children.erase(node->children.begin());
                root = merge(root, minChild);
            }
        }
    }
    void deleteNode(DHeapNode* node) {
        decreaseKey(node, std::numeric_limits<int>::min());
        extractMin();
    }
    void printHeap() {
        if (isEmpty()) {
            std::cout << "Heap is empty\n";
            return;
        }
        std::cout << "D-Heap: ";
        printTree(root);
        std::cout << "\n";
    }
private:
    DHeapNode* merge(DHeapNode* heap1, DHeapNode* heap2) {
        if (heap1 == nullptr) {
            return heap2;
        } else if (heap2 == nullptr) {
            return heap1;
        } else {
            if (heap1->key < heap2->key) {
                heap2->children.push_back(heap1);
                return heap2;
            } else {
                heap1->children.push_back(heap2);
                return heap1;
            }
        }
    }
    DHeapNode* mergePairs(const std::vector<DHeapNode*>& pairs) {
        if (pairs.size() == 1) {
            return pairs[0];
        }
        std::vector<DHeapNode*> mergedPairs;
        for (size_t i = 0; i + 1 < pairs.size(); i += 2) {
            DHeapNode* merged = merge(pairs[i], pairs[i + 1]);
            mergedPairs.push_back(merged);
        }
        if (pairs.size() % 2 == 1) {
            mergedPairs.push_back(pairs.back());
        }
        return mergePairs(mergedPairs);
    }
    void printTree(DHeapNode* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->key << " (";
        for (DHeapNode* child : node->children) {
            printTree(child);
            std::cout << " ";
        }
        std::cout << ")";
    }
};
int main() {
    const int D = 3; 
    DHeap<D> dHeap;
    dHeap.insert(3);
    dHeap.insert(8);
    dHeap.insert(2);
    dHeap.insert(5);
    dHeap.printHeap();
    std::cout << "Min: " << dHeap.getMin() << "\n";
    DHeap<D>::DHeapNode* minNode = nullptr;
    int minValue = dHeap.extractMin();
    std::cout << "Extracted Min: " << minValue << "\n";
    dHeap.printHeap();
    dHeap.decreaseKey(minNode, 1);
    dHeap.printHeap();
    dHeap.deleteNode(minNode);
    dHeap.printHeap();
    return 0;
}
