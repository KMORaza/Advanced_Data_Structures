// Implementing Uniform Spanning Tree using Scheiber-Vishkin algorithm 
#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <ctime>
class Graph {
private:
    int vertices;
    std::vector<std::vector<int>> adjacencyMatrix;
public:
    Graph(int V) : vertices(V), adjacencyMatrix(V, std::vector<int>(V, 0)) {}
    void addEdge(int u, int v) {
        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1;
    }
    std::vector<int> schieberVishkin() {
        std::vector<int> parent(vertices, -1);
        std::vector<int> depth(vertices, -1);
        std::vector<int> ancestors(vertices, -1);
        std::queue<int> q;
        std::mt19937 rng(static_cast<unsigned>(std::time(0)));
        std::uniform_int_distribution<int> dist(0, vertices - 1);
        int root = dist(rng);
        q.push(root);
        depth[root] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < vertices; ++v) {
                if (adjacencyMatrix[u][v] && parent[v] == -1) {
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    ancestors[v] = u;
                    q.push(v);
                } else if (depth[u] > depth[v] && ancestors[u] != v) {
                    for (int w = u; w != v; w = parent[w]) {
                        if (depth[w] < depth[v]) {
                            parent[w] = v;
                            depth[w] = depth[v] + 1;
                            ancestors[w] = v;
                            q.push(w);
                        }
                    }
                }
            }
        }
        return parent;
    }
};
int main() {
    int V, E;
    std::cout << "Enter the number of vertices and edges: ";
    std::cin >> V >> E;
    Graph graph(V);
    std::cout << "Enter the edges (u v):" << std::endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }
    std::vector<int> spanningTree = graph.schieberVishkin();
    std::cout << "Uniform Spanning Tree (parent of each vertex):" << std::endl;
    for (int i = 0; i < V; ++i) {
        std::cout << i << " -> " << spanningTree[i] << std::endl;
    }
    return 0;
}
