#include <iostream>
#include "vector.h"
#define DEFAULT_CAPACITY 8

template <typename T>
void Vector<T>::copyFrom(const Vector& other) {
    this->size = other.size;
    this->capacity = other.capacity;

    this->items = new T[this->capacity];
    for (int i = 0; i < this->size; ++i) {
        this->items[i] = other.items[i];
    }
}

template <typename T>
void Vector<T>::free() {
    delete[] this->items;
}

template <typename T>
Vector<T>::Vector() {
    this->capacity = DEFAULT_CAPACITY;
    this->size = 0;
    this->items = new T[this->capacity];
}

template <typename T>
Vector<T>::Vector(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->items = new T[this->capacity];
}

template <typename T>
Vector<T>::Vector(const T* items, size_t capacity, size_t size) {
    this->size = size;
    this->capacity = capacity;
    for (int i = 0; i < this->size; ++i) {
        this->items[i] = items[i];
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
    copyFrom(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    free();
}

template <typename T>
T& Vector<T>::operator[](size_t index) const {
    return this->items[index];
}

template <typename T>
size_t Vector<T>::getCapacity() const {
    return this->capacity;
}

template <typename T>
size_t Vector<T>::getSize() const {
    return this->size;
}

template <typename T>
void Vector<T>::resize(size_t capacity) {
    T* temp = new T[capacity];

    for (int i = 0; i < this->size; ++i) {
        temp[i] = this->items[i];
    }

    free();
    this->items = temp;
}

template <typename T>
void Vector<T>::remove(const T& item) {
    bool flag = false;
    for (int i = 0; i < this->size - 1; ++i) {
        if (this->items[i] == item) {
            flag = true;
        }
        if (flag) {
            this->items[i] = this->items[i + 1];
        }
    }

    this->size--;

    if (this->size - 1 <= this->capacity / 3) {
        resize(this->size);
    }
}

template <typename T>
void Vector<T>::add(const T& item) {
    if (this->size + 1 == this->capacity) {
        resize(this->capacity * 2);
    }

    this->items[this->size] = item;
    this->size++;
}