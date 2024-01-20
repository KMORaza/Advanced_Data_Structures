#include <iostream>
#include <vector>
#include <cmath>
class SuccinctDynamicDictionary {
private:
    std::vector<bool> bitVector;
    std::vector<size_t> rankIndex;
public:
    SuccinctDynamicDictionary() {}
    void insert(size_t element) {
        size_t newSize = std::max(element + 1, bitVector.size());
        bitVector.resize(newSize);
        bitVector[element] = true;
        rankIndex.clear();
    }
    void remove(size_t element) {
        if (element < bitVector.size()) {
            bitVector[element] = false;
            rankIndex.clear();
        }
    }
    bool contains(size_t element) {
        if (element >= bitVector.size()) {
            return false;
        }
        return bitVector[element];
    }
    size_t rank(size_t value) {
        if (rankIndex.empty()) {
            buildRankIndex();
        }
        if (value >= rankIndex.size()) {
            return bitVector.size();
        }
        return rankIndex[value];
    }
private:
    void buildRankIndex() {
        rankIndex.resize(bitVector.size() + 1, 0);
        for (size_t i = 1; i <= bitVector.size(); ++i) {
            rankIndex[i] = rankIndex[i - 1] + bitVector[i - 1];
        }
    }
};
int main() {
    SuccinctDynamicDictionary dictionary;
    dictionary.insert(5);
    dictionary.insert(8);
    dictionary.insert(3);
    std::cout << "Contains 5: " << std::boolalpha << dictionary.contains(5) << std::endl;
    std::cout << "Contains 2: " << std::boolalpha << dictionary.contains(2) << std::endl;
    dictionary.remove(8);
    std::cout << "Rank of 5: " << dictionary.rank(5) << std::endl;
    std::cout << "Rank of 10: " << dictionary.rank(10) << std::endl;
    return 0;
}
