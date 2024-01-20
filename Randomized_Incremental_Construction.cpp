#include <iostream>
#include <vector>
#include <algorithm>
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};
int orientation(const Point& p, const Point& q, const Point& r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;  
}
std::vector<Point> convexHullRIC(std::vector<Point>& points) {
    std::vector<Point> hull;
    std::sort(points.begin(), points.end());
    hull.push_back(points[0]);
    hull.push_back(points.back());
    std::vector<Point> upSet, downSet;
    for (size_t i = 1; i < points.size() - 1; ++i) {
        int orientationVal = orientation(points[0], points.back(), points[i]);
        if (orientationVal == 2) {
            upSet.push_back(points[i]);
        } else if (orientationVal == 1) {
            downSet.push_back(points[i]);
        }
    }
    for (const Point& p : upSet) {
        while (hull.size() >= 2 && orientation(hull[hull.size() - 2], hull.back(), p) != 2) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    for (const Point& p : downSet) {
        while (hull.size() >= 2 && orientation(hull[hull.size() - 2], hull.back(), p) != 2) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    return hull;
}
int main() {
    int n;
    std::cout << "Enter the number of points: ";
    std::cin >> n;
    std::vector<Point> points;
    std::cout << "Enter the coordinates of each point (x y):" << std::endl;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }
    std::vector<Point> convexHull = convexHullRIC(points);
    std::cout << "Convex Hull Points:" << std::endl;
    for (const Point& p : convexHull) {
        std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
    }
    return 0;
}
