#include <iostream>
#include <vector>
#include <limits>
class PairingNode {
public:
    int key;
    std::vector<PairingNode*> children;
    PairingNode(int k) : key(k) {}
    ~PairingNode() {
        for (PairingNode* child : children) {
            delete child;
        }
    }
};
class PairingHeap {
private:
    PairingNode* root;
public:
    PairingHeap() : root(nullptr) {}
    bool isEmpty() const {
        return root == nullptr;
    }
    void insert(int key) {
        PairingNode* newNode = new PairingNode(key);
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
        PairingNode* oldRoot = root;
        if (root->children.empty()) {
            delete root;
            root = nullptr;
        } else {
            root = mergePairs(root->children);
            delete oldRoot;
        }
        return minValue;
    }
    void decreaseKey(PairingNode* node, int newKey) {
        if (newKey > node->key) {
            std::cerr << "Error: New key is greater than current key\n";
            return;
        }
        node->key = newKey;
        if (node->children.size() > 0) {
            PairingNode* minChild = *(node->children.begin());
            if (minChild->key < newKey) {
                node->children.erase(node->children.begin());
                root = merge(root, minChild);
            }
        }
    }
    void deleteNode(PairingNode* node) {
        decreaseKey(node, std::numeric_limits<int>::min());
        extractMin();
    }
    void printHeap() {
        if (isEmpty()) {
            std::cout << "Heap is empty\n";
            return;
        }
        std::cout << "Pairing Heap: ";
        printTree(root);
        std::cout << "\n";
    }
private:
    PairingNode* merge(PairingNode* heap1, PairingNode* heap2) {
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
    PairingNode* mergePairs(const std::vector<PairingNode*>& pairs) {
        if (pairs.size() == 1) {
            return pairs[0];
        }
        std::vector<PairingNode*> mergedPairs;
        for (size_t i = 0; i + 1 < pairs.size(); i += 2) {
            PairingNode* merged = merge(pairs[i], pairs[i + 1]);
            mergedPairs.push_back(merged);
        }
        if (pairs.size() % 2 == 1) {
            mergedPairs.push_back(pairs.back());
        }
        return mergePairs(mergedPairs);
    }
    void printTree(PairingNode* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->key << " (";
        for (PairingNode* child : node->children) {
            printTree(child);
            std::cout << " ";
        }
        std::cout << ")";
    }
};
int main() {
    PairingHeap pairingHeap;
    pairingHeap.insert(3);
    pairingHeap.insert(8);
    pairingHeap.insert(2);
    pairingHeap.insert(5);
    pairingHeap.printHeap();
    std::cout << "Min: " << pairingHeap.getMin() << "\n";
    PairingNode* minNode = nullptr;
    int minValue = pairingHeap.extractMin();
    std::cout << "Extracted Min: " << minValue << "\n";
    pairingHeap.printHeap();
    pairingHeap.decreaseKey(minNode, 1);
    pairingHeap.printHeap();
    pairingHeap.deleteNode(minNode);
    pairingHeap.printHeap();
    return 0;
}
