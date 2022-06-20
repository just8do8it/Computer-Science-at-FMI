#include "textnode.h"

TextNode::TextNode(std::string type, std::string id, std::string name, unsigned level, Dictionary<std::string, std::string> attributes, 
        Node* parent, std::string text)
: Node(type, id, name, level, attributes, parent), text(text) {}

Node* TextNode::clone() const {
    return new TextNode(*this);
}



const std::string& TextNode::getText() const {
    return this->text;
}

void TextNode::streamPrint(std::ostream& out) const {
    std::string tabs("");
    for (int i = 0; i < getLevel(); ++i) {
        tabs += "\t";
    }

    size_t attrCount = getAttributes().getSize();
    out << tabs << "<" << getName();

    out << " id=\"" << this->getId() << "\"";
    if (attrCount) {
        getAttributes()[0].print();
        for (int i = 1; i < attrCount; ++i) {
            if (i > 1) out << " ";
            getAttributes()[i].print();
        }
    }
    out << ">";

    out << this->text;
    out << "</" << getName() << ">\n";
}