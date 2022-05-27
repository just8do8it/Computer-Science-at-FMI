#include "pair.h"

#define DEFAULT_CAPACITY 8

template <typename K, typename V>
Pair<K, V>::Pair(const K& key, const V& value) {
    this->key = key;
    this->value = value;
}

template <typename K, typename V>
const K& Pair<K, V>::getKey() const {
    return this->key;
}

template <typename K, typename V>
const V& Pair<K, V>::getValue() const {
    return this->value;
}

template <typename K, typename V>
void Pair<K, V>::setValue(const V& value) {
    this->value = value;
}

template <typename K, typename V>
void Pair<K, V>::print() const {
    std::cout << this->key << ": " << this->value << std::endl;
}