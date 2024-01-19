// Implementation of Red-Black Tree
#include <iostream>
#include <queue>
enum Color { RED, BLACK };
template <typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
    Node(Key k, Value v, Color c, Node* p, Node* l, Node* r)
        : key(k), value(v), color(c), parent(p), left(l), right(r) {}
};
template <typename Key, typename Value>
class RedBlackTree {
public:
    RedBlackTree() : root(nullptr) {}
    void insert(const Key& key, const Value& value) {
        Node<Key, Value>* newNode = new Node<Key, Value>(key, value, RED, nullptr, nullptr, nullptr);
        root = insertRecursive(root, newNode);
        fixInsertion(newNode);
    }
    void remove(const Key& key) {
        Node<Key, Value>* nodeToRemove = search(key);
        if (nodeToRemove != nullptr) {
            removeNode(nodeToRemove);
        }
    }
    Node<Key, Value>* search(const Key& key) const {
        return searchRecursive(root, key);
    }
    void print() const {
        levelOrderTraversal(root);
        std::cout << std::endl;
    }
private:
    Node<Key, Value>* root;
    Node<Key, Value>* insertRecursive(Node<Key, Value>* root, Node<Key, Value>* newNode) {
        if (root == nullptr) {
            return newNode;
        }
        if (newNode->key < root->key) {
            root->left = insertRecursive(root->left, newNode);
            root->left->parent = root;
        } else if (newNode->key > root->key) {
            root->right = insertRecursive(root->right, newNode);
            root->right->parent = root;
        }
        return root;
    }
    void fixInsertion(Node<Key, Value>* newNode) {
        while (newNode != root && newNode->parent->color == RED) {
            if (newNode->parent == newNode->parent->parent->left) {
                Node<Key, Value>* y = newNode->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    newNode->parent->color = BLACK;
                    y->color = BLACK;
                    newNode->parent->parent->color = RED;
                    newNode = newNode->parent->parent;
                } else {
                    if (newNode == newNode->parent->right) {
                        newNode = newNode->parent;
                        leftRotate(newNode);
                    }
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    rightRotate(newNode->parent->parent);
                }
            } else {
                Node<Key, Value>* y = newNode->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    newNode->parent->color = BLACK;
                    y->color = BLACK;
                    newNode->parent->parent->color = RED;
                    newNode = newNode->parent->parent;
                } else {
                    if (newNode == newNode->parent->left) {
                        newNode = newNode->parent;
                        rightRotate(newNode);
                    }
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    leftRotate(newNode->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    Node<Key, Value>* searchRecursive(Node<Key, Value>* root, const Key& key) const {
        if (root == nullptr || root->key == key) {
            return root;
        }
        if (key < root->key) {
            return searchRecursive(root->left, key);
        } else {
            return searchRecursive(root->right, key);
        }
    }
    Node<Key, Value>* inOrderSuccessor(Node<Key, Value>* node) const {
        Node<Key, Value>* current = node->right;
        while (current != nullptr && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    void removeNode(Node<Key, Value>* nodeToRemove) {
        Node<Key, Value>* x;
        Node<Key, Value>* y = nodeToRemove;
        Color yOriginalColor = y->color;
        if (nodeToRemove->left == nullptr) {
            x = nodeToRemove->right;
            transplant(nodeToRemove, nodeToRemove->right);
        } else if (nodeToRemove->right == nullptr) {
            x = nodeToRemove->left;
            transplant(nodeToRemove, nodeToRemove->left);
        } else {
            y = inOrderSuccessor(nodeToRemove);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == nodeToRemove) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = nodeToRemove->right;
                y->right->parent = y;
            }
            transplant(nodeToRemove, y);
            y->left = nodeToRemove->left;
            y->left->parent = y;
            y->color = nodeToRemove->color;
        }
        delete nodeToRemove;
        if (yOriginalColor == BLACK) {
            fixDeletion(x);
        }
    }
    void fixDeletion(Node<Key, Value>* x) {
        while (x != root && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) {
                Node<Key, Value>* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root; 
                }
            } else {
                Node<Key, Value>* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root; 
                }
            }
        }
        if (x != nullptr) {
            x->color = BLACK;
        }
    }
    void leftRotate(Node<Key, Value>* x) {
        Node<Key, Value>* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotate(Node<Key, Value>* y) {
        Node<Key, Value>* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }
    void transplant(Node<Key, Value>* u, Node<Key, Value>* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }
    void levelOrderTraversal(Node<Key, Value>* root) const {
        if (root == nullptr) {
            return;
        }
        std::queue<Node<Key, Value>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<Key, Value>* current = q.front();
            q.pop();
            std::cout << current->key << "(" << (current->color == RED ? "R" : "B") << ") ";
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }
};
int main() {
    RedBlackTree<int, std::string> rbTree;
    rbTree.insert(10, "A");
    rbTree.insert(20, "B");
    rbTree.insert(15, "C");
    rbTree.insert(25, "D");
    rbTree.insert(30, "E");
    std::cout << "Red-Black Tree: ";
    rbTree.print();
    int keyToSearch = 15;
    Node<int, std::string>* searchedNode = rbTree.search(keyToSearch);
    if (searchedNode != nullptr) {
        std::cout << "Node with key " << keyToSearch << " found, value: " << searchedNode->value << std::endl;
    } else {
        std::cout << "Node with key " << keyToSearch << " not found." << std::endl;
    }
    int keyToRemove = 20;
    std::cout << "Removing node with key " << keyToRemove << std::endl;
    rbTree.remove(keyToRemove);
    rbTree.print();
    return 0;
}
