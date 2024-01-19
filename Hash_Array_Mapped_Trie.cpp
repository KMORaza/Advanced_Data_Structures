#include <iostream>
#include <unordered_map>
#include <bitset>
#include <vector>
const int MAX_BRANCHING_FACTOR = 32;
class HAMTNode {
private:
    std::unordered_map<char, HAMTNode*> children;
    bool isEndOfWord;
public:
    HAMTNode() : isEndOfWord(false) {}
    void insert(const std::string& key) {
        if (key.empty()) {
            isEndOfWord = true;
            return;
        }
        char firstChar = key[0];
        std::string rest = key.substr(1);
        if (children.find(firstChar) == children.end()) {
            children[firstChar] = new HAMTNode();
        }
        children[firstChar]->insert(rest);
    }
    bool search(const std::string& key) const {
        if (key.empty()) {
            return isEndOfWord;
        }
        char firstChar = key[0];
        std::string rest = key.substr(1);
        if (children.find(firstChar) != children.end()) {
            return children.at(firstChar)->search(rest);
        }
        return false;
    }
    void remove(const std::string& key) {
        if (key.empty()) {
            isEndOfWord = false;
            return;
        }
        char firstChar = key[0];
        std::string rest = key.substr(1);
        if (children.find(firstChar) != children.end()) {
            children[firstChar]->remove(rest);
            if (children[firstChar]->isEmpty()) {
                delete children[firstChar];
                children.erase(firstChar);
            }
        }
    }
    bool isEmpty() const {
        return children.empty() && !isEndOfWord;
    }
    ~HAMTNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};
class HashArrayMappedTrie {
private:
    HAMTNode* root;
public:
    HashArrayMappedTrie() : root(new HAMTNode()) {}
    void insert(const std::string& key) {
        root->insert(key);
    }
    bool search(const std::string& key) const {
        return root->search(key);
    }
    void remove(const std::string& key) {
        root->remove(key);
    }
    ~HashArrayMappedTrie() {
        delete root;
    }
};
int main() {
    HashArrayMappedTrie hamt;
    std::cout << "Enter words to insert:" << std::endl;
    std::string word;
    while (std::getline(std::cin, word) && !word.empty()) {
        hamt.insert(word);
    }
    std::cout << "Enter a word to search:" << std::endl;
    std::cin >> word;
    if (hamt.search(word)) {
        std::cout << "The word is present!" << std::endl;
    } else {
        std::cout << "The word is not present!" << std::endl;
    }
    std::cout << "Enter a word to remove:" << std::endl;
    std::cin >> word;
    hamt.remove(word);
    return 0;
}
