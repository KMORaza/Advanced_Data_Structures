#include <iostream>
#include <vector>
#include <algorithm>
struct Interval {
    int low, high;
    Interval(int l, int h) : low(l), high(h) {}
};
class IntervalTree {
private:
    struct Node {
        int center;
        Interval interval;
        Node* left;
        Node* right;
        Node(const Interval& i) : center((i.low + i.high) / 2), interval(i), left(nullptr), right(nullptr) {}
    };
    Node* root;
public:
    IntervalTree() : root(nullptr) {}
    void insert(const Interval& interval) {
        root = insert(root, interval);
    }
    std::vector<Interval> queryOverlap(const Interval& queryInterval) const {
        std::vector<Interval> result;
        queryOverlap(root, queryInterval, result);
        return result;
    }
private:
    Node* insert(Node* node, const Interval& interval) {
        if (node == nullptr) {
            return new Node(interval);
        }
        if (interval.low <= node->center) {
            node->left = insert(node->left, interval);
        } else {
            node->right = insert(node->right, interval);
        }
        return node;
    }
    void queryOverlap(const Node* node, const Interval& queryInterval, std::vector<Interval>& result) const {
        if (node == nullptr) {
            return;
        }
        if (overlap(node->interval, queryInterval)) {
            result.push_back(node->interval);
        }
        if (queryInterval.low <= node->center) {
            queryOverlap(node->left, queryInterval, result);
        }
        if (queryInterval.high > node->center) {
            queryOverlap(node->right, queryInterval, result);
        }
    }
    bool overlap(const Interval& a, const Interval& b) const {
        return !(a.high < b.low || a.low > b.high);
    }
};
int main() {
    IntervalTree intervalTree;
    intervalTree.insert(Interval(15, 20));
    intervalTree.insert(Interval(10, 30));
    intervalTree.insert(Interval(17, 19));
    intervalTree.insert(Interval(5, 20));
    intervalTree.insert(Interval(12, 15));
    intervalTree.insert(Interval(30, 40));
    Interval queryInterval(14, 16);
    std::vector<Interval> result = intervalTree.queryOverlap(queryInterval);
    std::cout << "Intervals overlapping with [" << queryInterval.low << ", " << queryInterval.high << "]:" << std::endl;
    for (const auto& interval : result) {
        std::cout << "[" << interval.low << ", " << interval.high << "]" << std::endl;
    }
    return 0;
}
