#include <iostream>
#include <vector>
class LinkCutNode {
public:
    int key;
    LinkCutNode* parent;
    LinkCutNode* leftChild;
    LinkCutNode* rightChild;
    bool isRoot;
    bool reversed;
    LinkCutNode(int k) : key(k), parent(nullptr), leftChild(nullptr), rightChild(nullptr), isRoot(true), reversed(false) {}
};
class LinkCutTree {
private:
    std::vector<LinkCutNode*> nodes;
    void makeRoot(LinkCutNode* x) {
        access(x);
        splay(x);
        x->reversed = !x->reversed;
    }
    void link(LinkCutNode* x, LinkCutNode* y) {
        makeRoot(x);
        x->parent = y;
    }
    void cut(LinkCutNode* x) {
        access(x);
        splay(x);
        x->leftChild->parent = nullptr;
        x->leftChild = nullptr;
    }
    LinkCutNode* access(LinkCutNode* x) {
        LinkCutNode* last = nullptr;
        for (LinkCutNode* y = x; y; y = y->parent) {
            splay(y);
            y->rightChild = last;
            last = y;
        }
        splay(x);
        return last;
    }
    void splay(LinkCutNode* x) {
        while (!x->isRoot) {
            LinkCutNode* p = x->parent;
            LinkCutNode* g = p->parent;
            if (g) {
                pushDown(g);
            }
            pushDown(p);
            pushDown(x);
            if (!p->isRoot) {
                if ((g->leftChild == p) == (p->leftChild == x)) {
                    rotate(p);
                } else {
                    rotate(x);
                }
            }
            rotate(x);
        }
    }
    void rotate(LinkCutNode* x) {
        LinkCutNode* p = x->parent;
        LinkCutNode* g = p->parent;
        if (g) {
            if (g->leftChild == p) {
                g->leftChild = x;
            } else {
                g->rightChild = x;
            }
        }
        if (p->leftChild == x) {
            p->leftChild = x->rightChild;
            if (x->rightChild) {
                x->rightChild->parent = p;
            }
            x->rightChild = p;
        } else {
            p->rightChild = x->leftChild;
            if (x->leftChild) {
                x->leftChild->parent = p;
            }
            x->leftChild = p;
        }
        x->parent = g;
        p->parent = x;
    }
    void pushDown(LinkCutNode* x) {
        if (x->reversed) {
            std::swap(x->leftChild, x->rightChild);
            if (x->leftChild) {
                x->leftChild->reversed = !x->leftChild->reversed;
            }
            if (x->rightChild) {
                x->rightChild->reversed = !x->rightChild->reversed;
            }
            x->reversed = false;
        }
    }
public:
    LinkCutTree(int n) {
        nodes.reserve(n);
        for (int i = 0; i < n; ++i) {
            nodes.push_back(new LinkCutNode(i));
        }
    }
    ~LinkCutTree() {
        for (LinkCutNode* node : nodes) {
            delete node;
        }
    }
    void link(int x, int y) {
        link(nodes[x], nodes[y]);
    }
    void cut(int x) {
        cut(nodes[x]);
    }
    void makeRoot(int x) {
        makeRoot(nodes[x]);
    }
    bool connected(int x, int y) {
        return access(nodes[x]) == access(nodes[y]);
    }
    void printRoot(int x) {
        std::cout << "Root of node " << x << ": " << access(nodes[x])->key << std::endl;
    }
};
int main() {
    LinkCutTree linkCutTree(5);
    linkCutTree.link(0, 1);
    linkCutTree.link(1, 2);
    linkCutTree.link(2, 3);
    std::cout << "Is 0 connected to 3? " << (linkCutTree.connected(0, 3) ? "Yes" : "No") << std::endl;
    linkCutTree.makeRoot(0);
    linkCutTree.cut(2);
    std::cout << "Is 0 connected to 3 after cut? " << (linkCutTree.connected(0, 3) ? "Yes" : "No") << std::endl;
    linkCutTree.printRoot(2);
    return 0;
}
