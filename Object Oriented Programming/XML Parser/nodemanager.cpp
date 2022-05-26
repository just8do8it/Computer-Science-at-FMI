#include <iostream>
#include "nodemanager.h"

#define DEFAULT_CAPACITY 8

void NodeManager::copyFrom(const NodeManager& other) {
    this->size = other.size;
    this->capacity = other.capacity;

    this->events = new Node*[this->capacity];
    for (int i = 0; i < this->size; ++i) {
        this->events[i] = other.events[i]->clone();
    }
}

void NodeManager::free() {
    for (int i = 0; i < this->size; ++i) {
        delete this->events[i];
    }

    delete[] this->events;
}

NodeManager::NodeManager() {
    this->capacity = DEFAULT_CAPACITY;
    this->size = 0;
    this->events = new Node*[this->capacity];
}

NodeManager::NodeManager(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->events = new Node*[this->capacity];
}

NodeManager::NodeManager(const NodeManager& other) {
    copyFrom(other);
}

NodeManager& NodeManager::operator=(const NodeManager& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

NodeManager::~NodeManager() {
    free();
}

size_t NodeManager::getCapacity() const {
    return this->capacity;
}

size_t NodeManager::getSize() const {
    return this->size;
}

void NodeManager::resize() {
    NodeManager copy(*this);
    copy.capacity = this->capacity * 2;
    free();
    copyFrom(copy);
}

bool NodeManager::add(const Node* event) {
    if (this->size + 1 == this->capacity) {
        return false;
    }

    this->events[this->size] = event->clone();
    this->size++;

    return true;
}