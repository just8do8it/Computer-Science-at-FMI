#include "dictionary.h"

#define DEFAULT_CAPACITY 8

template <typename K, typename V>
void Dictionary<K, V>::copyFrom(const Dictionary& other) {
    this->capacity = other.capacity;
    this->size = other.size;
    this->pairs = new Pair<K, V>[this->capacity];

    for (int i = 0; i < this->size; ++i) {
        this->pairs[i] = other.pairs[i];
    }
}


template <typename K, typename V>
void Dictionary<K, V>::free() {
    delete[] this->pairs;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary() {
    this->capacity = DEFAULT_CAPACITY;
    this->size = 0;
    this->pairs = new Pair<K, V>[this->capacity];
}


template <typename K, typename V>
Dictionary<K, V>::Dictionary(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->pairs = new Pair<K, V>[this->capacity];
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
    nPairs = new Pair<K, V>[capacity];

    for (int i = 0; i < this->size; ++i) {
        nPairs[i] = this->pairs[i];
    }

    delete[] this->pairs;
    this->capacity = capacity;
    this->pairs = pairs;
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

    this->pairs[this->size] = Pair<K, V>(key, value);
    this->size++;
}


template <typename K, typename V>
V& Dictionary<K, V>::getValue(const K& key) {
    for (int i = 0; i < this->size; ++i) {
        if (this->pairs[i].getKey() == key) {
            return this->pairs[i].getValue();
        }
    }

    throw "No such key!";
}


template <typename K, typename V>
void Dictionary<K, V>::sortByKey() {
    for (int i = 0; i < this->size - 1; ++i) {
        for (int j = 0; j < this->size - i - 1; ++j) {
            if (this->pairs[i].getKey() > this->pairs[i + 1].getKey()) {
                Pair<K, V> temp = this->pairs[i];
                this->pairs[i] = this->pairs[i + 1];
                this->pairs[i + 1] = temp;
            }
        }
    }
}


template <typename K, typename V>
size_t Dictionary<K, V>::getSize() const {
    return this->size;
}

template <typename K, typename V>
size_t Dictionary<K, V>::getCapacity() const {
    return this->capacity;
}

template <typename K, typename V>
void Dictionary<K, V>::print() {
    sortByKey();
    for (int i = 0; i < this->size; ++i) {
        std::cout << this->pairs[i].getKey() << ": " << this->pairs[i].getValue() << std::endl;
    }
}

template <typename K, typename V>
Pair<K, V>& Dictionary<K, V>::operator[](size_t index) const {
    if (index > this->size) {
        throw "Index out of boundaries!";
    }
    return this->pairs[index];
}