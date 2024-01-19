#include <iostream>
#include <vector>
class Node {
public:
    Node* left;
    Node* right;
    Node* up;
    Node* down;
    int row;
    int col;
    Node(int r, int c) : left(nullptr), right(nullptr), up(nullptr), down(nullptr), row(r), col(c) {}
};
class DancingLinks {
private:
    std::vector<Node*> headerNodes;
    std::vector<std::vector<bool>> matrix;
    std::vector<int> solution;
public:
    DancingLinks(int numRows, int numCols) {
        initializeHeaders(numCols);
        initializeMatrix(numRows, numCols);
    }
    void addRow(const std::vector<int>& row) {
        int rowIndex = matrix.size();
        for (int colIndex : row) {
            Node* newNode = new Node(rowIndex, colIndex);
            insertNode(newNode, headerNodes[colIndex]);
        }
        matrix.push_back(std::vector<bool>(headerNodes.size(), false));
        for (int colIndex : row) {
            matrix[rowIndex][colIndex] = true;
        }
    }
    bool solve() {
        solution.clear();
        return search(0);
    }
    const std::vector<int>& getSolution() const {
        return solution;
    }
private:
    void initializeHeaders(int numCols) {
        for (int i = 0; i <= numCols; ++i) {
            Node* newNode = new Node(-1, i);
            newNode->left = headerNodes.back();
            headerNodes.back()->right = newNode;
            headerNodes.push_back(newNode);
        }
        headerNodes[0]->left = headerNodes.back();
        headerNodes.back()->right = headerNodes[0];
    }
    void initializeMatrix(int numRows, int numCols) {
        matrix.resize(numRows, std::vector<bool>(numCols, false));
    }
    void insertNode(Node* newNode, Node* header) {
        newNode->up = header->up;
        newNode->down = header;
        header->up->down = newNode;
        header->up = newNode;
    }
    void removeNode(Node* node) {
        node->left->right = node->right;
        node->right->left = node->left;
        Node* rowNode = node->down;
        while (rowNode != node) {
            Node* colNode = rowNode->right;
            while (colNode != rowNode) {
                colNode->up->down = colNode->down;
                colNode->down->up = colNode->up;
                colNode = colNode->right;
            }
            rowNode = rowNode->down;
        }
    }
    void restoreNode(Node* node) {
        Node* rowNode = node->up;
        while (rowNode != node) {
            Node* colNode = rowNode->left;
            while (colNode != rowNode) {
                colNode->up->down = colNode;
                colNode->down->up = colNode;
                colNode = colNode->left;
            }
            rowNode = rowNode->up;
        }
        node->left->right = node;
        node->right->left = node;
    }
    bool search(int k) {
        if (headerNodes[0]->right == headerNodes[0]) {
            return true; 
        }
        Node* column = chooseColumn();
        coverColumn(column);
        Node* row = column->down;
        while (row != column) {
            solution.push_back(row->row);
            Node* colNode = row->right;
            while (colNode != row) {
                coverColumn(headerNodes[colNode->col]);
                colNode = colNode->right;
            }
            if (search(k + 1)) {
                return true;
            }
            solution.pop_back();
            colNode = row->left;
            while (colNode != row) {
                uncoverColumn(headerNodes[colNode->col]);
                colNode = colNode->left;
            }
            row = row->down;
        }
        uncoverColumn(column);
        return false;
    }
    Node* chooseColumn() {
        Node* minColumn = headerNodes[0]->right;
        Node* currentColumn = minColumn->right;
        while (currentColumn != headerNodes[0]) {
            if (currentColumn->col < minColumn->col) {
                minColumn = currentColumn;
            }
            currentColumn = currentColumn->right;
        }
        return minColumn;
    }
    void coverColumn(Node* column) {
        column->left->right = column->right;
        column->right->left = column->left;
        Node* rowNode = column->down;
        while (rowNode != column) {
            Node* colNode = rowNode->right;
            while (colNode != rowNode) {
                colNode->up->down = colNode->down;
                colNode->down->up = colNode->up;
                colNode = colNode->right;
            }
            rowNode = rowNode->down;
        }
    }
    void uncoverColumn(Node* column) {
        Node* rowNode = column->up;
        while (rowNode != column) {
            Node* colNode = rowNode->left;
            while (colNode != rowNode) {
                colNode->up->down = colNode;
                colNode->down->up = colNode;
                colNode = colNode->left;
            }
            rowNode = rowNode->up;
        }
        column->left->right = column;
        column->right->left = column;
    }
};
int main() {
    DancingLinks dl(7, 7);
    dl.addRow({0, 3, 4});
    dl.addRow({1, 4, 5});
    dl.addRow({0, 2, 5});
    dl.addRow({1, 3});
    dl.addRow({2, 4, 6});
    dl.addRow({0, 3, 6});
    dl.addRow({2, 5, 6});
    if (dl.solve()) {
        const std::vector<int>& solution = dl.getSolution();
        std::cout << "Solution found: ";
        for (int row : solution) {
            std::cout << row << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No solution found.\n";
    }
    return 0;
}
