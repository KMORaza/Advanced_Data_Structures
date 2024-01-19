#include <iostream>
#include <vector>
class SegmentTree {
private:
    std::vector<int> arr;
    std::vector<int> tree;
public:
    SegmentTree(const std::vector<int>& input) : arr(input) {
        tree.resize(4 * arr.size(), 0);
        build(1, 0, arr.size() - 1);
    }
    void update(int index, int value) {
        update(1, 0, arr.size() - 1, index, value);
    }
    int query(int left, int right) {
        return query(1, 0, arr.size() - 1, left, right);
    }
    void printTree() const {
        for (int i : tree) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
private:
    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    void update(int node, int start, int end, int index, int value) {
        if (start == end) {
            arr[index] = value;
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (start <= index && index <= mid) {
                update(2 * node, start, mid, index, value);
            } else {
                update(2 * node + 1, mid + 1, end, index, value);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    int query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return 0;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int leftSum = query(2 * node, start, mid, left, right);
        int rightSum = query(2 * node + 1, mid + 1, end, left, right);
        return leftSum + rightSum;
    }
};
int main() {
    std::vector<int> input = {1, 3, 5, 7, 9, 11};
    SegmentTree segmentTree(input);
    std::cout << "Original Array: ";
    for (int i : input) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Segment Tree: ";
    segmentTree.printTree();
    std::cout << "Query(1, 3): " << segmentTree.query(1, 3) << std::endl;
    segmentTree.update(2, 6);
    std::cout << "Updated Array: ";
    for (int i : input) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Updated Segment Tree: ";
    segmentTree.printTree();
    std::cout << "Query(1, 3) after update: " << segmentTree.query(1, 3) << std::endl;
    return 0;
}
