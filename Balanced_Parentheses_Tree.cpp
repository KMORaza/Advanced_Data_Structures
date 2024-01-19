#include <iostream>
#include <string>
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char c) : data(c), left(nullptr), right(nullptr) {}
};
class ParenthesesTree {
private:
    Node* root;
public:
    ParenthesesTree() : root(nullptr) {}
    ~ParenthesesTree() {
        destroyTree(root);
    }
    void buildTree(const std::string& parenthesesString) {
        root = buildTreeRecursive(parenthesesString, 0, parenthesesString.size() - 1);
    }
    void printInOrder() const {
        std::cout << "In-order traversal: ";
        printInOrderRecursive(root);
        std::cout << std::endl;
    }
    void printPreOrder() const {
        std::cout << "Pre-order traversal: ";
        printPreOrderRecursive(root);
        std::cout << std::endl;
    }
    void printPostOrder() const {
        std::cout << "Post-order traversal: ";
        printPostOrderRecursive(root);
        std::cout << std::endl;
    }
private:
    Node* buildTreeRecursive(const std::string& str, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;
        Node* newNode = new Node(str[mid]);
        newNode->left = buildTreeRecursive(str, start, mid - 1);
        newNode->right = buildTreeRecursive(str, mid + 1, end);
        return newNode;
    }
    void printInOrderRecursive(const Node* node) const {
        if (node) {
            printInOrderRecursive(node->left);
            std::cout << node->data << " ";
            printInOrderRecursive(node->right);
        }
    }
    void printPreOrderRecursive(const Node* node) const {
        if (node) {
            std::cout << node->data << " ";
            printPreOrderRecursive(node->left);
            printPreOrderRecursive(node->right);
        }
    }
    void printPostOrderRecursive(const Node* node) const {
        if (node) {
            printPostOrderRecursive(node->left);
            printPostOrderRecursive(node->right);
            std::cout << node->data << " ";
        }
    }
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};
int main() {
    ParenthesesTree parenthesesTree;
    std::string parenthesesString = "(((())))";
    parenthesesTree.buildTree(parenthesesString);
    parenthesesTree.printInOrder();
    parenthesesTree.printPreOrder();
    parenthesesTree.printPostOrder();
    return 0;
}
