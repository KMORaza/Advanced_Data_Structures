#include <iostream>
#include <cmath>  
#include <vector>
#include <algorithm>
#include <random>
#include <functional>
class HyperLogLog {
private:
    std::vector<int> registers;
    std::vector<std::function<uint64_t(const std::string&)>> hashFunctions;
    size_t numRegisters;
public:
    HyperLogLog(size_t precision)
        : numRegisters(1 << precision), registers(numRegisters, 0) {
        initializeHashFunctions();
    }
    void add(const std::string& element) {
        uint64_t hashValue = hashFunctions[0](element);
        size_t index = hashValue & (numRegisters - 1);
        int runLength = countLeadingZeros(hashValue >> static_cast<int>(log2(numRegisters) + 1)) + 1;
        registers[index] = std::max(registers[index], runLength);
    }
    size_t estimateCardinality() const {
        double alpha;
        if (numRegisters == 16) {
            alpha = 0.673;
        } else if (numRegisters == 32) {
            alpha = 0.697;
        } else if (numRegisters == 64) {
            alpha = 0.709;
        } else {
            alpha = 0.7213 / (1 + 1.079 / numRegisters);
        }
        double harmonicMean = 0;
        for (int reg : registers) {
            harmonicMean += 1.0 / (1 << reg);
        }
        double estimate = alpha * numRegisters * numRegisters / harmonicMean;
        if (estimate <= 2.5 * numRegisters) {
            int zeroRegisters = std::count(registers.begin(), registers.end(), 0);
            if (zeroRegisters != 0) {
                estimate = numRegisters * std::log(static_cast<double>(numRegisters) / zeroRegisters);
            }
        }
        return static_cast<size_t>(estimate);
    }
private:
    void initializeHashFunctions() {
        hashFunctions.push_back(std::hash<std::string>());
    }
    static int countLeadingZeros(uint64_t value) {
        int count = 0;
        while ((value & 0x8000000000000000) == 0) {
            value <<= 1;
            ++count;
        }
        return count;
    }
};
int main() {
    HyperLogLog hyperLogLog(10);
    hyperLogLog.add("apple");
    hyperLogLog.add("orange");
    hyperLogLog.add("banana");
    std::cout << "Estimated cardinality: " << hyperLogLog.estimateCardinality() << std::endl;
    return 0;
}
