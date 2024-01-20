// Implementation of all pair shortest path using Johnson's algorithm
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
struct Edge {
    int source, destination, weight;
};
void addEdge(std::vector<std::vector<Edge>>& graph, int source, int destination, int weight) {
    graph[source].push_back({source, destination, weight});
}
bool bellmanFord(std::vector<std::vector<Edge>>& graph, std::vector<int>& h) {
    int V = graph.size();
    std::vector<int> dist(V, INT_MAX);
    dist[0] = 0;
    for (int i = 0; i < V - 1; ++i) {
        for (const auto& edges : graph) {
            for (const Edge& edge : edges) {
                if (dist[edge.source] != INT_MAX && dist[edge.source] + edge.weight < dist[edge.destination]) {
                    dist[edge.destination] = dist[edge.source] + edge.weight;
                }
            }
        }
    }
    for (const auto& edges : graph) {
        for (const Edge& edge : edges) {
            if (dist[edge.source] != INT_MAX && dist[edge.source] + edge.weight < dist[edge.destination]) {
                return false; 
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        h[i] = dist[i];
    }
    return true;
}
std::vector<int> dijkstra(const std::vector<std::vector<Edge>>& graph, int source, const std::vector<int>& h) {
    int V = graph.size();
    std::vector<int> dist(V, INT_MAX);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    dist[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight + h[u] - h[v];
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        if (dist[i] != INT_MAX) {
            dist[i] -= h[i];
        }
    }
    return dist;
}
std::vector<std::vector<int>> johnsonsAlgorithm(std::vector<std::vector<Edge>>& graph) {
    int V = graph.size();
    for (int i = 0; i < V; ++i) {
        addEdge(graph, V, i, 0);
    }
    std::vector<int> h(V + 1, 0);
    if (!bellmanFord(graph, h)) {
        std::cout << "Graph contains a negative-weight cycle. Johnson's Algorithm cannot be applied." << std::endl;
        return {};
    }
    std::vector<std::vector<int>> shortestPaths(V, std::vector<int>(V, INT_MAX));
    for (int i = 0; i < V; ++i) {
        std::vector<int> dist = dijkstra(graph, i, h);
        shortestPaths[i] = dist;
    }
    return shortestPaths;
}
int main() {
    int V, E;
    std::cout << "Enter the number of vertices and edges: ";
    std::cin >> V >> E;
    std::vector<std::vector<Edge>> graph(V);
    std::cout << "Enter the edges (source destination weight):" << std::endl;
    for (int i = 0; i < E; ++i) {
        int source, destination, weight;
        std::cin >> source >> destination >> weight;
        addEdge(graph, source, destination, weight);
    }
    std::vector<std::vector<int>> shortestPaths = johnsonsAlgorithm(graph);
    std::cout << "Shortest Paths:" << std::endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (shortestPaths[i][j] == INT_MAX) {
                std::cout << "INF\t";
            } else {
                std::cout << shortestPaths[i][j] << "\t";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
