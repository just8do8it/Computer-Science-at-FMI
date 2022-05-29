#ifndef PAIR_HH
#define PAIR_HH
#include <iostream>
#include "../Vector/vector.h"

template <typename K, typename V>
class Pair {
    K key;
    V value;
public:
    Pair() = default;
    Pair(const K&, const V&);

    const K& getKey() const;
    const V& getValue() const;
    void setValue(const V&);
    void print() const;
};

#include "pair.inl"

#endif