#include <iostream>
#include <vector>
#include <algorithm>
template <typename Point, typename Value>
struct KDNode {
    Point point;
    Value data;
    KDNode* left;
    KDNode* right;
    KDNode(const Point& p, const Value& d) : point(p), data(d), left(nullptr), right(nullptr) {}
};
template <typename Point, typename Value>
class KDTree {
public:
    KDTree() : root(nullptr), dimensions(0) {}
    void insert(const Point& point, const Value& data) {
        root = insertNode(root, point, data, 0);
    }
    Value nearestNeighbor(const Point& query) const {
        if (root == nullptr) {
            throw std::runtime_error("KD-Tree is empty");
        }
        KDNode<Point, Value>* nearest = nullptr;
        double minDistance = std::numeric_limits<double>::max();
        nearestNeighbor(root, query, 0, nearest, minDistance);
        return nearest->data;
    }
    void inOrderTraversal() const {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
    void preOrderTraversal() const {
        preOrderTraversal(root);
        std::cout << std::endl;
    }
    void postOrderTraversal() const {
        postOrderTraversal(root);
        std::cout << std::endl;
    }
private:
    KDNode<Point, Value>* root;
    std::size_t dimensions;
    KDNode<Point, Value>* insertNode(KDNode<Point, Value>* node, const Point& point, const Value& data, std::size_t depth) {
        if (node == nullptr) {
            dimensions = point.size();
            return new KDNode<Point, Value>(point, data);
        }
        std::size_t axis = depth % dimensions;
        if (point[axis] < node->point[axis]) {
            node->left = insertNode(node->left, point, data, depth + 1);
        } else {
            node->right = insertNode(node->right, point, data, depth + 1);
        }
        return node;
    }
    void nearestNeighbor(KDNode<Point, Value>* node, const Point& query, std::size_t depth,
                         KDNode<Point, Value>*& nearest, double& minDistance) const {
        if (node == nullptr) {
            return;
        }
        std::size_t axis = depth % dimensions;
        double distance = calculateDistance(query, node->point);
        if (distance < minDistance) {
            nearest = node;
            minDistance = distance;
        }
        if (query[axis] < node->point[axis]) {
            nearestNeighbor(node->left, query, depth + 1, nearest, minDistance);
            if (query[axis] + minDistance >= node->point[axis]) {
                nearestNeighbor(node->right, query, depth + 1, nearest, minDistance);
            }
        } else {
            nearestNeighbor(node->right, query, depth + 1, nearest, minDistance);
            if (query[axis] - minDistance <= node->point[axis]) {
                nearestNeighbor(node->left, query, depth + 1, nearest, minDistance);
            }
        }
    }
    double calculateDistance(const Point& p1, const Point& p2) const {
        double distance = 0.0;
        for (std::size_t i = 0; i < dimensions; ++i) {
            distance += std::pow(p1[i] - p2[i], 2);
        }
        return std::sqrt(distance);
    }
    void inOrderTraversal(const KDNode<Point, Value>* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            printNode(node);
            inOrderTraversal(node->right);
        }
    }
    void preOrderTraversal(const KDNode<Point, Value>* node) const {
        if (node != nullptr) {
            printNode(node);
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }
    void postOrderTraversal(const KDNode<Point, Value>* node) const {
        if (node != nullptr) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            printNode(node);
        }
    }
    void printNode(const KDNode<Point, Value>* node) const {
        std::cout << "(";
        for (std::size_t i = 0; i < dimensions; ++i) {
            std::cout << node->point[i];
            if (i < dimensions - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ") ";
    }
};
int main() {
    KDTree<std::vector<double>, std::string> kdTree;
    kdTree.insert({2.0, 3.0}, "A");
    kdTree.insert({5.0, 4.0}, "B");
    kdTree.insert({9.0, 6.0}, "C");
    kdTree.insert({4.0, 7.0}, "D");
    kdTree.insert({8.0, 1.0}, "E");
    std::cout << "In-Order Traversal: ";
    kdTree.inOrderTraversal();
    std::cout << "Pre-Order Traversal: ";
    kdTree.preOrderTraversal();
    std::cout << "Post-Order Traversal: ";
    kdTree.postOrderTraversal();
    std::vector<double> queryPoint = {6.0, 3.0};
    std::cout << "Nearest neighbor to query point (6.0, 3.0): " << kdTree.nearestNeighbor(queryPoint) << std::endl;
    return 0;
}
