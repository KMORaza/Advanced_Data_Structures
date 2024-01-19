#include <iostream>
#include <vector>
class FenwickTree {
public:
    FenwickTree(std::size_t size) : size(size), tree(size + 1, 0) {}
    FenwickTree(const std::vector<int>& values) : size(values.size()), tree(size + 1, 0) {
        for (std::size_t i = 0; i < size; ++i) {
            update(i, values[i]);
        }
    }
    void update(std::size_t i, int delta) {
        ++i; 
        while (i <= size) {
            tree[i] += delta;
            i += i & -i;
        }
    }
    int prefixSum(std::size_t i) const {
        ++i; 
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & -i; 
        }
        return sum;
    }
    int rangeSum(std::size_t left, std::size_t right) const {
        if (left == 0) {
            return prefixSum(right);
        } else {
            return prefixSum(right) - prefixSum(left - 1);
        }
    }
private:
    std::size_t size;
    std::vector<int> tree;
};
int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};
    FenwickTree fenwick(values);
    std::cout << "Prefix Sums: ";
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << fenwick.prefixSum(i) << " ";
    }
    std::cout << std::endl;
    fenwick.update(2, 6);
    std::cout << "Prefix Sums after Update: ";
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << fenwick.prefixSum(i) << " ";
    }
    std::cout << std::endl;
    std::size_t left = 1, right = 3;
    int sumInRange = fenwick.rangeSum(left, right);
    std::cout << "Sum in range [" << left << ", " << right << "]: " << sumInRange << std::endl;
    return 0;
}
