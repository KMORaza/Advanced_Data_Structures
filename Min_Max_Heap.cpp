#include <iostream>
#include <vector>
#include <cmath>
class MinMaxHeap {
private:
    std::vector<int> heap;
public:
    MinMaxHeap() {}
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }
    int findMin() const {
        if (isEmpty()) {
            std::cerr << "Heap is empty." << std::endl;
            return -1; 
        }
        return heap[0];
    }
    int findMax() const {
        if (isEmpty()) {
            std::cerr << "Heap is empty." << std::endl;
            return -1; 
        }
        if (heap.size() == 1 || heap.size() == 2) {
            return heap.back();
        }
        return std::max(heap[1], heap[2]);
    }
    int extractMin() {
        if (isEmpty()) {
            std::cerr << "Heap is empty." << std::endl;
            return -1; 
        }
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDownMin(0);
        return minVal;
    }
    int extractMax() {
        if (isEmpty()) {
            std::cerr << "Heap is empty." << std::endl;
            return -1; 
        }
        if (heap.size() == 1 || heap.size() == 2) {
            int maxVal = heap.back();
            heap.pop_back();
            return maxVal;
        }
        int maxChildIndex = (heap[1] > heap[2]) ? 1 : 2;
        int maxVal = heap[maxChildIndex];
        heap[maxChildIndex] = heap.back();
        heap.pop_back();
        heapifyDownMax(maxChildIndex);
        return maxVal;
    }
    bool isEmpty() const {
        return heap.empty();
    }
private:
    void heapifyUp(int index) {
        bool isMinLevel = isMinLevelNode(index);
        while (index > 0) {
            int parent = (index - 1) / 2;
            if ((isMinLevel && heap[index] < heap[parent]) ||
                (!isMinLevel && heap[index] > heap[parent])) {
                std::swap(heap[index], heap[parent]);
                index = parent;
                isMinLevel = !isMinLevel;
            } else {
                break;
            }
        }
    }
    void heapifyDownMin(int index) {
        int minChildIndex = findMinChildIndex(index);
        if (minChildIndex != -1 && heap[minChildIndex] < heap[index]) {
            std::swap(heap[index], heap[minChildIndex]);
            heapifyDownMax(minChildIndex);
        }
    }
    void heapifyDownMax(int index) {
        int maxChildIndex = findMaxChildIndex(index);
        if (maxChildIndex != -1 && heap[maxChildIndex] > heap[index]) {
            std::swap(heap[index], heap[maxChildIndex]);
            heapifyDownMin(maxChildIndex);
        }
    }
    int findMinChildIndex(int index) const {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild < heap.size()) {
            int minChildIndex = leftChild;
            if (rightChild < heap.size() && heap[rightChild] < heap[leftChild]) {
                minChildIndex = rightChild;
            }
            return minChildIndex;
        }
        return -1;
    }
    int findMaxChildIndex(int index) const {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild < heap.size()) {
            int maxChildIndex = leftChild;
            if (rightChild < heap.size() && heap[rightChild] > heap[leftChild]) {
                maxChildIndex = rightChild;
            }
            return maxChildIndex;
        }
        return -1;
    }
    bool isMinLevelNode(int index) const {
        int level = static_cast<int>(std::log2(index + 1));
        return level % 2 == 0;
    }
};
int main() {
    MinMaxHeap minMaxHeap;
    minMaxHeap.insert(5);
    minMaxHeap.insert(2);
    minMaxHeap.insert(8);
    minMaxHeap.insert(1);
    minMaxHeap.insert(7);
    std::cout << "Min: " << minMaxHeap.findMin() << std::endl; 
    std::cout << "Max: " << minMaxHeap.findMax() << std::endl;
    std::cout << "Extract Min: " << minMaxHeap.extractMin() << std::endl;
    std::cout << "Extract Max: " << minMaxHeap.extractMax() << std::endl;
    std::cout << "Min after extraction: " << minMaxHeap.findMin() << std::endl; 
    std::cout << "Max after extraction: " << minMaxHeap.findMax() << std::endl; 
    return 0;
}
