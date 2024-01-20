#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
class LZWCompression {
private:
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> compressedData;
    int nextCode;
public:
    LZWCompression() : nextCode(256) {
        initializeDictionary();
    }
    void initializeDictionary() {
        for (int i = 0; i < 256; ++i) {
            std::string symbol(1, static_cast<char>(i));
            dictionary[symbol] = i;
        }
    }
    std::vector<int> compress(const std::string& input) {
        std::string current;
        for (char c : input) {
            std::string newStr = current + c;
            if (dictionary.find(newStr) != dictionary.end()) {
                current = newStr;
            } else {
                compressedData.push_back(dictionary[current]);
                dictionary[newStr] = nextCode++;
                current = c;
            }
        }
        if (!current.empty()) {
            compressedData.push_back(dictionary[current]);
        }
        return compressedData;
    }
};
int main() {
    std::string input;
    std::cout << "Enter the string to compress: ";
    std::cin >> input;
    LZWCompression lzw;
    std::vector<int> compressedData = lzw.compress(input);
    std::cout << "Compressed Data: ";
    for (int code : compressedData) {
        std::cout << code << " ";
    }
    std::cout << std::endl;
    return 0;
}
