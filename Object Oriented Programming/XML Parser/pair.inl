#include "pair.h"

#define DEFAULT_CAPACITY 8

template <typename K, typename V>
Pair<K, V>::Pair() {
    this->capacity = DEFAULT_CAPACITY;
    this->size = 0;
    this->keys = new Vector<K>(this->capacity);
    this->values = new Vector<V>(this->capacity);
}


template <typename K, typename V>
Pair<K, V>::Pair(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->keys = new Vector<K>(this->capacity);
    this->values = new Vector<V>(this->capacity);
}

template <typename K, typename V>
void Pair<K, V>::resize(size_t capacity) {
    Vector<K> tempKeys(this->keys, capacity, this->size);
    Vector<V> tempValues(this->values, capacity, this->size);

    this->capacity = capacity;
    this->keys = tempKeys;
    this->values = tempValues;
}


template <typename K, typename V>
void Pair<K, V>::addEntry(const K& key, const V& value) {
    if (this->size + 1 == this->capacity) {
        resize(this->capacity * 2);
    }

    // for (int i = 0; i < this->size; ++i) {
    //     if (this->keys[i] == key) {
    //         throw "Already existing pair!";
    //     }
    // }

    this->keys[this->size] = key;
    this->values[this->size] = value;

    this->size++;
}


template <typename K, typename V>
V& Pair<K, V>::findValue(const K& key) {
    for (int i = 0; i < this->size; ++i) {
        if (this->keys[i] == key) {
            return this->values[i];
        }
    }

    throw "No such key!";
}


template <typename K, typename V>
void Pair<K, V>::sortByKey() {
    for (int i = 0; i < this->size - 1; ++i) {
        for (int j = 0; j < this->size - i - 1; ++j) {
            if (this->keys[i] > this->keys[i + 1]) {
                K tempKey = this->keys[i];
                V tempValue = this->values[i];
                
                this->keys[i] = this->keys[i + 1];
                this->values[i] = this->values[i + 1];
                
                this->keys[i + 1] = tempKey;
                this->values[i + 1] = tempValue;
            }
        }
    }
}


template <typename K, typename V>
void Pair<K, V>::print() {
    sortByKey();
    for (int i = 0; i < this->size; ++i) {
        std::cout << this->keys[i] << ": " << this->values[i] << std::endl;
    }
}