#include <iostream>
#include <vector>
#include <list>

struct Node {
    int data;
    Node* next;
};

struct BinaryTree {
    int value;
    BinaryTree* left;
    BinaryTree* right;
};

class LinkedList{
    public:
        int data;
        LinkedList* next;
};

int main() {
    Node node1 = {10, nullptr};
    Node node2 = {20, nullptr};
    node1.next = &node2;

    LinkedList node;
    
    BinaryTree tree1 = {30, nullptr, nullptr};

    std::cout << "Node1 data: " << node1.data << std::endl;
    std::cout << "Node2 data: " << node2.data << std::endl;
    std::cout << "Tree1 value: " << tree1.value << std::endl;

    return 0;
}

