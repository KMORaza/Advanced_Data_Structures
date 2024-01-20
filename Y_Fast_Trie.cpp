#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <cmath>
class YFastNode {
public:
    int key;
    YFastNode* left;
    YFastNode* right;
    YFastNode(int k) : key(k), left(nullptr), right(nullptr) {}
};
class YFastTrie {
private:
    int universeSize;
    int blockSize;
    std::set<int> keys;
    std::unordered_map<int, YFastNode*> level0;
    std::vector<std::set<int>> levels;
    YFastNode* findPredecessor(int x) const {
        auto it = keys.lower_bound(x);
        if (it == keys.begin()) {
            return nullptr;
        }
        --it;
        return level0.find(*it) != level0.end() ? level0.at(*it) : nullptr;
    }
    void deleteTree(YFastNode* node) {
        if (!node) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
public:
    YFastTrie(int universeSize) : universeSize(universeSize), blockSize(static_cast<int>(sqrt(universeSize))) {
        levels.resize(static_cast<size_t>(log2(universeSize)) + 1);
    }
    ~YFastTrie() {
        deleteTree(level0.begin()->second);
    }
    void insert(int x) {
        if (keys.find(x) != keys.end()) {
            return; 
        }
        keys.insert(x);
        YFastNode* pred = findPredecessor(x);
        YFastNode* newNode = new YFastNode(x);
        if (!pred) {
            level0[x] = newNode;
        } else {
            newNode->left = pred;
            newNode->right = pred->right;
            if (pred->right) {
                pred->right->left = newNode;
            }
            pred->right = newNode;
        }
        int level = 1;
        while (level < levels.size() && level <= log2(universeSize) && keys.size() % static_cast<int>(pow(2, level)) == 0) {
            auto it = keys.lower_bound(x);
            for (int i = 0; i < (1 << level); ++i) {
                if (it == keys.end()) {
                    break;
                }
                levels[level].insert(*it);
                ++it;
            }
            level++;
        }
    }
    bool search(int x) const {
        return keys.find(x) != keys.end();
    }
    void remove(int x) {
        auto it = keys.find(x);
        if (it == keys.end()) {
            return; 
        }
        keys.erase(it);
        auto nodeIt = level0.find(x);
        if (nodeIt != level0.end()) {
            YFastNode* node = nodeIt->second;
            if (node->left) {
                node->left->right = node->right;
            }
            if (node->right) {
                node->right->left = node->left;
            }
            delete node;
            level0.erase(nodeIt);
        }
        int level = 1;
        while (level < levels.size() && level <= log2(universeSize) && keys.size() % static_cast<int>(pow(2, level)) == 0) {
            auto it = keys.lower_bound(x);
            for (int i = 0; i < (1 << level); ++i) {
                if (it == keys.end()) {
                    break;
                }
                levels[level].erase(*it);
                ++it;
            }
            level++;
        }
    }
    void inorderTraversal(YFastNode* node) const {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }
    void preorderTraversal(YFastNode* node) const {
        if (node) {
            std::cout << node->key << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }
    void postorderTraversal(YFastNode* node) const {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->key << " ";
        }
    }
    void printLevels() const {
        for (const auto& level : levels) {
            for (int key : level) {
                std::cout << key << " ";
            }
            std::cout << std::endl;
        }
    }
    void printInorder() const {
        inorderTraversal(level0.begin()->second);
        std::cout << std::endl;
    }
    void printPreorder() const {
        preorderTraversal(level0.begin()->second);
        std::cout << std::endl;
    }
    void printPostorder() const {
        postorderTraversal(level0.begin()->second);
        std::cout << std::endl;
    }
};
int main() {
    YFastTrie yFastTrie(16);
    yFastTrie.insert(2);
    yFastTrie.insert(8);
    yFastTrie.insert(5);
    yFastTrie.insert(11);
    yFastTrie.insert(3);
    std::cout << "Y-Fast Trie:" << std::endl;
    yFastTrie.printLevels();
    std::cout << "Inorder Traversal:" << std::endl;
    yFastTrie.printInorder();
    std::cout << "Preorder Traversal:" << std::endl;
    yFastTrie.printPreorder();
    std::cout << "Postorder Traversal:" << std::endl;
    yFastTrie.printPostorder();
    int searchKey = 5;
    std::cout << "Search for " << searchKey << ": " << (yFastTrie.search(searchKey) ? "Found" : "Not Found") << std::endl;
    int removeKey = 8;
    yFastTrie.remove(removeKey);
    std::cout << "After removing " << removeKey << ":" << std::endl;
    yFastTrie.printLevels();
    return 0;
}
