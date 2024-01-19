// Comprehensive implementation of Quad Tree
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
class Point {
public:
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};
class Rectangle {
public:
    double x, y, width, height;
    Rectangle(double x, double y, double width, double height)
        : x(x), y(y), width(width), height(height) {}
    bool contains(const Point& point) const {
        return point.x >= x && point.x <= x + width && point.y >= y && point.y <= y + height;
    }
    bool intersects(const Rectangle& other) const {
        return !(x + width < other.x || other.x + other.width < x ||
                 y + height < other.y || other.y + other.height < y);
    }
};
template <typename T>
class QuadtreeNode {
public:
    Rectangle bounds;
    std::vector<T> data;
    QuadtreeNode<T>* children[4];
    QuadtreeNode(const Rectangle& bounds) : bounds(bounds) {
        for (int i = 0; i < 4; ++i) {
            children[i] = nullptr;
        }
    }
    ~QuadtreeNode() {
        for (int i = 0; i < 4; ++i) {
            delete children[i];
        }
    }
};
template <typename T>
class Quadtree {
public:
    Quadtree(const Rectangle& bounds) : root(new QuadtreeNode<T>(bounds)) {}
    ~Quadtree() {
        clear();
    }
    void insert(const Point& point, const T& data) {
        insert(root, point, data);
    }
    void remove(const Point& point) {
        remove(root, point);
    }
    bool search(const Point& point) const {
        return search(root, point);
    }
    std::vector<T> queryRange(const Rectangle& range) const {
        std::vector<T> result;
        queryRange(root, range, result);
        return result;
    }
    T nearestNeighbor(const Point& query) const {
        if (root == nullptr) {
            throw std::runtime_error("Quadtree is empty");
        }
        QuadtreeNode<T>* nearest = nullptr;
        double minDistance = std::numeric_limits<double>::max();
        nearestNeighbor(root, query, nearest, minDistance);
        return nearest->data.front(); 
    }
    void update(const Point& point, const T& newData) {
        remove(point);
        insert(point, newData);
    }
    void clear() {
        delete root;
        root = new QuadtreeNode<T>(root->bounds);
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
    std::size_t count() const {
        return count(root);
    }
    bool isEmpty() const {
        return count() == 0;
    }
private:
    QuadtreeNode<T>* root;
    void insert(QuadtreeNode<T>* node, const Point& point, const T& data) {
        if (!node->bounds.contains(point)) {
            return;
        }
        if (node->data.size() < 4) {
            node->data.push_back(data);
        } else {
            if (node->children[0] == nullptr) {
                splitNode(node);
            }
            for (int i = 0; i < 4; ++i) {
                insert(node->children[i], point, data);
            }
        }
    }
    void remove(QuadtreeNode<T>* node, const Point& point) {
        if (node == nullptr) {
            return;
        }
        auto it = std::find_if(node->data.begin(), node->data.end(),
                               [point](const T& d) { return d == point; });
        if (it != node->data.end()) {
            node->data.erase(it);
        } else {
            for (int i = 0; i < 4; ++i) {
                remove(node->children[i], point);
            }
        }
    }
    bool search(QuadtreeNode<T>* node, const Point& point) const {
        if (node == nullptr) {
            return false;
        }
        auto it = std::find_if(node->data.begin(), node->data.end(),
                               [point](const T& d) { return d == point; });
        if (it != node->data.end()) {
            return true;
        } else {
            for (int i = 0; i < 4; ++i) {
                if (node->children[i]->bounds.contains(point)) {
                    if (search(node->children[i], point)) {
                        return true;
                    }
                }
            }
            return false;
        }
    }
    void queryRange(QuadtreeNode<T>* node, const Rectangle& range, std::vector<T>& result) const {
        if (node == nullptr) {
            return;
        }
        if (node->bounds.intersects(range)) {
            for (const T& data : node->data) {
                if (range.contains(data)) {
                    result.push_back(data);
                }
            }
            for (int i = 0; i < 4; ++i) {
                queryRange(node->children[i], range, result);
            }
        }
    }
    void nearestNeighbor(QuadtreeNode<T>* node, const Point& query,
                         QuadtreeNode<T>*& nearestNode, double& minDistance) const {
        if (node == nullptr) {
            return;
        }
        if (node->bounds.intersects(getBoundingCircle(query, minDistance))) {
            for (const T& data : node->data) {
                double distance = distanceBetweenPoints(query, data);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestNode = node;
                }
            }
            for (int i = 0; i < 4; ++i) {
                nearestNeighbor(node->children[i], query, nearestNode, minDistance);
            }
        }
    }
    Rectangle getBoundingCircle(const Point& center, double radius) const {
        return Rectangle(center.x - radius, center.y - radius, 2 * radius, 2 * radius);
    }
    void splitNode(QuadtreeNode<T>* node) {
        double x = node->bounds.x;
        double y = node->bounds.y;
        double width = node->bounds.width / 2;
        double height = node->bounds.height / 2;
        node->children[0] = new QuadtreeNode<T>(Rectangle(x, y, width, height));
        node->children[1] = new QuadtreeNode<T>(Rectangle(x + width, y, width, height));
        node->children[2] = new QuadtreeNode<T>(Rectangle(x, y + height, width, height));
        node->children[3] = new QuadtreeNode<T>(Rectangle(x + width, y + height, width, height));
        for (const T& data : node->data) {
            for (int i = 0; i < 4; ++i) {
                if (node->children[i]->bounds.contains(data)) {
                    insert(node->children[i], data);
                    break;
                }
            }
        }
        node->data.clear();
    }
    void inOrderTraversal(QuadtreeNode<T>* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->children[0]);
            for (const T& data : node->data) {
                std::cout << data << " ";
            }
            inOrderTraversal(node->children[1]);
            inOrderTraversal(node->children[2]);
            inOrderTraversal(node->children[3]);
        }
    }
    void preOrderTraversal(QuadtreeNode<T>* node) const {
        if (node != nullptr) {
            for (const T& data : node->data) {
                std::cout << data << " ";
            }
            preOrderTraversal(node->children[0]);
            preOrderTraversal(node->children[1]);
            preOrderTraversal(node->children[2]);
            preOrderTraversal(node->children[3]);
        }
    }
    void postOrderTraversal(QuadtreeNode<T>* node) const {
        if (node != nullptr) {
            postOrderTraversal(node->children[0]);
            postOrderTraversal(node->children[1]);
            postOrderTraversal(node->children[2]);
            postOrderTraversal(node->children[3]);
            for (const T& data : node->data) {
                std::cout << data << " ";
            }
        }
    }
    std::size_t count(QuadtreeNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        std::size_t count = node->data.size();
        for (int i = 0; i < 4; ++i) {
            count += count(node->children[i]);
        }
        return count;
    }
    double distanceBetweenPoints(const Point& a, const Point& b) const {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }
};
int main() {
    Quadtree<std::string> quadtree(Rectangle(0, 0, 10, 10));
    quadtree.insert(Point(2, 2), "A");
    quadtree.insert(Point(5, 4), "B");
    quadtree.insert(Point(9, 6), "C");
    quadtree.insert(Point(4, 7), "D");
    quadtree.insert(Point(8, 1), "E");
    std::cout << "In-Order Traversal: ";
    quadtree.inOrderTraversal();
    std::cout << "Pre-Order Traversal: ";
    quadtree.preOrderTraversal();
    std::cout << "Post-Order Traversal: ";
    quadtree.postOrderTraversal();
    Rectangle queryRange(3, 3, 4, 4);
    std::vector<std::string> result = quadtree.queryRange(queryRange);
    std::cout << "Points in the range: ";
    for (const std::string& point : result) {
        std::cout << point << " ";
    }
    std::cout << std::endl;
    Point queryPoint(6.0, 3.0);
    std::cout << "Nearest neighbor to query point (6.0, 3.0): "
              << quadtree.nearestNeighbor(queryPoint) << std::endl;
    quadtree.update(Point(5, 4), "F");
    std::cout << "In-Order Traversal (After Update): ";
    quadtree.inOrderTraversal();
    std::cout << "Number of points in the Quadtree: " << quadtree.count() << std::endl;
    std::cout << "Is it empty? " << (quadtree.isEmpty() ? "Yes" : "No") << std::endl;
    quadtree.clear();
    std::cout << "In-Order Traversal (After Clear): ";
    quadtree.inOrderTraversal();
    return 0;
}
