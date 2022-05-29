#include "node.h"

Node::Node(String id, String name, unsigned level) : id(id), name(name), level(level) {
    this->attributes = new Vector<Pair<String, String>>();
    this->parent = nullptr;
}

Node::Node(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes) 
: id(id), name(name), level(level), attributes(attributes) {}

Node::Node(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes, Node* parent) 
: id(id), name(name), level(level), attributes(attributes), parent(parent) {}

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

const Node* Node::getParent() const {
    return this->parent;
}

Node* Node::clone() const {
    return new Node(*this);
}

void Node::print() const {
    String tabs("");
    for (int i = 0; i < getLevel(); ++i) {
        tabs += "\t";
    }

    size_t attrCount = getAttributes()->getSize();
    std::cout << tabs << "<" << getName() << " ";
    
    if (attrCount) {
        getAttributes()->operator[](0).print();
        for (int i = 1; i < attrCount; ++i) {
            std::cout << " ";
            getAttributes()->operator[](i).print();
        }
    }
    std::cout << ">";

    std::cout << "</" << getName() << ">" << std::endl;
}