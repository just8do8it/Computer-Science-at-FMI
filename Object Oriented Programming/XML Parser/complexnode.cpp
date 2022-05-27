#include "complexnode.h"

ComplexNode::ComplexNode(String id, String name, unsigned level, PVector<Node>* childNodes)
: Node(id, name, level), childNodes(childNodes) {}

ComplexNode::ComplexNode(String id, String name, unsigned level,
                Vector<Pair<String, String>>* attributes, PVector<Node>* childNodes)
: Node(id, name, level, attributes), childNodes(childNodes) {}

ComplexNode::ComplexNode(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes, 
                    PVector<Node>* parentNodes, PVector<Node>* childNodes)
: Node(id, name, level, attributes, parentNodes), childNodes(childNodes) {}

Node* ComplexNode::clone() const {
    return new ComplexNode(*this);
}

const PVector<Node>* ComplexNode::getChildNodes() const {
    return this->childNodes;
}

void ComplexNode::print() const {
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
    std::cout << ">" << std::endl;

    for (int i = 0; i < this->childNodes->getSize(); ++i) {
        this->childNodes->operator[](i)->print();
    }

    std::cout << tabs << "</" << getName() << ">" << std::endl;
}