#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};
struct Edge {
    int i, j;
    Edge(int i, int j) : i(i), j(j) {}
};
double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}
bool isEdgeInsideCircle(const Point& a, const Point& b, const Point& c, const Point& d) {
    double ax = a.x - d.x;
    double ay = a.y - d.y;
    double bx = b.x - d.x;
    double by = b.y - d.y;
    double cx = c.x - d.x;
    double cy = c.y - d.y;
    double det = ax * (by * cx - bx * cy) - ay * (bx * cx - by * cy) + (ax * by - ay * bx) * cx;
    return det > 0;
}
std::vector<Edge> delaunayTriangulation(const std::vector<Point>& points) {
    std::vector<Edge> edges;
    std::vector<Point> sortedPoints = points;
    std::sort(sortedPoints.begin(), sortedPoints.end(), [](const Point& p1, const Point& p2) {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    });
    for (int i = 0; i < sortedPoints.size(); ++i) {
        for (int j = i + 1; j < sortedPoints.size(); ++j) {
            bool validEdge = true;
            for (int k = 0; k < sortedPoints.size(); ++k) {
                if (k != i && k != j) {
                    if (isEdgeInsideCircle(sortedPoints[i], sortedPoints[j], sortedPoints[k], sortedPoints[k])) {
                        validEdge = false;
                        break;
                    }
                }
            }
            if (validEdge) {
                edges.emplace_back(i, j);
            }
        }
    }
    return edges;
}
std::vector<Edge> concaveHull(const std::vector<Point>& points, double alpha) {
    std::vector<Edge> delaunayEdges = delaunayTriangulation(points);
    std::vector<Edge> concaveHullEdges;
    for (const auto& edge : delaunayEdges) {
        Point p1 = points[edge.i];
        Point p2 = points[edge.j];
        double dist = distance(p1, p2);
        if (dist <= alpha) {
            concaveHullEdges.emplace_back(edge);
        }
    }
    return concaveHullEdges;
}
int main() {
    int numPoints;
    std::cout << "Enter the number of points: ";
    std::cin >> numPoints;
    std::vector<Point> points;
    std::cout << "Enter the points (format: x y):" << std::endl;
    for (int i = 0; i < numPoints; ++i) {
        double x, y;
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }
    double alpha;
    std::cout << "Enter the alpha parameter: ";
    std::cin >> alpha;
    std::vector<Edge> concaveHullEdges = concaveHull(points, alpha);
    if (concaveHullEdges.empty()) {
        std::cout << "No Concave Hull edges found." << std::endl;
    } else {
        std::cout << "Concave Hull edges:" << std::endl;
        for (const auto& edge : concaveHullEdges) {
            std::cout << "(" << points[edge.i].x << ", " << points[edge.i].y << ") - "
                      << "(" << points[edge.j].x << ", " << points[edge.j].y << ")" << std::endl;
        }
    }
    return 0;
}
/*
// This implementation of Concave Hull involves use of CGAL library 
#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Alpha_shape_2.h>
#include <CGAL/Alpha_shape_vertex_base_2.h>
#include <CGAL/Alpha_shape_face_base_2.h>
#include <CGAL/Alpha_shape_cell_base_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Alpha_shape_vertex_base_2<K> Vb;
typedef CGAL::Alpha_shape_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Delaunay;
typedef CGAL::Alpha_shape_2<Delaunay> Alpha_shape_2;
typedef K::Point_2 Point;
int main() {
    std::vector<Point> points = {{0, 0}, {1, 1}, {2, 0}, {3, 3}, {4, 1}};
    Delaunay dt;
    dt.insert(points.begin(), points.end());
    Alpha_shape_2 alpha_shape(dt);
    alpha_shape.set_alpha(0.1); 
    std::vector<Point> result;
    alpha_shape.points(std::back_inserter(result));
    std::cout << "Concave Hull points:" << std::endl;
    for (const auto& p : result) {
        std::cout << "(" << p.x() << ", " << p.y() << ")" << std::endl;
    }
    return 0;
}
*/
