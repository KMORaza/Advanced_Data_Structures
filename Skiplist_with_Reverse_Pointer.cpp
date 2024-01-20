#include <iostream>
#include <vector>
#include <limits>
class SkipNode {
public:
    int key;
    int height;
    SkipNode* forward;
    SkipNode* backward;
    SkipNode(int k, int h) : key(k), height(h), forward(nullptr), backward(nullptr) {}
};
class SkipList {
private:
    int maxLevel;
    SkipNode* header;
    int getRandomHeight() {
        int height = 1;
        while ((rand() % 2 == 0) && (height < maxLevel))
            height++;
        return height;
    }
public:
    SkipList(int maxLvl) : maxLevel(maxLvl) {
        header = new SkipNode(std::numeric_limits<int>::min(), maxLevel);
    }
    ~SkipList() {
        while (header->forward) {
            SkipNode* temp = header->forward;
            header->forward = temp->forward;
            delete temp;
        }
        delete header;
    }
    void insert(int key) {
        std::vector<SkipNode*> update(maxLevel + 1, nullptr);
        SkipNode* current = header;
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward && current->forward->key < key)
                current = current->forward;
            update[i] = current;
        }
        int newHeight = getRandomHeight();
        if (newHeight > maxLevel) {
            newHeight = maxLevel + 1;
            update.resize(newHeight + 1);
            update[maxLevel + 1] = header;
            maxLevel = newHeight;
        }
        SkipNode* newNode = new SkipNode(key, newHeight);
        for (int i = 0; i <= newHeight; i++) {
            newNode->forward = update[i]->forward;
            update[i]->forward = newNode;
            if (i > 0) {
                if (update[i]->forward)
                    update[i]->forward->backward = newNode;
                newNode->backward = update[i];
            }
        }
    }
    void printSkipList() {
        for (int i = maxLevel; i >= 0; i--) {
            SkipNode* current = header->forward;
            while (current) {
                if (current->height >= i) {
                    std::cout << current->key << " ";
                }
                current = current->forward;
            }
            std::cout << std::endl;
        }
    }
};
int main() {
    SkipList skipList(4);
    skipList.insert(3);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(9);
    skipList.insert(12);
    std::cout << "Skip List:" << std::endl;
    skipList.printSkipList();
    return 0;
}
