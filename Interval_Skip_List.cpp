#include <iostream>
#include <limits>
class IntervalSkipList {
private:
    struct Node {
        int start;
        int end;
        Node** next;
        int level;
        Node(int s, int e, int lev)
            : start(s), end(e), level(lev) {
            next = new Node*[level + 1];
            std::fill(next, next + level + 1, nullptr);
        }
        ~Node() {
            delete[] next;
        }
    };
    const int MAX_LEVEL = 16; 
    const float PROBABILITY = 0.5;  
    Node* header;  
public:
    IntervalSkipList() {
        header = new Node(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), MAX_LEVEL);
    }
    ~IntervalSkipList() {
        deleteList();
    }
    void insert(int start, int end) {
        Node* update[MAX_LEVEL + 1];
        Node* current = header;
        for (int i = MAX_LEVEL; i >= 0; --i) {
            while (current->next[i] != nullptr && current->next[i]->start < start) {
                current = current->next[i];
            }
            update[i] = current;
        }
        int newLevel = randomLevel();
        if (newLevel > MAX_LEVEL) {
            newLevel = MAX_LEVEL;
        }
        Node* newNode = new Node(start, end, newLevel);
        for (int i = 0; i <= newLevel; ++i) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
    void remove(int start, int end) {
        Node* update[MAX_LEVEL + 1];
        Node* current = header;
        for (int i = MAX_LEVEL; i >= 0; --i) {
            while (current->next[i] != nullptr && current->next[i]->start < start) {
                current = current->next[i];
            }
            update[i] = current;
        }
        current = current->next[0];
        if (current != nullptr && current->start == start && current->end == end) {
            for (int i = 0; i <= MAX_LEVEL; ++i) {
                if (update[i]->next[i] != current) {
                    break;
                }
                update[i]->next[i] = current->next[i];
            }
            delete current;
        }
    }
    void search(int start, int end) {
        Node* current = header;
        for (int i = MAX_LEVEL; i >= 0; --i) {
            while (current->next[i] != nullptr && current->next[i]->start < end) {
                if (current->next[i]->end > start) {
                    std::cout << "[" << current->next[i]->start << ", " << current->next[i]->end << "] ";
                }
                current = current->next[i];
            }
        }
        std::cout << std::endl;
    }
private:
    int randomLevel() {
        int level = 0;
        while (level < MAX_LEVEL && ((double)std::rand() / RAND_MAX) < PROBABILITY) {
            level++;
        }
        return level;
    }
    void deleteList() {
        Node* current = header->next[0];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next[0];
            delete temp;
        }
        delete header;
    }
};
int main() {
    IntervalSkipList skipList;
    skipList.insert(15, 25);
    skipList.insert(5, 12);
    skipList.insert(7, 17);
    skipList.insert(8, 23);
    skipList.insert(16, 27);
    std::cout << "Skip List after insertion:" << std::endl;
    skipList.search(10, 20);
    skipList.remove(8, 23);
    std::cout << "Skip List after removal:" << std::endl;
    skipList.search(10, 20);
    return 0;
}
