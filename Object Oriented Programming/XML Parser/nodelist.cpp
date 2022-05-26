#include <iostream>
#include "nodelist.h"

#define DEFAULT_CAPACITY 8

void NodeList::copyFrom(const NodeList& other) {
    this->size = other.size;
    this->capacity = other.capacity;

    this->nodes = new Node*[this->capacity];
    for (int i = 0; i < this->size; ++i) {
        this->nodes[i] = other.nodes[i]->clone();
    }
}

void NodeList::free() {
    for (int i = 0; i < this->size; ++i) {
        delete this->nodes[i];
    }

    delete[] this->nodes;
}

NodeList::NodeList() {
    this->capacity = DEFAULT_CAPACITY;
    this->size = 0;
    this->nodes = new Node*[this->capacity];
}

NodeList::NodeList(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->nodes = new Node*[this->capacity];
}

NodeList::NodeList(const NodeList& other) {
    copyFrom(other);
}

NodeList& NodeList::operator=(const NodeList& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

NodeList::~NodeList() {
    free();
}

size_t NodeList::getCapacity() const {
    return this->capacity;
}

size_t NodeList::getSize() const {
    return this->size;
}

void NodeList::resize() {
    Node** temp = new Node*[this->capacity * 2];

    for (int i = 0; i < this->size; ++i) {
        temp[i] = this->nodes[i]->clone();
    }

    free();
    this->nodes = temp;
}

void NodeList::add(const Node* node) {
    if (this->size + 1 == this->capacity) {
        resize();
    }

    this->nodes[this->size] = node->clone();
    this->size++;
}