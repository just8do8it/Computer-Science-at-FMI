#ifndef PVECTOR_HH
#define PVECTOR_HH
#include <iostream>

template <typename T>
class PVector {
    T** items;
    size_t capacity;
    size_t size;

    void copyFrom(const PVector&);
    void free();
public:
    PVector();
    PVector(size_t);
    PVector(const PVector&);
    PVector& operator=(const PVector&);
    ~PVector();

    size_t getCapacity() const;
    size_t getSize() const;

    void resize();
    void add(const T&);
};

#include "pvector.inl"

#endif