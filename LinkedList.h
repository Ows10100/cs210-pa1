#pragma once
#include "List.h"
#include "Node.h"
#include <iostream>

template <typename T>
class LinkedList : public List<T> {
private:
    Node<T>* head_;
    int size_; // Required for bounds checking in addAnywhere/deleteAnywhere[cite: 6]

public:
    LinkedList() : head_(nullptr), size_(0) {}

    ~LinkedList() override {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current->data; // free heap T object
            delete current;       // free node
            current = nextNode;
        }
    }

    void addFront(T value) override {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head_;
        head_ = newNode;
        ++size_; // update size
    }

    void deleteFront() override {
        if (head_ == nullptr) {
            std::cout << "Error: List is empty." << std::endl;
            return;
        }
        Node<T>* doomed = head_;
        head_ = head_->next;
        delete doomed->data; // free heap T object
        delete doomed;
        --size_; // update size
    }

    void search(T value) override {
        Node<T>* current = head_;
        int index = 0;
        while (current != nullptr) {
            if (*current->data == *value) {
                std::cout << "Found at index " << index << std::endl;
                return;
            }
            current = current->next;
            ++index;
        }
        std::cout << "Not found." << std::endl;
    }

    void print() override {
        Node<T>* current = head_;
        while (current != nullptr) {
            std::cout << *current->data << ",";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // --- New Assignment 1 Methods ---

    void addAnywhere(int position, T value) override {
        if (position < 0 || position > size_) {
            std::cout << "Error: Position out of bounds for addAnywhere." << std::endl;
            delete value; // avoid memory leak
            return;
        }
        if (position == 0) {
            addFront(value);
            return;
        }
        Node<T>* current = head_;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        Node<T>* newNode = new Node<T>(value);
        newNode->next = current->next;
        current->next = newNode;
        ++size_; // update size[cite: 6]
    }

    void deleteAnywhere(int position) override {
        if (position < 0 || position >= size_) {
            std::cout << "Error: Position out of bounds for deleteAnywhere." << std::endl;
            return;
        }
        if (position == 0) {
            deleteFront();
            return;
        }
        Node<T>* current = head_;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        Node<T>* doomed = current->next;
        current->next = doomed->next;
        delete doomed->data; // free heap T object
        delete doomed;
        --size_; // update size[cite: 6]
    }

    void reverse() override {
        if (head_ == nullptr || head_->next == nullptr) return;
        Node<T>* prev = nullptr;
        Node<T>* current = head_;
        Node<T>* nextNode = nullptr;
        while (current != nullptr) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head_ = prev;
    }

    void concat(List<T>* other) override {
        LinkedList<T>* otherList = dynamic_cast<LinkedList<T>*>(other);
        if (otherList == nullptr) {
            std::cout << "Error: Representation mismatch in concat." << std::endl;
            return;
        }
        if (otherList->head_ == nullptr) return;

        if (head_ == nullptr) {
            head_ = otherList->head_;
            size_ = otherList->size_;
        } else {
            Node<T>* current = head_;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = otherList->head_;
            size_ += otherList->size_;
        }
        otherList->head_ = nullptr;
        otherList->size_ = 0; // other list is now empty[cite: 7]
    }
};

// To test LinkedList instead of ArrayList, switch the return type here:
// template <typename T>
// List<T>* makeList() {
//     return new LinkedList<T>();
// }