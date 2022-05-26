#ifndef PAIR_HH
#define PAIR_HH
#include <iostream>
#include "vector.h"

template <typename K, typename V>
class Pair {
    Vector<K> keys;
    Vector<V> values;
    size_t capacity;
    size_t size;
public:
    Pair();
    Pair(size_t);

    size_t getCapacity() const;
    size_t getSize() const;
    
    void resize(size_t);
    void addEntry(const K& key, const V& value);
    V& findValue(const K& key);
    void sortByKey();
    void print();
};

#include "pair.inl"

#endif