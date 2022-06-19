#include "complexnode.h"

ComplexNode::ComplexNode(std::string id, std::string name, unsigned level, Dictionary<std::string, std::string> attributes, 
                Node* parent, PVector<Node> children)
: Node(id, name, level, attributes, parent) {
    this->children = PVector<Node>(children.getCapacity());
    for (int i = 0; i < children.getSize(); ++i) {
        this->children.add(children[i]->clone());
    }
}

ComplexNode::ComplexNode(const ComplexNode& other) : Node(other) {
    this->children = PVector<Node>(other.children.getCapacity());

    for (int i = 0; i < other.children.getSize(); ++i) {
        this->children.add(other.children[i]->clone());
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

void ComplexNode::print() const {
    std::string tabs("");
    for (int i = 0; i < getLevel(); ++i) {
        tabs += "\t";
    }

    size_t attrCount = getAttributes().getSize();
    std::cout << tabs << "<" << getName() << " ";

    if (attrCount) {
        getAttributes()[0].print();
        for (int i = 1; i < attrCount; ++i) {
            std::cout << " ";
            getAttributes()[i].print();
        }
    }
    std::cout << ">" << std::endl;

    for (int i = 0; i < this->children.getSize(); ++i) {
        this->children[i]->print();
    }

    std::cout << tabs << "</" << getName() << ">" << std::endl;
}