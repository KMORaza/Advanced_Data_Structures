#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
struct Node {
    std::vector<Node*> children;
    Node* suffixLink;
    int start;
    int* end;
    int suffixIndex;
};
struct ActivePoint {
    Node* activeNode;
    int activeEdge;
    int activeLength;
};
class SuffixTree {
public:
    SuffixTree(const std::string& str) : root(nullptr), lastNewNode(nullptr), activeNode(nullptr), activeEdge(-1), activeLength(0), remainder(0) {
        this->text = str + "$";
        this->leafEnd = new int;
        *(this->leafEnd) = -1;  
        this->buildSuffixTree();
    }
    ~SuffixTree() {
        deleteTree(root);
        delete leafEnd;
    }
    void printSuffixes() {
        std::cout << "Suffixes of " << text << " are:" << std::endl;
        printSuffixesUtil(root);
        std::cout << std::endl;
    }
    void clusterStrings(const std::vector<std::string>& strings) {
        for (const auto& str : strings) {
            std::cout << "Common substrings of " << str << " with " << text << " are:" << std::endl;
            clusterStringsUtil(root, str);
            std::cout << std::endl;
        }
    }
private:
    Node* root;
    Node* lastNewNode;
    Node* activeNode;
    int activeEdge;
    int activeLength;
    int remainder;
    int* leafEnd;
    std::string text;
    Node* createNewNode(int start, int* end) {
        Node* node = new Node;
        node->suffixLink = nullptr;
        node->start = start;
        node->end = end;
        node->suffixIndex = -1;
        return node;
    }
    int edgeLength(Node* node) {
        return *(node->end) - node->start + 1;
    }
    void addSuffixLink(Node* node) {
        if (lastNewNode != nullptr) {
            lastNewNode->suffixLink = node;
        }
        lastNewNode = node;
    }
    void extendSuffixTree(int pos) {
        remainder++;
        lastNewNode = nullptr;
        while (remainder > 0) {
            if (activeLength == 0) {
                activeEdge = pos;
            }
            if (activeNode->children[text[activeEdge]] == nullptr) {
                activeNode->children[text[activeEdge]] = createNewNode(pos, leafEnd);
                addSuffixLink(activeNode);
            } else {
                Node* nextNode = activeNode->children[text[activeEdge]];
                if (walkDown(nextNode)) {
                    continue;
                }
                if (text[nextNode->start + activeLength] == text[pos]) {
                    activeLength++;
                    addSuffixLink(activeNode);
                    break;
                }
                int* splitEnd = new int(nextNode->start + activeLength - 1);
                Node* splitNode = createNewNode(nextNode->start, splitEnd);
                activeNode->children[text[activeEdge]] = splitNode;
                splitNode->children[text[pos]] = createNewNode(pos, leafEnd);
                nextNode->start += activeLength;
                splitNode->children[text[nextNode->start]] = nextNode;
                addSuffixLink(splitNode);
            }
            remainder--;
            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainder + 1;
            } else if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }
    bool walkDown(Node* nextNode) {
        if (activeLength >= edgeLength(nextNode)) {
            activeEdge += edgeLength(nextNode);
            activeLength -= edgeLength(nextNode);
            activeNode = nextNode;
            return true;
        }
        return false;
    }
    void buildSuffixTree() {
        int n = text.length();
        root = createNewNode(-1, nullptr);
        root->suffixLink = root;
        activeNode = root;
        for (int i = 0; i < n; ++i) {
            extendSuffixTree(i);
        }
    }
    void printSuffixesUtil(Node* node) {
        if (node == nullptr) {
            return;
        }
        if (node->start != -1) {
            std::cout << text.substr(node->start, edgeLength(node)) << std::endl;
        }
        for (Node* child : node->children) {
            printSuffixesUtil(child);
        }
    }
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        for (Node* child : node->children) {
            deleteTree(child);
        }
        delete node;
    }
    void clusterStringsUtil(Node* node, const std::string& str) {
        if (node == nullptr) {
            return;
        }
        if (node->start != -1) {
            int commonLen = longestCommonPrefix(str, node->start, node->end);
            if (commonLen > 0) {
                std::cout << str.substr(0, commonLen) << std::endl;
            }
        }
        for (Node* child : node->children) {
            clusterStringsUtil(child, str);
        }
    }
    int longestCommonPrefix(const std::string& str, int start, int* end) {
        int len = std::min(*end - start + 1, static_cast<int>(str.length()));
        int commonLen = 0;
        for (int i = 0; i < len; ++i) {
            if (text[start + i] != str[i]) {
                break;
            }
            commonLen++;
        }
        return commonLen;
    }
};
int main() {
    std::vector<std::string> strings = {"hat", "mat", "rat", "cat"};
    SuffixTree suffixTree("hat");
    suffixTree.printSuffixes();
    suffixTree.clusterStrings(strings);
    return 0;
}
