#ifndef DICTIONARY_HH
#define DICTIONARY_HH
#include <iostream>
#include "../Pair/pair.h"

template <typename K, typename V>
class Dictionary {
    Pair<K, V>* pairs;
    size_t capacity;
    size_t size;

    void copyFrom(const Dictionary&);
    void free();
public:
    Dictionary();
    Dictionary(size_t);
    Dictionary(const Dictionary&);
    Dictionary& operator=(const Dictionary&);
    ~Dictionary();

    size_t getSize() const;
    size_t getCapacity() const;

    Pair<K, V>& operator[](size_t) const;
    void resize(size_t);
    void addEntry(Pair<K, V>*);
    const V& getValue(const K& key) const;
    void setValue(const K& key, const V& value) const;
    void sortByKey();
    void print() const;
};


#include "dictionary.inl"

#endif