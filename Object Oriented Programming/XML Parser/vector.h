#ifndef VECTOR_HH
#define VECTOR_HH
#include <iostream>

template <typename T>
class Vector {
    T* items;
    size_t capacity;
    size_t size;

    void copyFrom(const Vector&);
    void free();
public:
    Vector();
    Vector(size_t);
    Vector(const T*, size_t, size_t);
    Vector(const Vector&);
    Vector& operator=(const Vector&);
    ~Vector();

    size_t getCapacity() const;
    size_t getSize() const;
    
    void resize();
    void add(const T&);
};

#include "vector.inl"

#endif