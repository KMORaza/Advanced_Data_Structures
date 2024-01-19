#include <iostream>
#include <vector>
class BinomialNode {
public:
    int key;
    int degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;
    BinomialNode(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};
class BinomialHeap {
private:
    std::vector<BinomialNode*> trees;
public:
    BinomialHeap() {}
    bool isEmpty() const {
        return trees.empty();
    }
    void insert(int key) {
        BinomialNode* newNode = new BinomialNode(key);
        BinomialHeap tempHeap;
        tempHeap.trees.push_back(newNode);
        unionHeaps(*this, tempHeap);
    }
    int getMin() const {
        if (isEmpty()) {
            std::cerr << "Error: Heap is empty\n";
            return -1;
        }
        BinomialNode* minNode = findMinNode();
        return minNode->key;
    }
    int extractMin() {
        if (isEmpty()) {
            std::cerr << "Error: Heap is empty\n";
            return -1; 
        }
        BinomialNode* minNode = findMinNode();
        removeTree(minNode);
        BinomialHeap tempHeap;
        while (minNode->child) {
            BinomialNode* child = minNode->child;
            minNode->child = child->sibling;
            child->parent = nullptr;
            child->sibling = nullptr;
            tempHeap.trees.push_back(reverseTree(child));
        }
        unionHeaps(*this, tempHeap);
        int minValue = minNode->key;
        delete minNode;
        return minValue;
    }
    void decreaseKey(BinomialNode* node, int newKey) {
        if (newKey > node->key) {
            std::cerr << "Error: New key is greater than current key\n";
            return;
        }
        node->key = newKey;
        while (node->parent && node->key < node->parent->key) {
            std::swap(node->key, node->parent->key);
            node = node->parent;
        }
    }
    void deleteNode(BinomialNode* node) {
        decreaseKey(node, std::numeric_limits<int>::min());
        extractMin();
    }
    void printHeap() {
        if (isEmpty()) {
            std::cout << "Heap is empty\n";
            return;
        }
        for (BinomialNode* tree : trees) {
            printTree(tree);
        }
    }
private:
    BinomialNode* findMinNode() const {
        BinomialNode* minNode = nullptr;
        for (BinomialNode* tree : trees) {
            if (!minNode || (tree && tree->key < minNode->key)) {
                minNode = tree;
            }
        }
        return minNode;
    }
    void removeTree(BinomialNode* target) {
        trees.erase(std::remove(trees.begin(), trees.end(), target), trees.end());
    }
    void unionHeaps(BinomialHeap& heap1, BinomialHeap& heap2) {
        heap1.trees.insert(heap1.trees.end(), heap2.trees.begin(), heap2.trees.end());
        heap2.trees.clear();
        consolidate(heap1);
    }
    void consolidate(BinomialHeap& heap) {
        if (heap.trees.size() <= 1) {
            return;
        }
        std::vector<BinomialNode*> degreeTable(2 * heap.trees.size(), nullptr);
        for (BinomialNode* tree : heap.trees) {
            int degree = tree->degree;
            while (degreeTable[degree] != nullptr) {
                BinomialNode* otherTree = degreeTable[degree];
                if (tree->key > otherTree->key) {
                    std::swap(tree, otherTree);
                }
                link(tree, otherTree);
                degreeTable[degree] = nullptr;
                degree++;
            }
            degreeTable[degree] = tree;
        }
        heap.trees.clear();
        for (BinomialNode* tree : degreeTable) {
            if (tree != nullptr) {
                heap.trees.push_back(tree);
            }
        }
    }
    void link(BinomialNode* tree1, BinomialNode* tree2) {
        tree1->parent = tree2;
        tree1->sibling = tree2->child;
        tree2->child = tree1;
        tree2->degree++;
    }
    BinomialNode* reverseTree(BinomialNode* root) {
        BinomialNode* prev = nullptr;
        BinomialNode* current = root;
        while (current) {
            BinomialNode* next = current->sibling;
            current->sibling = prev;
            current->parent = nullptr;
            prev = current;
            current = next;
        }
        return prev;
    }
    void printTree(BinomialNode* root) {
        if (root == nullptr) {
            return;
        }
        BinomialNode* current = root;
        while (current) {
            std::cout << current->key << " ";
            printTree(current->child);
            current = current->sibling;
        }
    }
};
int main() {
    BinomialHeap binHeap;
    binHeap.insert(3);
    binHeap.insert(8);
    binHeap.insert(2);
    binHeap.insert(5);
    binHeap.printHeap();
    std::cout << "Min: " << binHeap.getMin() << "\n";
    binHeap.decreaseKey(binHeap.trees[0]->child, 1);
    binHeap.printHeap();
    binHeap.deleteNode(binHeap.trees[0]->child);
    binHeap.printHeap();
    return 0;
}
