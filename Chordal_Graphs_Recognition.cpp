#include <iostream>
#include <vector>
#include <set>
class ChordalGraphRecognizer {
private:
    std::vector<std::vector<int>> graph;
    int vertices;
    bool isChordal() {
        for (int v = 0; v < vertices; ++v) {
            std::set<int> neighbors(graph[v].begin(), graph[v].end());
            for (int neighbor1 : neighbors) {
                for (int neighbor2 : neighbors) {
                    if (neighbor1 != neighbor2 && graph[neighbor1][neighbor2] == 0) {
                        bool commonNeighbor = false;
                        for (int neighbor3 : neighbors) {
                            if (neighbor3 != neighbor1 && neighbor3 != neighbor2 &&
                                graph[neighbor1][neighbor3] == 1 && graph[neighbor2][neighbor3] == 1) {
                                commonNeighbor = true;
                                break;
                            }
                        }
                        if (!commonNeighbor) {
                            std::cout << "The graph is not chordal." << std::endl;
                            return false;
                        }
                    }
                }
            }
        }
        std::cout << "The graph is chordal." << std::endl;
        return true;
    }
public:
    ChordalGraphRecognizer(int n) : vertices(n), graph(n, std::vector<int>(n, 0)) {}
    void addEdge(int u, int v) {
        graph[u][v] = graph[v][u] = 1;
    }
    void recognizeChordalGraph() {
        isChordal();
    }
};
int main() {
    int n, m; 
    std::cout << "Enter the number of vertices: ";
    std::cin >> n;
    std::cout << "Enter the number of edges: ";
    std::cin >> m;
    ChordalGraphRecognizer recognizer(n);
    std::cout << "Enter the edges (u v):" << std::endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        recognizer.addEdge(u, v);
    }
    recognizer.recognizeChordalGraph();
    return 0;
}
