#include <iostream>
#include <vector>
class BinaryHeap {
private:
    std::vector<int> heap;
public:
    BinaryHeap() {}
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
    int extractMin() {
        if (isEmpty()) {
            std::cerr << "Heap is empty. Cannot extract minimum element.\n";
            return -1; 
        }
        int minValue = heap[0];
        int lastIndex = heap.size() - 1;
        std::swap(heap[0], heap[lastIndex]);
        heap.pop_back();
        heapifyDown(0);
        return minValue;
    }
    bool isEmpty() const {
        return heap.empty();
    }
    void printHeap() const {
        for (int value : heap) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
private:
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] < heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;
        if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }
        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
};
int main() {
    BinaryHeap minHeap;
    minHeap.insert(3);
    minHeap.insert(2);
    minHeap.insert(1);
    minHeap.insert(7);
    minHeap.insert(8);
    minHeap.insert(4);
    minHeap.insert(6);
    minHeap.insert(5);
    std::cout << "Original Heap: ";
    minHeap.printHeap();
    std::cout << "Extracted Min: " << minHeap.extractMin() << std::endl;
    std::cout << "Heap after extraction: ";
    minHeap.printHeap();
    return 0;
}
