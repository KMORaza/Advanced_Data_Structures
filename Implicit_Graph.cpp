#include <iostream>
#include <vector>
#include <functional>
class ImplicitGraph {
private:
    int numNodes;
    std::function<std::vector<int>(int)> adjacencyFunction;
public:
    ImplicitGraph(int nodes, const std::function<std::vector<int>(int)>& adjacencyFunc)
        : numNodes(nodes), adjacencyFunction(adjacencyFunc) {}
    void printNeighbors(int node) const {
        std::vector<int> neighbors = adjacencyFunction(node);
        std::cout << "Neighbors of Node " << node << ": ";
        for (int neighbor : neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
};
int main() {
    auto adjacencyFunc = [](int node) -> std::vector<int> {
        std::vector<int> neighbors;
        if (node == 0) {
            neighbors = {1, 2};
        } else if (node == 1) {
            neighbors = {0, 3};
        } else if (node == 2) {
            neighbors = {0};
        } else if (node == 3) {
            neighbors = {1};
        }
        return neighbors;
    };
    ImplicitGraph graph(4, adjacencyFunc);
    for (int i = 0; i < 4; ++i) {
        graph.printNeighbors(i);
    }
    return 0;
}
