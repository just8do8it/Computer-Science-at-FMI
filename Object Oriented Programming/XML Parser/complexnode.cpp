#include "complexnode.h"

ComplexNode::ComplexNode(String id, String name, PVector<Node> childNodes)
: Node(id, name), childNodes(childNodes) {}

ComplexNode::ComplexNode(String id, String name, 
                Vector<Pair<String, String>> attributes, PVector<Node> childNodes)
: Node(id, name, attributes), childNodes(childNodes) {}

ComplexNode::ComplexNode(String id, String name, Vector<Pair<String, String>> attributes, 
                    PVector<Node> parentNodes, PVector<Node> childNodes)
: Node(id, name, attributes, parentNodes), childNodes(childNodes) {}

Node* ComplexNode::clone() const {
    return new ComplexNode(*this);
}