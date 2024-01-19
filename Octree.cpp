#include <iostream>
#include <vector>
#include <cmath>
class Point {
public:
    double x, y, z;
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
};
class OctreeNode {
public:
    Point center;
    double size;
    std::vector<Point> points;
    OctreeNode* children[8];
    OctreeNode(const Point& center, double size) : center(center), size(size) {
        for (int i = 0; i < 8; ++i) {
            children[i] = nullptr;
        }
    }
    ~OctreeNode() {
        for (int i = 0; i < 8; ++i) {
            delete children[i];
        }
    }
};
class Octree {
public:
    Octree(const Point& center, double size) : root(new OctreeNode(center, size)) {}
    ~Octree() {
        clear();
    }
    void insert(const Point& point) {
        insert(root, point);
    }
    bool search(const Point& point) const {
        return search(root, point);
    }
    std::vector<Point> queryRange(const Point& center, double size) const {
        std::vector<Point> result;
        queryRange(root, center, size, result);
        return result;
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
    void clear() {
        delete root;
        root = new OctreeNode(Point(0, 0, 0), 1.0);
    }
private:
    OctreeNode* root;
    void insert(OctreeNode* node, const Point& point) {
        if (node->size == 0.0) {
            return;
        }
        int octant = getOctant(node->center, point);
        if (node->children[octant] == nullptr) {
            double childSize = node->size / 2.0;
            Point childCenter = getChildCenter(node->center, octant, childSize);
            node->children[octant] = new OctreeNode(childCenter, childSize);
        }
        insert(node->children[octant], point);
    }
    bool search(OctreeNode* node, const Point& point) const {
        if (node->size == 0.0) {
            return false;
        }
        int octant = getOctant(node->center, point);
        if (node->children[octant] == nullptr) {
            return false;
        }
        if (node->children[octant]->size == 0.0) {
            for (const Point& p : node->children[octant]->points) {
                if (p.x == point.x && p.y == point.y && p.z == point.z) {
                    return true;
                }
            }
            return false;
        }
        return search(node->children[octant], point);
    }
    void queryRange(OctreeNode* node, const Point& center, double size, std::vector<Point>& result) const {
        if (node->size == 0.0) {
            return;
        }
        int octant = getOctant(node->center, center);
        if (node->children[octant] == nullptr) {
            return;
        }
        if (node->children[octant]->size == 0.0) {
            for (const Point& p : node->children[octant]->points) {
                if (isInsideRange(p, center, size)) {
                    result.push_back(p);
                }
            }
            return;
        }
        queryRange(node->children[octant], center, size, result);
        for (int i = 0; i < 8; ++i) {
            if (i != octant) {
                queryRange(node->children[i], center, size, result);
            }
        }
    }
    void inOrderTraversal(OctreeNode* node) const {
        if (node != nullptr) {
            for (int i = 0; i < 8; ++i) {
                inOrderTraversal(node->children[i]);
            }
            for (const Point& point : node->points) {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
            }
        }
    }
    void preOrderTraversal(OctreeNode* node) const {
        if (node != nullptr) {
            for (const Point& point : node->points) {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
            }
            for (int i = 0; i < 8; ++i) {
                preOrderTraversal(node->children[i]);
            }
        }
    }
    void postOrderTraversal(OctreeNode* node) const {
        if (node != nullptr) {
            for (int i = 0; i < 8; ++i) {
                postOrderTraversal(node->children[i]);
            }
            for (const Point& point : node->points) {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
            }
        }
    }
    int getOctant(const Point& center, const Point& point) const {
        int octant = 0;
        if (point.x > center.x) octant |= 1;
        if (point.y > center.y) octant |= 2;
        if (point.z > center.z) octant |= 4;
        return octant;
    }
    Point getChildCenter(const Point& center, int octant, double childSize) const {
        double xOffset = (octant & 1) ? childSize : -childSize;
        double yOffset = (octant & 2) ? childSize : -childSize;
        double zOffset = (octant & 4) ? childSize : -childSize;
        return Point(center.x + xOffset, center.y + yOffset, center.z + zOffset);
    }
    bool isInsideRange(const Point& point, const Point& center, double size) const {
        double halfSize = size / 2.0;
        return point.x >= center.x - halfSize && point.x <= center.x + halfSize &&
               point.y >= center.y - halfSize && point.y <= center.y + halfSize &&
               point.z >= center.z - halfSize && point.z <= center.z + halfSize;
    }
};
int main() {
    Octree octree(Point(0, 0, 0), 10.0);
    octree.insert(Point(2, 2, 2));
    octree.insert(Point(5, 4, 3));
    octree.insert(Point(9, 6, 7));
    octree.insert(Point(4, 7, 1));
    octree.insert(Point(8, 1, 5));
    std::cout << "In-Order Traversal: ";
    octree.inOrderTraversal();
    std::cout << "Pre-Order Traversal: ";
    octree.preOrderTraversal();
    std::cout << "Post-Order Traversal: ";
    octree.postOrderTraversal();
    Point searchPoint(4, 7, 1);
    std::cout << "Search for point (" << searchPoint.x << ", " << searchPoint.y << ", " << searchPoint.z
              << "): " << (octree.search(searchPoint) ? "Found" : "Not Found") << std::endl;
    Point queryCenter(5, 5, 5);
    double querySize = 4.0;
    std::vector<Point> pointsInRange = octree.queryRange(queryCenter, querySize);
    std::cout << "Points in Range (" << queryCenter.x << ", " << queryCenter.y << ", " << queryCenter.z
              << ") with Size " << querySize << ": ";
    for (const Point& point : pointsInRange) {
        std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
    }
    std::cout << std::endl;
    octree.clear();
    std::cout << "In-Order Traversal (After Clear): ";
    octree.inOrderTraversal();
    return 0;
}
