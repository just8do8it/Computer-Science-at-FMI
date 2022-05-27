#include "node.h"

Node::Node(String id, String name, unsigned level) : id(id), name(name), level(level) {
    this->attributes = new Vector<Pair<String, String>>();
    this->parentNodes = new PVector<Node>();
}

Node::Node(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes) 
: id(id), name(name), level(level), attributes(attributes) {}

Node::Node(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes, PVector<Node>* parentNodes) 
: id(id), name(name), level(level), attributes(attributes), parentNodes(parentNodes) {}

const String& Node::getId() const {
    return this->id;
}

const String& Node::getName() const {
    return this->name;
}

const unsigned& Node::getLevel() const {
    return this->level;
}

const Vector<Pair<String, String>>* Node::getAttributes() const {
    return this->attributes;
}

const PVector<Node>* Node::getParentNodes() const {
    return this->parentNodes;
}