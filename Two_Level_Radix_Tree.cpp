#include <iostream>
#include <unordered_map>
class RadixTreeNode {
public:
    std::unordered_map<char, RadixTreeNode*> children;
    bool isLeaf;

    RadixTreeNode() : isLeaf(false) {}
};
class TwoLevelRadixTree {
private:
    std::unordered_map<char, RadixTreeNode*> topLevelNodes;
public:
    void insert(const std::string& key) {
        char firstChar = key[0];
        if (topLevelNodes.find(firstChar) == topLevelNodes.end()) {
            topLevelNodes[firstChar] = new RadixTreeNode();
        }
        RadixTreeNode* current = topLevelNodes[firstChar];
        for (int i = 1; i < key.size(); ++i) {
            char currentChar = key[i];
            if (current->children.find(currentChar) == current->children.end()) {
                current->children[currentChar] = new RadixTreeNode();
            }
            current = current->children[currentChar];
        }
        current->isLeaf = true;
    }
    bool search(const std::string& key) const {
        char firstChar = key[0];
        if (topLevelNodes.find(firstChar) == topLevelNodes.end()) {
            return false;
        }
        const RadixTreeNode* current = topLevelNodes.at(firstChar);
        for (int i = 1; i < key.size(); ++i) {
            char currentChar = key[i];
            if (current->children.find(currentChar) == current->children.end()) {
                return false;
            }
            current = current->children.at(currentChar);
        }
        return current->isLeaf;
    }
};
int main() {
    TwoLevelRadixTree radixTree;
    int n;
    std::cout << "Enter the number of keys: ";
    std::cin >> n;
    std::cout << "Enter the keys, one per line:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::string key;
        std::cin >> key;
        radixTree.insert(key);
    }
    std::string searchKey;
    std::cout << "Enter a key to search: ";
    std::cin >> searchKey;
    std::cout << "Search '" << searchKey << "': " << (radixTree.search(searchKey) ? "Found" : "Not found") << std::endl;
    return 0;
}
