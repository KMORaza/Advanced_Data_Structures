#include <iostream>
#include <vector>
#include <cmath>
class EliasFano {
private:
    std::vector<uint64_t> upperBits;
    std::vector<uint64_t> lowerBits;
    uint64_t universeSize;
public:
    EliasFano(const std::vector<uint64_t>& input) {
        universeSize = input.back() + 1;
        uint64_t highBits = 0;
        uint64_t lowBits = 0;
        for (size_t i = 0; i < input.size(); ++i) {
            uint64_t current = input[i];
            highBits += current / (universeSize / (input.size() - i));
            lowBits <<= static_cast<uint64_t>(log2(universeSize / (input.size() - i)));
            lowBits += current % (universeSize / (input.size() - i));
        }
        upperBits.push_back(highBits);
        lowerBits.push_back(lowBits);
    }
    std::vector<uint64_t> decode() const {
        std::vector<uint64_t> result;
        uint64_t position = 0;
        for (size_t i = 0; i < upperBits.size(); ++i) {
            uint64_t highBits = upperBits[i];
            uint64_t lowBits = lowerBits[i];
            for (uint64_t j = 0; j < (sizeof(uint64_t) * 8) - static_cast<uint64_t>(log2(universeSize)); ++j) {
                uint64_t current = (highBits << static_cast<uint64_t>(log2(universeSize))) + lowBits;
                result.push_back(current);
                lowBits >>= static_cast<uint64_t>(log2(universeSize));
                highBits = current / universeSize;
            }
        }
        return result;
    }
};
int main() {
    std::vector<uint64_t> input;
    uint64_t value;
    std::cout << "Enter a monotone sequence of integers:" << std::endl;
    while (std::cin >> value) {
        input.push_back(value);
    }
    EliasFano ef(input);
    std::cout << "Original sequence: ";
    for (uint64_t val : ef.decode()) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}
