#include <iostream>
#include <vector>
#include <functional>
#include <limits> 
class CountMinSketch {
private:
    std::vector<std::vector<int>> table;
    std::vector<std::function<size_t(const std::string&)>> hashFunctions;
    size_t numRows;
    size_t numCols;
public:
    CountMinSketch(size_t numRows, size_t numCols)
        : numRows(numRows), numCols(numCols), table(numRows, std::vector<int>(numCols, 0)) {
        initializeHashFunctions();
    }
    void update(const std::string& element, int count = 1) {
        for (size_t i = 0; i < numRows; ++i) {
            size_t index = hashFunctions[i](element) % numCols;
            table[i][index] += count;
        }
    }
    int estimate(const std::string& element) const {
        int minCount = std::numeric_limits<int>::max(); 
        for (size_t i = 0; i < numRows; ++i) {
            size_t index = hashFunctions[i](element) % numCols;
            minCount = std::min(minCount, table[i][index]);
        }
        return minCount;
    }
private:
    void initializeHashFunctions() {
        hashFunctions.push_back(std::hash<std::string>());
    }
    static size_t hashFunction1(const std::string& str) {
        size_t hash = 0;
        for (char c : str) {
            hash = hash * 31 + c;
        }
        return hash;
    }
};
int main() {
    CountMinSketch countMinSketch(3, 10);
    countMinSketch.update("apple", 3);
    countMinSketch.update("orange", 2);
    countMinSketch.update("banana", 5);
    std::cout << "Estimated count of 'apple': " << countMinSketch.estimate("apple") << std::endl;
    std::cout << "Estimated count of 'grape': " << countMinSketch.estimate("grape") << std::endl;
    return 0;
}
