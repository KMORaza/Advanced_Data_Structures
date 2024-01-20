#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>  
class TopKDataStructure {
private:
    int k;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
public:
    TopKDataStructure(int k) : k(k) {}
    void addElement(int element) {
        if (minHeap.size() < k) {
            minHeap.push(element);
        } else if (element > minHeap.top()) {
            minHeap.pop();
            minHeap.push(element);
        }
    }
    std::vector<int> getTopK() {
        std::vector<int> result;
        result.reserve(minHeap.size());
        while (!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        std::reverse(result.begin(), result.end());
        for (int element : result) {
            minHeap.push(element);
        }
        return result;
    }
};
int main() {
    int k;
    std::cout << "Enter the value of k for Top-k queries: ";
    std::cin >> k;
    TopKDataStructure topKDS(k);
    int numElements;
    std::cout << "Enter the number of elements to add: ";
    std::cin >> numElements;
    std::cout << "Enter the elements:" << std::endl;
    for (int i = 0; i < numElements; ++i) {
        int element;
        std::cin >> element;
        topKDS.addElement(element);
    }
    std::vector<int> topKElements = topKDS.getTopK();
    std::cout << "Top-" << k << " elements:" << std::endl;
    for (int element : topKElements) {
        std::cout << element << " ";
    }
    return 0;
}
