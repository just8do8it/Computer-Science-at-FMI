#include "complexnode.h"

ComplexNode::ComplexNode(std::string type, std::string id, std::string name, unsigned level, Dictionary<std::string, std::string> attributes, 
                Node* parent, PVector<Node> children)
: Node(type, id, name, level, attributes, parent) {
    this->children = PVector<Node>(children.getCapacity());
    for (int i = 0; i < children.getSize(); ++i) {
        this->children.add(children[i]->clone());
    }
}

Node* ComplexNode::clone() const {
    Node *n = new ComplexNode(*this);
    return new ComplexNode(*this);
}

const PVector<Node>& ComplexNode::getChildren() const {
    return this->children;
}

void ComplexNode::addChild(Node* node) {
    node->setParent(this);
    this->children.add(node);
}

void ComplexNode::streamPrint(std::ostream& out) const {
    std::string tabs("");
    for (int i = 0; i < getLevel(); ++i) {
        tabs += "\t";
    }

    size_t attrCount = getAttributes().getSize();
    out << tabs << "<" << getName();       

    out << " id=\"" << this->getId() << "\"";

    if (attrCount) {
        out << " ";
        getAttributes()[0].print();
        for (int i = 1; i < attrCount; ++i) {
            out << " ";
            getAttributes()[i].print();
        }
    }
    out << ">\n";

    for (int i = 0; i < this->children.getSize(); ++i) {
        this->children[i]->streamPrint(out);
    }

    out << tabs << "</" << getName() << ">\n";
}