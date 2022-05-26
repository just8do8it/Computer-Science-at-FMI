#include "dictionary.h"

#define DEFAULT_CAPACITY 8

template <typename K, typename V>
void Dictionary<K, V>::copyFrom(const Dictionary& other) {
    this->capacity = other.capacity;
    this->size = other.size;
    this->keys = new K[this->capacity];
    this->values = new V[this->capacity];

    for (int i = 0; i < this->size; ++i) {
        this->keys[i] = other.keys[i];
        this->values[i] = other.values[i];
    }
}


template <typename K, typename V>
void Dictionary<K, V>::free() {
    delete[] this->keys, this->values;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary() {
    this->capacity = DEFAULT_CAPACITY;
    this->size = 0;
    this->keys = new K[this->capacity];
    this->values = new V[this->capacity];
}


template <typename K, typename V>
Dictionary<K, V>::Dictionary(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->keys = new K[this->capacity];
    this->values = new V[this->capacity];
}


template <typename K, typename V>
Dictionary<K, V>::Dictionary(const Dictionary& other) {
    copyFrom(other);
}


template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::operator=(const Dictionary& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}


template <typename K, typename V>
Dictionary<K, V>::~Dictionary() {
    free();
}


template <typename K, typename V>
void Dictionary<K, V>::resize(size_t capacity) {
    K* nKeys = new K[capacity];
    V* nValues = new V[capacity];

    for (int i = 0; i < this->size; ++i) {
        nKeys[i] = this->keys[i];
        nValues[i] = this->values[i];
    }

    delete[] this->keys, this->values;
    this->capacity = capacity;
    this->keys = nKeys;
    this->values = nValues;
}


template <typename K, typename V>
void Dictionary<K, V>::addEntry(const K& key, const V& value) {
    if (this->size + 1 == this->capacity) {
        resize(this->capacity * 2);
    }

    for (int i = 0; i < this->size; ++i) {
        if (this->keys[i] == key) {
            throw "Already existing pair!";
        }
    }

    this->keys[this->size] = key;
    this->values[this->size] = value;

    this->size++;
}


template <typename K, typename V>
V& Dictionary<K, V>::findValue(const K& key) {
    for (int i = 0; i < this->size; ++i) {
        if (this->keys[i] == key) {
            return this->values[i];
        }
    }

    throw "No such key!";
}


template <typename K, typename V>
void Dictionary<K, V>::sortByKey() {
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
void Dictionary<K, V>::print() {
    sortByKey();
    for (int i = 0; i < this->size; ++i) {
        std::cout << this->keys[i] << ": " << this->values[i] << std::endl;
    }
}