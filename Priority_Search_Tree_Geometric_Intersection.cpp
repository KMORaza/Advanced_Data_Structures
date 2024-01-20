#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};
struct Event {
    enum Type { OPEN, CLOSE, POINT };
    Type type;
    Point point;
    int index;
    Event(Type type, const Point& point, int index) : type(type), point(point), index(index) {}
    bool operator<(const Event& other) const {
        return point.y < other.point.y;
    }
};
struct Node {
    Point point;
    Node* left;
    Node* right;
    Node(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};
struct CompareEventsX {
    bool operator()(const Event& a, const Event& b) const {
        return a.point.x < b.point.x || (a.point.x == b.point.x && a.type < b.type);
    }
};
struct ComparePointsY {
    bool operator()(const Point& a, const Point& b) const {
        return a.y < b.y || (a.y == b.y && a.x < b.x);
    }
};
class PST {
private:
    Node* root;
    Node* buildPST(vector<Event>& events) {
        if (events.empty()) {
            return nullptr;
        }
        sort(events.begin(), events.end(), CompareEventsX());
        int mid = events.size() / 2;
        Node* node = new Node(events[mid].point);
        vector<Event> leftEvents(events.begin(), events.begin() + mid);
        vector<Event> rightEvents(events.begin() + mid + 1, events.end());
        node->left = buildPST(leftEvents);
        node->right = buildPST(rightEvents);
        return node;
    }
    void verticalLineSweep(Node* node, set<Point, ComparePointsY>& status, vector<pair<Point, Point>>& intersections) {
        if (node == nullptr) {
            return;
        }
        verticalLineSweep(node->left, status, intersections);
        if (node->point.y > status.begin()->y) {
            auto it = status.lower_bound(node->point);
            if (it != status.begin()) {
                --it;
                Point p1 = min(node->point, *it);
                Point p2 = max(node->point, *it);
                intersections.emplace_back(p1, p2);
            }
            status.erase(node->point);
        }
        status.insert(node->point);
        verticalLineSweep(node->right, status, intersections);
    }
public:
    PST(vector<Point>& points) {
        vector<Event> events;
        for (int i = 0; i < points.size(); ++i) {
            events.emplace_back(Event::OPEN, points[i], i);
            events.emplace_back(Event::CLOSE, points[i], i);
            events.emplace_back(Event::POINT, points[i], i);
        }
        sort(events.begin(), events.end());
        root = buildPST(events);
    }
    vector<pair<Point, Point>> findIntersections() {
        set<Point, ComparePointsY> status;
        vector<pair<Point, Point>> intersections;
        verticalLineSweep(root, status, intersections);
        return intersections;
    }
};
int main() {
    vector<Point> points = {
        {1, 5},
        {2, 3},
        {3, 6},
        {4, 8},
        {5, 7},
        {6, 4}
    };
    PST pst(points);
    vector<pair<Point, Point>> intersections = pst.findIntersections();
    cout << "Intersections:" << endl;
    for (const auto& intersection : intersections) {
        cout << "(" << intersection.first.x << ", " << intersection.first.y << ") - ";
        cout << "(" << intersection.second.x << ", " << intersection.second.y << ")" << endl;
    }
    return 0;
}
