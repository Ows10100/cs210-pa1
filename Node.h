#pragma once

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
    
    ~Node() {
        // Note: Depending on your design, data ownership is managed by the list/stack,
        // but if your Node.h needs a specific destructor from class, use your existing one.
    }
};