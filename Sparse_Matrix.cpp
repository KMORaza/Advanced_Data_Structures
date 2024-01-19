#include <iostream>
#include <vector>
class SparseMatrix {
private:
    struct Element {
        int row;
        int col;
        int value;
        Element(int r, int c, int v) : row(r), col(c), value(v) {}
    };
    int numRows;
    int numCols;
    std::vector<Element> elements;
public:
    SparseMatrix(int rows, int cols) : numRows(rows), numCols(cols) {}
    void insert(int row, int col, int value) {
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
            std::cerr << "Error: Index out of bounds\n";
            return;
        }
        if (value != 0) {
            elements.push_back(Element(row, col, value));
        }
    }
    void printMatrix() const {
        std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 0));
        for (const Element& element : elements) {
            matrix[element.row][element.col] = element.value;
        }
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};
int main() {
    SparseMatrix sparseMat(5, 5);
    sparseMat.insert(0, 1, 2);
    sparseMat.insert(1, 2, 3);
    sparseMat.insert(2, 3, 4);
    sparseMat.insert(3, 4, 5);
    sparseMat.printMatrix();
    return 0;
}
