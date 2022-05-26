#include "node.h"

Node::Node(String id, String name) : id(id), name(name) {
    this->attributes = Vector<Pair<String, String>>();
    this->parentNodes = PVector<Node>();
}

Node::Node(String id, String name, Vector<Pair<String, String>> attributes) 
: id(id), name(name), attributes(attributes) {}

Node::Node(String id, String name, Vector<Pair<String, String>> attributes, PVector<Node> parentNodes) 
: id(id), name(name), attributes(attributes), parentNodes(parentNodes) {}