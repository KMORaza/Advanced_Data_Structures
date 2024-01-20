#include <iostream>
#include <vector>
class SlidingWindowTree {
private:
    std::vector<int> fenwickTree;
public:
    SlidingWindowTree(int n) : fenwickTree(n + 1, 0) {}
    void update(int index, int delta) {
        index++;
        while (index < fenwickTree.size()) {
            fenwickTree[index] += delta;
            index += index & -index;
        }
    }
    int query(int index) {
        index++; 
        int sum = 0;
        while (index > 0) {
            sum += fenwickTree[index];
            index -= index & -index; 
        }
        return sum;
    }
    int rangeQuery(int left, int right) {
        return query(right) - (left > 0 ? query(left - 1) : 0);
    }
};
int main() {
    int n;
    std::cout << "Enter the size of the array: ";
    std::cin >> n;
    SlidingWindowTree swt(n);
    std::cout << "Enter the elements of the array:" << std::endl;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        swt.update(i, value);
    }
    int left, right;
    std::cout << "Enter the range [left, right] for the query:" << std::endl;
    std::cin >> left >> right;
    int result = swt.rangeQuery(left, right);
    std::cout << "Sum of elements in the range [" << left << ", " << right << "]: " << result << std::endl;
    return 0;
}
