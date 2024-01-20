#include <iostream>
#include <vector>
#include <algorithm>
class Node {
public:
    int x, y;
    Node* left;
    Node* right;
    Node(int x, int y) : x(x), y(y), left(nullptr), right(nullptr) {}
};
class GreedyDualTree {
private:
    Node* root;
    Node* buildTree(const std::vector<std::pair<int, int>>& points, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        std::vector<std::pair<int, int>> sortedPoints(points.begin() + start, points.begin() + end + 1);
        std::sort(sortedPoints.begin(), sortedPoints.end());
        int medianIndex = start + (end - start) / 2;
        Node* medianNode = new Node(sortedPoints[medianIndex].first, sortedPoints[medianIndex].second);
        medianNode->left = buildTree(points, start, medianIndex - 1);
        medianNode->right = buildTree(points, medianIndex + 1, end);
        return medianNode;
    }
    void rangeQuery(Node* node, int x1, int x2, int y, std::vector<std::pair<int, int>>& result) const {
        if (node == nullptr) {
            return;
        }
        if (node->x >= x1 && node->x <= x2 && node->y >= y) {
            result.emplace_back(node->x, node->y);
        }
        if (node->x >= x1) {
            rangeQuery(node->left, x1, x2, y, result);
        }
        if (node->x <= x2) {
            rangeQuery(node->right, x1, x2, y, result);
        }
    }
public:
    GreedyDualTree(const std::vector<std::pair<int, int>>& points) : root(nullptr) {
        root = buildTree(points, 0, points.size() - 1);
    }
    std::vector<std::pair<int, int>> rangeQuery(int x1, int x2, int y) const {
        std::vector<std::pair<int, int>> result;
        rangeQuery(root, x1, x2, y, result);
        return result;
    }
};
int main() {
    int n;
    std::cout << "Enter the number of points: ";
    std::cin >> n;
    std::vector<std::pair<int, int>> points;
    std::cout << "Enter the points (x y):" << std::endl;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }
    GreedyDualTree tree(points);
    int x1, x2, y;
    std::cout << "Enter the range query (x1 x2 y): ";
    std::cin >> x1 >> x2 >> y;
    std::vector<std::pair<int, int>> result = tree.rangeQuery(x1, x2, y);
    std::cout << "Points in the range query:" << std::endl;
    for (const auto& point : result) {
        std::cout << "(" << point.first << ", " << point.second << ")" << std::endl;
    }
    return 0;
}
