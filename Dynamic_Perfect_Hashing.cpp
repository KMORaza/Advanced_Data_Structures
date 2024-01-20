#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
class DynamicPerfectHashing {
private:
    int universeSize;
    std::vector<std::vector<int>> hashTable;
    std::vector<std::vector<int>> keys;
    void buildSecondLevelHashTable(int bucket) {
        int m = static_cast<int>(keys[bucket].size());
        int secondLevelSize = m * m;
        while (true) {
            hashTable[bucket].assign(secondLevelSize, -1);
            bool success = true;
            for (int i = 0; i < m; ++i) {
                int h = hash(keys[bucket][i], secondLevelSize);
                if (hashTable[bucket][h] == -1) {
                    hashTable[bucket][h] = keys[bucket][i];
                } else {
                    success = false;
                    break;
                }
            }
            if (success) {
                break;
            }
            secondLevelSize *= 2;
        }
    }
    int hash(int key, int tableSize) const {
        return key % tableSize;
    }
public:
    DynamicPerfectHashing(int universeSize) : universeSize(universeSize) {
        int initialSize = static_cast<int>(sqrt(universeSize));
        hashTable.resize(initialSize);
        keys.resize(initialSize);
    }
    void insert(int key) {
        int bucket = key % hashTable.size();
        if (std::find(keys[bucket].begin(), keys[bucket].end(), key) == keys[bucket].end()) {
            keys[bucket].push_back(key);
            if (keys[bucket].size() * keys[bucket].size() > hashTable.size()) {
                buildSecondLevelHashTable(bucket);
            }
        }
    }
void remove(int key) {
    int bucket = key % hashTable.size();
    auto it = std::find(keys[bucket].begin(), keys[bucket].end(), key);
    if (it != keys[bucket].end()) {
        keys[bucket].erase(it);
        buildSecondLevelHashTable(bucket);
    }
}
    bool contains(int key) const {
        int bucket = key % hashTable.size();
        int h = hash(key, static_cast<int>(keys[bucket].size() * keys[bucket].size()));
        return hashTable[bucket][h] == key;
    }
};
int main() {
    DynamicPerfectHashing dynamicPerfectHashing(100);
    dynamicPerfectHashing.insert(42);
    dynamicPerfectHashing.insert(13);
    dynamicPerfectHashing.insert(88);
    std::cout << "Contains 13? " << (dynamicPerfectHashing.contains(13) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 99? " << (dynamicPerfectHashing.contains(99) ? "Yes" : "No") << std::endl;
    dynamicPerfectHashing.remove(13);
    std::cout << "After removing 13, Contains 13? " << (dynamicPerfectHashing.contains(13) ? "Yes" : "No") << std::endl;
    return 0;
}
