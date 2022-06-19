#include "node.h"

void Node::copyFrom(const Node& other) {
    if (other.parent == nullptr) {
        this->parent = nullptr;
    } else {
        this->parent = other.parent->clone();
    }
}

void Node::free() {
    delete this->parent;
}

Node::Node(std::string id, std::string name, unsigned level, Dictionary<std::string, std::string> attributes, 
        Node* parent) 
: id(id), name(name), level(level), attributes(attributes) {
    if (parent != nullptr) {
        this->parent = parent->clone();
    } else {
        this->parent = nullptr;
    }
}

Node::Node(const Node& other)
: id(other.id), name(other.name), level(other.level), attributes(other.attributes) {
    copyFrom(other);
}

Node& Node::operator=(const Node& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

Node::~Node() {
    free();
}

const std::string& Node::getId() const {
    return this->id;
}

const std::string& Node::getName() const {
    return this->name;
}

const unsigned& Node::getLevel() const {
    return this->level;
}

const Dictionary<std::string, std::string>& Node::getAttributes() const {
    return this->attributes;
}

const Node* Node::getParent() const {
    return this->parent;
}

void Node::setParent(Node* other) {
    if (other == nullptr) {
        throw "Nullptr parent exception!";
    }
    this->parent = other;
}