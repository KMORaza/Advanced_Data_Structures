#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
class DynamicPerfectHashing {
private:
    std::vector<std::list<int>> hashTable;
    std::vector<std::pair<int, int>> coefficients;
    int m; 
    int n; 
    int hashFunction(int a, int b, int x) {
        return (a * x + b) % m;
    }
    void resize() {
        m *= 2;
        coefficients[0].first = rand() % (m - 1) + 1;
        coefficients[0].second = rand() % m;
        std::vector<std::list<int>> newHashTable(m);
        for (const auto& chain : hashTable) {
            for (int element : chain) {
                int h = hashFunction(coefficients[0].first, coefficients[0].second, element);
                newHashTable[h].push_back(element);
            }
        }
        hashTable = std::move(newHashTable);
    }
public:
DynamicPerfectHashing() : m(2), n(0) {
    coefficients.emplace_back(rand() % (m - 1) + 1, rand() % m);
    hashTable.resize(m);
}
    void insert(int key) {
        if (n > 4 * m) {
            resize();
        }
        int h1 = hashFunction(coefficients[0].first, coefficients[0].second, key);
        if (std::find(hashTable[h1].begin(), hashTable[h1].end(), key) != hashTable[h1].end()) {
            return;
        }
        while (!hashTable[h1].empty()) {
            coefficients.emplace_back(rand() % (m - 1) + 1, rand() % m);
            resize();
            h1 = hashFunction(coefficients[0].first, coefficients[0].second, key);
        }
        hashTable[h1].push_back(key);
        n++;
    }
    bool search(int key) {
        int h1 = hashFunction(coefficients[0].first, coefficients[0].second, key);
        return std::find(hashTable[h1].begin(), hashTable[h1].end(), key) != hashTable[h1].end();
    }
};
int main() {
    DynamicPerfectHashing dph;
    dph.insert(5);
    dph.insert(15);
    dph.insert(25);
    std::cout << "Search 5: " << (dph.search(5) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 10: " << (dph.search(10) ? "Found" : "Not found") << std::endl;
    return 0;
}
