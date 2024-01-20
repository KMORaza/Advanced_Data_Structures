#include <iostream>
#include <vector>
class SegmentTree {
private:
    std::vector<int> tree, lazy;
    int size;
    void propagate(int node, int left, int right) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (right - left + 1);
            if (left != right) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0; 
        }
    }
    int query(int node, int left, int right, int queryLeft, int queryRight) {
        propagate(node, left, right);
        if (queryRight < left || queryLeft > right) {
            return 0;
        }
        if (queryLeft <= left && queryRight >= right) {
            return tree[node]; 
        }
        int mid = (left + right) / 2;
        int leftSum = query(2 * node + 1, left, mid, queryLeft, queryRight);
        int rightSum = query(2 * node + 2, mid + 1, right, queryLeft, queryRight);
        return leftSum + rightSum;
    }
    void update(int node, int left, int right, int updateLeft, int updateRight, int value) {
        propagate(node, left, right);
        if (updateRight < left || updateLeft > right) {
            return;
        }
        if (updateLeft <= left && updateRight >= right) {
            tree[node] += value * (right - left + 1);
            if (left != right) {
                lazy[2 * node + 1] += value;
                lazy[2 * node + 2] += value;
            }
            return;
        }
        int mid = (left + right) / 2;
        update(2 * node + 1, left, mid, updateLeft, updateRight, value);
        update(2 * node + 2, mid + 1, right, updateLeft, updateRight, value);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
public:
    SegmentTree(int n) {
        size = n;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }
    int query(int queryLeft, int queryRight) {
        return query(0, 0, size - 1, queryLeft, queryRight);
    }
    void update(int updateLeft, int updateRight, int value) {
        update(0, 0, size - 1, updateLeft, updateRight, value);
    }
};
int main() {
    int n = 8;
    SegmentTree segmentTree(n);
    segmentTree.update(1, 5, 3);
    segmentTree.update(3, 7, 2);
    std::cout << "Query result: " << segmentTree.query(2, 6) << std::endl;
    return 0;
}
