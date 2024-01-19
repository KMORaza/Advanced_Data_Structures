// Basic implementation of Quad Tree
#include <iostream>
#include <vector>
struct Point {
    double x;
    double y;
    Point(double x, double y) : x(x), y(y) {}
};
struct Rectangle {
    double x; 
    double y; 
    double width;
    double height;
    Rectangle(double x, double y, double width, double height)
        : x(x), y(y), width(width), height(height) {}
    bool contains(const Point& point) const {
        return (point.x >= x && point.x <= x + width && point.y >= y && point.y <= y + height);
    }
    bool intersects(const Rectangle& other) const {
        return (x < other.x + other.width && x + width > other.x && y < other.y + other.height && y + height > other.y);
    }
};
template <typename T>
struct QuadNode {
    Rectangle boundary;
    std::vector<Point> points;
    QuadNode* NW; 
    QuadNode* NE; 
    QuadNode* SW; 
    QuadNode* SE; 
    QuadNode(const Rectangle& boundary) : boundary(boundary), NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}
};
template <typename T>
class Quadtree {
public:
    Quadtree(const Rectangle& boundary) : root(new QuadNode<T>(boundary)) {}
    void insert(const Point& point) {
        insert(root, point);
    }
    std::vector<Point> queryRange(const Rectangle& range) const {
        std::vector<Point> result;
        queryRange(root, range, result);
        return result;
    }
private:
    QuadNode<T>* root;
    void insert(QuadNode<T>*& node, const Point& point) {
        if (!node->boundary.contains(point)) {
            return;
        }
        if (node->points.size() < MAX_POINTS_PER_NODE) {
            node->points.push_back(point);
        } else {
            if (node->NW == nullptr) {
                subdivide(node);
            }
            insert(node->NW, point);
            insert(node->NE, point);
            insert(node->SW, point);
            insert(node->SE, point);
        }
    }
    void subdivide(QuadNode<T>*& node) {
        double x = node->boundary.x;
        double y = node->boundary.y;
        double w = node->boundary.width;
        double h = node->boundary.height;
        Rectangle NW(x, y + h / 2, w / 2, h / 2);
        Rectangle NE(x + w / 2, y + h / 2, w / 2, h / 2);
        Rectangle SW(x, y, w / 2, h / 2);
        Rectangle SE(x + w / 2, y, w / 2, h / 2);
        node->NW = new QuadNode<T>(NW);
        node->NE = new QuadNode<T>(NE);
        node->SW = new QuadNode<T>(SW);
        node->SE = new QuadNode<T>(SE);
    }
    void queryRange(const QuadNode<T>* node, const Rectangle& range, std::vector<Point>& result) const {
        if (node == nullptr) {
            return;
        }
        if (!node->boundary.intersects(range)) {
            return;
        }
        for (const Point& point : node->points) {
            if (range.contains(point)) {
                result.push_back(point);
            }
        }
        queryRange(node->NW, range, result);
        queryRange(node->NE, range, result);
        queryRange(node->SW, range, result);
        queryRange(node->SE, range, result);
    }
    static const int MAX_POINTS_PER_NODE = 4;
};
int main() {
    Rectangle boundary(0, 0, 10, 10);
    Quadtree<int> quadtree(boundary);
    quadtree.insert(Point(2, 3));
    quadtree.insert(Point(5, 4));
    quadtree.insert(Point(9, 6));
    quadtree.insert(Point(4, 7));
    quadtree.insert(Point(8, 1));
    Rectangle queryRange(3, 2, 3, 3);
    std::vector<Point> result = quadtree.queryRange(queryRange);
    std::cout << "Points within the range: ";
    for (const Point& point : result) {
        std::cout << "(" << point.x << ", " << point.y << ") ";
    }
    std::cout << std::endl;
    return 0;
}
