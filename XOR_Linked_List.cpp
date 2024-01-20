// Implementation of XOR linked list
#include <iostream>
#include <cstdint>
class Node {
public:
    int data;
    Node* xorPointer;  
    Node(int val) : data(val), xorPointer(nullptr) {}
};
class XORLinkedList {
private:
    Node* head;
public:
    XORLinkedList() : head(nullptr) {}
    void insert(int data) {
        Node* newNode = new Node(data);
        newNode->xorPointer = head;
        if (head != nullptr) {
            head->xorPointer = XOR(head->xorPointer, newNode);
        }
        head = newNode;
    }
    void printForward() const {
        Node* current = head;
        Node* prev = nullptr;
        Node* next;
        std::cout << "Forward traversal: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            next = XOR(prev, current->xorPointer);
            prev = current;
            current = next;
        }
        std::cout << std::endl;
    }
    void printBackward() const {
        Node* current = head;
        Node* prev = nullptr;
        Node* next;
        std::cout << "Backward traversal: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            next = XOR(prev, current->xorPointer);
            prev = current;
            current = next;
        }
        std::cout << std::endl;
    }
private:
    Node* XOR(Node* a, Node* b) const {
        return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
    }
};
int main() {
    XORLinkedList xorList;
    xorList.insert(1);
    xorList.insert(2);
    xorList.insert(3);
    xorList.insert(4);
    xorList.printForward();
    xorList.printBackward();
    return 0;
}
