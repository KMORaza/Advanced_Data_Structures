#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class BipartiteGraph {
private:
    int vertices;
    vector<vector<int>> adjacencyList;
public:
    BipartiteGraph(int v) : vertices(v), adjacencyList(v) {}
    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }
    bool isBipartite() {
        vector<int> color(vertices, -1);
        queue<int> q;
        for (int i = 0; i < vertices; ++i) {
            if (color[i] == -1) {
                color[i] = 0; 
                q.push(i);
                while (!q.empty()) {
                    int current = q.front();
                    q.pop();
                    for (int neighbor : adjacencyList[current]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[current];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[current]) {
                            return false; 
                        }
                    }
                }
            }
        }
        return true; 
    }
};
int main() {
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;
    BipartiteGraph graph(vertices);
    cout << "Enter the edges (format: u v):" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }
    if (graph.isBipartite()) {
        cout << "The graph is Bipartite." << endl;
    } else {
        cout << "The graph is not Bipartite." << endl;
    }
    return 0;
}
