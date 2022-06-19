#include "textnode.h"

TextNode::TextNode(std::string id, std::string name, unsigned level, Dictionary<std::string, std::string> attributes, 
        Node* parent, std::string text)
: Node(id, name, level, attributes, parent), text(text) {}

Node* TextNode::clone() const {
    return new TextNode(*this);
}

const std::string& TextNode::getText() const {
    return this->text;
}

void TextNode::print() const {
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
    std::cout << ">";

    std::cout << this->text;
    std::cout << "</" << getName() << ">" << std::endl;
}