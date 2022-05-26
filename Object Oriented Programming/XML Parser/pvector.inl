#include <iostream>
#include "pvector.h"
#define DEFAULT_CAPACITY 8

template <typename T>
void PVector<T>::copyFrom(const PVector& other) {
    this->size = other.size;
    this->capacity = other.capacity;

    this->items = new T*[this->capacity];
    for (int i = 0; i < this->size; ++i) {
        this->items[i] = other.items[i]->clone();
    }
}

template <typename T>
void PVector<T>::free() {
    for (int i = 0; i < this->size; ++i) {
        delete this->items[i];
    }

    delete[] this->items;
}

template <typename T>
PVector<T>::PVector() {
    this->capacity = DEFAULT_CAPACITY;
    this->size = 0;
    this->items = new T*[this->capacity];
}

template <typename T>
PVector<T>::PVector(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->items = new T*[this->capacity];
}

template <typename T>
PVector<T>::PVector(const PVector& other) {
    copyFrom(other);
}

template <typename T>
PVector<T>& PVector<T>::operator=(const PVector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
PVector<T>::~PVector() {
    free();
}

template <typename T>
size_t PVector<T>::getCapacity() const {
    return this->capacity;
}

template <typename T>
size_t PVector<T>::getSize() const {
    return this->size;
}

template <typename T>
void PVector<T>::resize() {
    T** temp = new T*[this->capacity * 2];

    for (int i = 0; i < this->size; ++i) {
        temp[i] = this->items[i]->clone();
    }

    free();
    this->items = temp;
}

template <typename T>
void PVector<T>::add(const T& item) {
    if (this->size + 1 == this->capacity) {
        resize();
    }

    this->items[this->size] = item->clone();
    this->size++;
}