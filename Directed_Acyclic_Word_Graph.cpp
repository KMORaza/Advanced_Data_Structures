#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
class DAWG {
private:
    struct Node {
        std::unordered_map<char, Node*> children;
        bool isEndOfWord;
        Node() : isEndOfWord(false) {}
    };
    Node* root;
public:
    DAWG() : root(new Node()) {}
    ~DAWG() {
        destroy(root);
    }
    void insert(const std::string& word) {
        insertHelper(root, word, 0);
    }
    bool search(const std::string& word) const {
        return searchHelper(root, word, 0);
    }
private:
    void insertHelper(Node* current, const std::string& word, size_t index) {
        if (index == word.length()) {
            current->isEndOfWord = true;
            return;
        }
        char ch = word[index];
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new Node();
        }
        insertHelper(current->children[ch], word, index + 1);
    }
    bool searchHelper(const Node* current, const std::string& word, size_t index) const {
        if (index == word.length()) {
            return current->isEndOfWord;
        }
        char ch = word[index];
        if (current->children.find(ch) == current->children.end()) {
            return false;
        }
        return searchHelper(current->children.at(ch), word, index + 1);
    }
    void destroy(Node* current) {
        for (auto& pair : current->children) {
            destroy(pair.second);
        }
        delete current;
    }
};
int main() {
    DAWG dawg;
    std::cout << "Enter words to insert:" << std::endl;
    std::string word;
    while (std::getline(std::cin, word) && !word.empty()) {
        dawg.insert(word);
    }
    std::cout << "Enter a word to search:" << std::endl;
    std::cin >> word;
    if (dawg.search(word)) {
        std::cout << "The word is present!" << std::endl;
    } else {
        std::cout << "The word is not present!" << std::endl;
    }
    return 0;
}
