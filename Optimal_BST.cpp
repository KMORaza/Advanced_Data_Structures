#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
class OptimalBST {
private:
    std::vector<double> keys; 
    std::vector<double> freq; 
    std::vector<std::vector<double>> dp; 
    std::vector<std::vector<int>> root; 
public:
    OptimalBST(const std::vector<double>& keys, const std::vector<double>& freq)
        : keys(keys), freq(freq) {}
    double calculateCost(int i, int j) {
        double cost = 0.0;
        for (int k = i; k <= j; ++k) {
            cost += freq[k];
        }
        return cost;
    }
    void constructOptimalBST() {
        int n = keys.size();
        dp.resize(n, std::vector<double>(n, 0.0));
        root.resize(n, std::vector<int>(n, -1));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = freq[i];
            root[i][i] = i;
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = std::numeric_limits<double>::infinity();
                for (int r = i; r <= j; ++r) {
                    double c = (r > i) ? dp[i][r - 1] : 0;
                    c += (r < j) ? dp[r + 1][j] : 0;
                    c += calculateCost(i, j);
                    if (c < dp[i][j]) {
                        dp[i][j] = c;
                        root[i][j] = r;
                    }
                }
            }
        }
    }
    void printOptimalBST(int i, int j, bool isRoot) {
        if (i <= j) {
            int r = root[i][j];
            if (isRoot) {
                std::cout << "Root: " << keys[r] << std::endl;
            } else {
                std::cout << "Left child of " << keys[j] << ": " << keys[r] << std::endl;
            }
            printOptimalBST(i, r - 1, false);
            printOptimalBST(r + 1, j, false);
        }
    }
    void displayOptimalBST() {
        std::cout << "Optimal Binary Search Tree:" << std::endl;
        printOptimalBST(0, keys.size() - 1, true);
    }
};
int main() {
    std::vector<double> keys = {10, 12, 20};
    std::vector<double> freq = {34, 8, 50};
    OptimalBST optimalBST(keys, freq);
    optimalBST.constructOptimalBST();
    optimalBST.displayOptimalBST();
    return 0;
}
