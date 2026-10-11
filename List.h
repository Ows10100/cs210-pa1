#pragma once

#include <iostream>
#include <memory>

template <typename T>
class List {
public:
    virtual ~List() = default;

    virtual void addFront(T value) = 0;
    virtual void deleteFront() = 0;
    virtual void search(T value) = 0;
    virtual void print() = 0;

    virtual void addAnywhere(int position, T value) = 0;
    virtual void deleteAnywhere(int position) = 0;
    virtual void reverse() = 0;
    virtual void concat(List<T>* other) = 0;
};

// Forward declarations
template <typename T>
class ArrayList;

template <typename T>
class LinkedList;

// --- TOGGLE YOUR IMPLEMENTATION HERE ---
// Change to true to test LinkedList, or false to test ArrayList
#define TEST_LINKED_LIST false

#if TEST_LINKED_LIST
#include "LinkedList.h"
template <typename T>
List<T>* makeList() {
    return new LinkedList<T>();
}
#else
#include "ArrayList.h"
template <typename T>
List<T>* makeList() {
    return new ArrayList<T>();
}
#endif