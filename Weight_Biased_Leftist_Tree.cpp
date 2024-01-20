#include <iostream>
#include <algorithm>
class WeightBiasedLeftistTree {
private:
    struct Node {
        int key;
        int weight;
        Node* left;
        Node* right;
        Node(int k) : key(k), weight(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* merge(Node* h1, Node* h2) {
        if (h1 == nullptr) return h2;
        if (h2 == nullptr) return h1;
        if (h1->key > h2->key) std::swap(h1, h2);
        h1->right = merge(h1->right, h2);
        if (h1->left == nullptr || (h1->right != nullptr && h1->left->weight < h1->right->weight)) {
            std::swap(h1->left, h1->right);
        }
        h1->weight = (h1->right == nullptr) ? 1 : (h1->right->weight + 1);
        return h1;
    }
    Node* insertRecursive(Node* root, int key) {
        return merge(root, new Node(key));
    }
    Node* deleteMinRecursive(Node* root) {
        Node* left = root->left;
        Node* right = root->right;
        delete root;
        return merge(left, right);
    }
    void inOrderTraversal(Node* root) {
        if (root) {
            inOrderTraversal(root->left);
            std::cout << root->key << " ";
            inOrderTraversal(root->right);
        }
    }
public:
    WeightBiasedLeftistTree() : root(nullptr) {}
    void insert(int key) {
        root = insertRecursive(root, key);
    }
    void deleteMin() {
        if (root != nullptr) {
            root = deleteMinRecursive(root);
        }
    }
    void inOrder() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
    void mergeWith(WeightBiasedLeftistTree& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }
};
int main() {
    WeightBiasedLeftistTree wblt1, wblt2;
    wblt1.insert(10);
    wblt1.insert(5);
    wblt1.insert(15);
    wblt2.insert(8);
    wblt2.insert(12);
    wblt2.insert(20);
    std::cout << "Weight-Biased Leftist Tree 1 (in-order): ";
    wblt1.inOrder();
    std::cout << "Weight-Biased Leftist Tree 2 (in-order): ";
    wblt2.inOrder();
    wblt1.mergeWith(wblt2);
    std::cout << "After merging (in-order): ";
    wblt1.inOrder();
    wblt1.deleteMin();
    std::cout << "After deleting the minimum element (in-order): ";
    wblt1.inOrder();
    return 0;
}
