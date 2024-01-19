#include <iostream>
#include <bitset>
#include <functional>
#include <vector>
class BloomFilter {
private:
    std::vector<bool> bitArray;
    std::vector<std::function<size_t(const std::string&)>> hashFunctions;
    size_t numHashFunctions;
public:
    BloomFilter(size_t size, size_t numHashFunctions)
        : bitArray(size, false), numHashFunctions(numHashFunctions) {
        initializeHashFunctions();
    }
    void insert(const std::string& element) {
        for (const auto& hashFunction : hashFunctions) {
            size_t index = hashFunction(element) % bitArray.size();
            bitArray[index] = true;
        }
    }
    bool contains(const std::string& element) const {
        for (const auto& hashFunction : hashFunctions) {
            size_t index = hashFunction(element) % bitArray.size();
            if (!bitArray[index]) {
                return false; 
            }
        }
        return true; 
    }
private:
    void initializeHashFunctions() {
        hashFunctions.push_back(std::hash<std::string>());
        hashFunctions.push_back(hashFunction1);
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
    BloomFilter bloomFilter(100, 3);
    bloomFilter.insert("apple");
    bloomFilter.insert("orange");
    bloomFilter.insert("banana");
    std::cout << "Contains 'apple': " << bloomFilter.contains("apple") << std::endl;    
    std::cout << "Contains 'grape': " << bloomFilter.contains("grape") << std::endl;  
    return 0;
}
