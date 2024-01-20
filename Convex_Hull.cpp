#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    static bool compare(const Point& p1, const Point& p2) {
        if (p1.y == p2.y) {
            return p1.x < p2.x;
        }
        return p1.y < p2.y;
    }
};
int crossProduct(const Point& p0, const Point& p1, const Point& p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}
std::vector<Point> convexHull(std::vector<Point>& points) {
    if (points.size() < 3) {
        return {};
    }
    auto pivot = std::min_element(points.begin(), points.end(), Point::compare);
    std::sort(points.begin(), points.end(), [pivot](const Point& p1, const Point& p2) {
        int cross = crossProduct(*pivot, p1, p2);
        if (cross == 0) {
            return Point::compare(p1, p2);
        }
        return cross > 0;
    });
    std::stack<Point> hullStack;
    hullStack.push(points[0]);
    hullStack.push(points[1]);
    for (size_t i = 2; i < points.size(); ++i) {
        while (hullStack.size() >= 2) {
            Point p1 = hullStack.top();
            hullStack.pop();
            Point p0 = hullStack.top();
            if (crossProduct(p0, p1, points[i]) > 0) {
                hullStack.push(p1);
                break;
            }
        }
        hullStack.push(points[i]);
    }
    std::vector<Point> convexHullPoints;
    while (!hullStack.empty()) {
        convexHullPoints.push_back(hullStack.top());
        hullStack.pop();
    }
    std::reverse(convexHullPoints.begin(), convexHullPoints.end());
    return convexHullPoints;
}
int main() {
    std::vector<Point> points = {{0, 0}, {1, 1}, {2, 2}, {3, 1}, {2, 0}, {1, 2}, {2, 3}};
    std::vector<Point> convexHullPoints = convexHull(points);
    std::cout << "Convex Hull Points:" << std::endl;
    for (const auto& point : convexHullPoints) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }
    return 0;
}
