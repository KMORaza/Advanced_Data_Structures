// Implementation of succinct data structure for bitvector
#include <iostream>
#include <vector>
class SuccinctBitVector {
private:
    std::vector<uint64_t> data;
    std::vector<uint64_t> rankBlocks;
public:
    SuccinctBitVector(const std::vector<bool>& bits) {
        data.reserve(bits.size());
        rankBlocks.reserve((bits.size() / 64) + 1);
        uint64_t currentBlock = 0;
        uint64_t rankCount = 0;
        for (bool bit : bits) {
            if (bit) {
                currentBlock |= 1ULL << (rankCount % 64);
                rankCount++;
            }
            if ((rankCount % 64) == 0) {
                data.push_back(currentBlock);
                rankBlocks.push_back(rankCount);
                currentBlock = 0;
            }
        }
        if (rankCount % 64 != 0) {
            data.push_back(currentBlock);
            rankBlocks.push_back(rankCount);
        }
    }
    uint64_t rank(uint64_t i) const {
        uint64_t block = i / 64;
        uint64_t offset = i % 64;
        uint64_t rank = (block > 0) ? rankBlocks[block - 1] : 0;
        if (offset > 0) {
            uint64_t mask = (1ULL << offset) - 1;
            rank += __builtin_popcountll(data[block] & mask);
        }
        return rank;
    }
    uint64_t select(uint64_t i) const {
        uint64_t block = i / 64;
        uint64_t offset = i % 64;
        if (block >= rankBlocks.size()) {
            return 0; 
        }
        uint64_t rankBlock = rankBlocks[block];
        if (offset > 0) {
            uint64_t mask = (1ULL << offset) - 1;
            uint64_t setBits = __builtin_popcountll(data[block] & mask);
            rankBlock += setBits;
        }
        return rankBlock;
    }
};
int main() {
    std::vector<bool> bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0};
    SuccinctBitVector sdbv(bits);
    std::cout << "Rank(10): " << sdbv.rank(10) << std::endl;
    std::cout << "Select(5): " << sdbv.select(5) << std::endl;
    return 0;
}
