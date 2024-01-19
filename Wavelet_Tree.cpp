// Comprehensive implementation of Wavelet Tree
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
class WaveletTree {
public:
    WaveletTree(const std::vector<int>& input) : original(input), alphabet(*std::max_element(input.begin(), input.end()) + 1), levels(0) {
        construct(0, input.size() - 1, 0, alphabet);
    }
    int encode(int symbol, int position) const {
        int result = 0;
        for (int level = levels - 1; level >= 0; --level) {
            bool bit = (symbol & (1 << level)) != 0;
            if (bit) {
                result |= (1 << level);
                position = sum[level][position] + (original[position] & (1 << level));
            } else {
                position -= original[position] & (1 << level);
            }
        }
        return result;
    }
    int decode(int encodedSymbol, int position) const {
        int result = 0;
        for (int level = levels - 1; level >= 0; --level) {
            bool bit = (encodedSymbol & (1 << level)) != 0;
            if (bit) {
                position = sum[level][position] + (original[position] & (1 << level));
                result |= (1 << level);
            } else {
                position -= original[position] & (1 << level);
            }
        }
        return result;
    }
    int rank(int symbol, int position) const {
        int result = 0;
        for (int level = levels - 1; level >= 0; --level) {
            bool bit = (symbol & (1 << level)) != 0;
            if (bit) {
                result = sum[level][position] + count[level][symbol] - count[level][position];
                position = sum[level][position] + (original[position] & (1 << level));
            } else {
                position -= original[position] & (1 << level);
            }
        }
        return result;
    }
    int select(int symbol, int k) const {
        if (k <= 0 || k > count[levels - 1][symbol]) {
            return -1; 
        }
        int position = k;
        for (int level = 0; level < levels; ++level) {
            bool bit = (symbol & (1 << level)) != 0;
            if (bit) {
                position = selectSum(level, position, original.size() - 1);
                position -= (original[position] & (1 << level));
            } else {
                position = selectZero(level, position, original.size() - 1);
            }
        }
        return position;
    }
private:
    std::vector<int> original;
    int alphabet;
    int levels;
    std::vector<std::vector<int>> sum;
    std::vector<std::vector<int>> count;
    void construct(int left, int right, int level, int alpha) {
        if (level >= levels || left >= right) {
            return;
        }
        int mid = (left + right) / 2;
        sum[level].resize(right - left + 2, 0);
        count[level].resize(alpha + 1, 0);
        for (int i = left; i <= right; ++i) {
            sum[level][i - left + 1] = sum[level][i - left] + (original[i] & (1 << level));
            count[level][original[i]]++;
        }
        for (int i = 1; i <= alpha; ++i) {
            count[level][i] += count[level][i - 1];
        }
        int pivot = std::stable_partition(original.begin() + left, original.begin() + right + 1, [level](int x) {
            return (x & (1 << level)) != 0;
        }) - original.begin();
        construct(left, pivot - 1, level + 1, alpha);
        construct(pivot, right, level + 1, alpha);
    }
    int selectSum(int level, int k, int right) const {
        int left = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (sum[level][mid] < k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }
    int selectZero(int level, int k, int right) const {
        int left = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (mid - sum[level][mid] < k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }
};
int main() {
    std::vector<int> input = {3, 5, 2, 1, 4, 3, 2, 1};
    WaveletTree waveletTree(input);
    int symbolToEncode = 5;
    int positionToEncode = 4;
    int encodedSymbol = waveletTree.encode(symbolToEncode, positionToEncode);
    std::cout << "Encoded symbol: " << std::bitset<8>(encodedSymbol) << std::endl;
    int decodedSymbol = waveletTree.decode(encodedSymbol, positionToEncode);
    std::cout << "Decoded symbol: " << decodedSymbol << std::endl;
    int symbolForRank = 2;
    int positionForRank = 5;
    int rankResult = waveletTree.rank(symbolForRank, positionForRank);
    std::cout << "Rank of symbol " << symbolForRank << " up to position " << positionForRank << ": " << rankResult << std::endl;
    int kthOccurrence = 2;
    int selectResult = waveletTree.select(symbolForRank, kthOccurrence);
    std::cout << "Position of " << kthOccurrence << "-th occurrence of symbol " << symbolForRank << ": " << selectResult << std::endl;
    return 0;
}
