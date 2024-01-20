#include <iostream>
#include <vector>
#include <algorithm>
class FusionTreeNode {
public:
    int value;
    std::vector<FusionTreeNode*> children;
    FusionTreeNode(int val) : value(val) {}
};
class FusionTree {
private:
    FusionTreeNode* root;
    int elementsPerNode;
    FusionTreeNode* insertNode(FusionTreeNode* node, int value) {
        if (!node) {
            return new FusionTreeNode(value);
        }
        if (value < node->value) {
            node->children.push_back(insertNode(nullptr, value));
            std::sort(node->children.begin(), node->children.end(),
                      [](const FusionTreeNode* a, const FusionTreeNode* b) {
                          return a->value < b->value;
                      });
        } else {
            for (FusionTreeNode* child : node->children) {
                if (value < child->value) {
                    insertNode(child, value);
                    break;
                }
            }
        }
        return node;
    }
    bool searchNode(FusionTreeNode* node, int value) const {
        if (!node) {
            return false;
        }
        if (value == node->value) {
            return true;
        }
        for (FusionTreeNode* child : node->children) {
            if (value < child->value) {
                return searchNode(child, value);
            }
        }
        return false;
    }
    FusionTreeNode* deleteNode(FusionTreeNode* node, int value) {
        if (!node) {
            return nullptr;
        }
        if (value == node->value) {
            delete node;
            return nullptr;
        }
        auto it = std::find_if(node->children.begin(), node->children.end(),
                               [value](const FusionTreeNode* child) {
                                   return value < child->value;
                               });
        if (it != node->children.end()) {
            *it = deleteNode(*it, value);
        }
        return node;
    }
    void inorderTraversal(FusionTreeNode* node) const {
        if (node) {
            for (FusionTreeNode* child : node->children) {
                inorderTraversal(child);
                std::cout << node->value << " ";
            }
        }
    }
    void preorderTraversal(FusionTreeNode* node) const {
        if (node) {
            std::cout << node->value << " ";
            for (FusionTreeNode* child : node->children) {
                preorderTraversal(child);
            }
        }
    }
    void postorderTraversal(FusionTreeNode* node) const {
        if (node) {
            for (FusionTreeNode* child : node->children) {
                postorderTraversal(child);
            }
            std::cout << node->value << " ";
        }
    }
public:
    FusionTree(int elementsPerNode) : root(nullptr), elementsPerNode(elementsPerNode) {}
    void insert(int value) {
        root = insertNode(root, value);
    }
    bool search(int value) const {
        return searchNode(root, value);
    }
    void remove(int value) {
        root = deleteNode(root, value);
    }
    void printInorder() const {
        inorderTraversal(root);
        std::cout << std::endl;
    }
    void printPreorder() const {
        preorderTraversal(root);
        std::cout << std::endl;
    }
    void printPostorder() const {
        postorderTraversal(root);
        std::cout << std::endl;
    }
};
int main() {
    FusionTree fusionTree(3); 
    fusionTree.insert(5);
    fusionTree.insert(8);
    fusionTree.insert(3);
    fusionTree.insert(10);
    fusionTree.insert(7);
    std::cout << "Inorder Traversal:" << std::endl;
    fusionTree.printInorder();
    std::cout << "Preorder Traversal:" << std::endl;
    fusionTree.printPreorder();
    std::cout << "Postorder Traversal:" << std::endl;
    fusionTree.printPostorder();
    return 0;
}
