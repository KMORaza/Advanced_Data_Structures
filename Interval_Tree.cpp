#include <iostream>
#include <vector>
#include <algorithm>
class Interval {
public:
    int low, high;
    Interval(int low, int high) : low(low), high(high) {}
};
class IntervalTreeNode {
public:
    Interval interval;
    int maxEnd;
    IntervalTreeNode* left;
    IntervalTreeNode* right;
    IntervalTreeNode(const Interval& interval) : interval(interval), maxEnd(interval.high), left(nullptr), right(nullptr) {}
};
class IntervalTree {
private:
    IntervalTreeNode* root;
public:
    IntervalTree() : root(nullptr) {}
    ~IntervalTree() {
        clear(root);
    }
    void insert(const Interval& interval) {
        root = insert(root, interval);
    }
    void remove(const Interval& interval) {
        root = remove(root, interval);
    }
    bool search(const Interval& interval) const {
        return search(root, interval);
    }
    std::vector<Interval> queryOverlap(const Interval& interval) const {
        std::vector<Interval> result;
        queryOverlap(root, interval, result);
        return result;
    }
    void inOrderTraversal() const {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
private:
    IntervalTreeNode* insert(IntervalTreeNode* node, const Interval& interval) {
        if (node == nullptr) {
            return new IntervalTreeNode(interval);
        }
        if (interval.low < node->interval.low) {
            node->left = insert(node->left, interval);
        } else {
            node->right = insert(node->right, interval);
        }
        node->maxEnd = std::max(node->maxEnd, interval.high);
        return node;
    }
    IntervalTreeNode* remove(IntervalTreeNode* node, const Interval& interval) {
        if (node == nullptr) {
            return nullptr;
        }
        if (interval.low < node->interval.low) {
            node->left = remove(node->left, interval);
        } else if (interval.low > node->interval.low) {
            node->right = remove(node->right, interval);
        } else {
            if (interval.high != node->interval.high) {
                node->right = remove(node->right, interval);
            } else {
                if (node->left == nullptr) {
                    IntervalTreeNode* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    IntervalTreeNode* temp = node->left;
                    delete node;
                    return temp;
                }
                IntervalTreeNode* successor = findMin(node->right);
                node->interval = successor->interval;
                node->right = remove(node->right, successor->interval);
            }
        }
        if (node != nullptr) {
            node->maxEnd = std::max(getMaxEnd(node->left), getMaxEnd(node->right));
        }
        return node;
    }
    bool search(IntervalTreeNode* node, const Interval& interval) const {
        while (node != nullptr) {
            if (doOverlap(node->interval, interval)) {
                return true;
            }
            if (node->left != nullptr && node->left->maxEnd >= interval.low) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }
    void queryOverlap(IntervalTreeNode* node, const Interval& interval, std::vector<Interval>& result) const {
        if (node == nullptr) {
            return;
        }
        if (doOverlap(node->interval, interval)) {
            result.push_back(node->interval);
        }
        if (node->left != nullptr && node->left->maxEnd >= interval.low) {
            queryOverlap(node->left, interval, result);
        }
        queryOverlap(node->right, interval, result);
    }
    void inOrderTraversal(IntervalTreeNode* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            std::cout << "[" << node->interval.low << ", " << node->interval.high << "] ";
            inOrderTraversal(node->right);
        }
    }
    IntervalTreeNode* findMin(IntervalTreeNode* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    int getMaxEnd(IntervalTreeNode* node) const {
        return (node != nullptr) ? node->maxEnd : 0;
    }
    bool doOverlap(const Interval& interval1, const Interval& interval2) const {
        return (interval1.low <= interval2.high && interval2.low <= interval1.high);
    }
    void clear(IntervalTreeNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};
int main() {
    IntervalTree intervalTree;
    intervalTree.insert(Interval(15, 20));
    intervalTree.insert(Interval(10, 30));
    intervalTree.insert(Interval(5, 12));
    intervalTree.insert(Interval(17, 19));
    intervalTree.insert(Interval(30, 40));
    std::cout << "In-Order Traversal: ";
    intervalTree.inOrderTraversal();
    std::cout << std::endl;
    Interval searchInterval(14, 16);
    std::cout << "Search for interval [" << searchInterval.low << ", " << searchInterval.high << "]: "
              << (intervalTree.search(searchInterval) ? "Found" : "Not Found") << std::endl;
    Interval removeInterval(15, 20);
    intervalTree.remove(removeInterval);
    std::cout << "In-Order Traversal (After Removal): ";
    intervalTree.inOrderTraversal();
    std::cout << std::endl;
    std::vector<Interval> overlapIntervals = intervalTree.queryOverlap(Interval(6, 16));
    std::cout << "Overlapping Intervals with [6, 16]: ";
    for (const Interval& interval : overlapIntervals) {
        std::cout << "[" << interval.low << ", " << interval.high << "] ";
    }
    std::cout << std::endl;
    return 0;
}
