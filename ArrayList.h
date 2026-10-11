#pragma once
#include <iostream>
#include <memory>
#include "List.h"
#include "ArrayList.h" // Include this so makeList() is visible to main.cpp!
#include "Player.h"
#include "Card.h"
#include "Stack.h"

template <typename T>
class ArrayList : public List<T> {
private:
    T* data_;
    int capacity_;
    int size_;

public:
    ArrayList(int capacity = 100) : capacity_(capacity), size_(0) {
        data_ = new T[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            data_[i] = nullptr;
        }
    }

    ~ArrayList() override {
        for (int i = 0; i < size_; ++i) {
            delete data_[i];
        }
        delete[] data_;
    }

    void addFront(T value) override {
        if (size_ >= capacity_) {
            std::cout << "Error: ArrayList capacity reached." << std::endl;
            delete value;
            return;
        }
        for (int i = size_; i > 0; --i) {
            data_[i] = data_[i - 1];
        }
        data_[0] = value;
        ++size_;
    }

    void deleteFront() override {
        if (size_ == 0) {
            std::cout << "Error: List is empty." << std::endl;
            return;
        }
        delete data_[0];
        for (int i = 0; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        data_[size_ - 1] = nullptr;
        --size_;
    }

    void search(T value) override {
        for (int i = 0; i < size_; ++i) {
            if (*data_[i] == *value) {
                std::cout << "Found at index " << i << std::endl;
                return;
            }
        }
        std::cout << "Not found." << std::endl;
    }

    void print() override {
        for (int i = 0; i < size_; ++i) {
            std::cout << *data_[i] << ",";
        }
        std::cout << std::endl;
    }

    // --- New Assignment 1 Methods ---

    void addAnywhere(int position, T value) override {
        if (position < 0 || position > size_) {
            std::cout << "Error: Position out of bounds for addAnywhere." << std::endl;
            delete value;
            return;
        }
        if (size_ >= capacity_) {
            std::cout << "Error: ArrayList capacity reached." << std::endl;
            delete value;
            return;
        }
        for (int i = size_; i > position; --i) {
            data_[i] = data_[i - 1];
        }
        data_[position] = value;
        ++size_;
    }

    void deleteAnywhere(int position) override {
        if (position < 0 || position >= size_) {
            std::cout << "Error: Position out of bounds for deleteAnywhere." << std::endl;
            return;
        }
        delete data_[position];
        for (int i = position; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        data_[size_ - 1] = nullptr;
        --size_;
    }

    void reverse() override {
        if (size_ <= 1) return;
        int left = 0;
        int right = size_ - 1;
        while (left < right) {
            T temp = data_[left];
            data_[left] = data_[right];
            data_[right] = temp;
            ++left;
            --right;
        }
    }

    void concat(List<T>* other) override {
        ArrayList<T>* otherList = dynamic_cast<ArrayList<T>*>(other);
        if (otherList == nullptr) {
            std::cout << "Error: Representation mismatch in concat." << std::endl;
            return;
        }
        if (size_ + otherList->size_ > capacity_) {
            std::cout << "Error: Not enough capacity to concat." << std::endl;
            return;
        }
        for (int i = 0; i < otherList->size_; ++i) {
            data_[size_++] = otherList->data_[i];
            otherList->data_[i] = nullptr;
        }
        otherList->size_ = 0;
    }
};



