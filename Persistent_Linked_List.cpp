#include <iostream>
struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};
class PersistentLinkedList {
private:
    Node* head;
public:
    PersistentLinkedList() : head(nullptr) {}
    PersistentLinkedList insert(int value) const {
        PersistentLinkedList newList;
        Node* newNode = new Node(value);
        newList.head = copyList(head);
        newNode->next = newList.head;
        newList.head = newNode;
        return newList;
    }
    void print() const {
        Node* current = head;
        std::cout << "List: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
private:
    Node* copyList(const Node* original) const {
        if (original == nullptr) {
            return nullptr;
        }
        Node* newHead = new Node(original->data);
        Node* newCurrent = newHead;
        const Node* current = original->next;
        while (current != nullptr) {
            newCurrent->next = new Node(current->data);
            newCurrent = newCurrent->next;
            current = current->next;
        }
        return newHead;
    }
};
int main() {
    PersistentLinkedList list1;
    list1 = list1.insert(1);
    list1 = list1.insert(2);
    list1 = list1.insert(3);
    list1.print();
    PersistentLinkedList list2 = list1.insert(4);
    list2.print();
    list1.print();
    return 0;
}
