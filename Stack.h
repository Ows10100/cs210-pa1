#pragma once
#include <iostream>
#include "Node.h"

// A linked-list-backed stack. Reuses the same Node<T> the rest of the
// project already uses. Not a wrapper around List<T>: List<T> has no
// way to hand back the value it removed, or to look at the front
// without removing it, and a real stack needs both. So Stack<T> talks
// to Node<T> directly, the same way Queue<T> does.
//
// The one ownership rule that's different from everything else in this
// project: pop() hands the T* back to the caller. It only deletes the
// Node, not the T inside it. Whoever calls pop() now owns that pointer
// and is responsible for deleting it eventually. Nothing that's still
// sitting in the stack when it's destroyed gets that treatment, the
// destructor deletes both layers for anything nobody ever popped.

template <typename T>
class Stack {
private:
    Node<T>* top_;
    int size_;

public:
    Stack() : top_(nullptr), size_(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top_;
        top_ = newNode;
        ++size_;
    }

    T pop() {
        if (isEmpty()) {
            return nullptr; // or default T value
        }
        Node<T>* doomed = top_;
        top_ = top_->next;
        T value = doomed->data;
        delete doomed;
        --size_;
        return value;
    }

    bool isEmpty() const {
        return top_ == nullptr;
    }

    int size() const {
        return size_;
    }
};