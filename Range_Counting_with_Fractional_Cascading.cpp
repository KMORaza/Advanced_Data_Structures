#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class FractionalCascading {
private:
    vector<vector<int>> data;
    vector<vector<int>> prefixSum;
public:
    FractionalCascading(const vector<vector<int>>& arrays) {
        int rows = arrays.size();
        int cols = arrays[0].size();
        data = arrays;
        prefixSum.resize(rows + 1, vector<int>(cols + 1, 0));
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + data[i - 1][j - 1];
            }
        }
        for (int i = 0; i < rows; ++i) {
            sort(data[i].begin(), data[i].end());
        }
    }
    int countInRange(int rowStart, int rowEnd, int colStart, int colEnd, int value) {
        int count = 0;
        for (int i = rowStart; i <= rowEnd; ++i) {
            int colPos = upper_bound(data[i].begin(), data[i].end(), value) - data[i].begin();
            count += prefixSum[i][colPos + colEnd] - prefixSum[i][colPos + colStart - 1];
        }
        return count;
    }
};
int main() {
    vector<vector<int>> arrays = {
        {1, 3, 5, 7},
        {2, 4, 6, 8},
        {1, 2, 3, 4}
    };
    FractionalCascading fc(arrays);
    int result = fc.countInRange(0, 2, 1, 3, 5);
    cout << "Number of elements less than or equal to 5 in the specified range: " << result << endl;
    return 0;
}
