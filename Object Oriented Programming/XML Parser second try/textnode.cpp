#include "textnode.h"

TextNode::TextNode(String id, String name, unsigned level, String text)
: Node(id, name, level), text(text) {}

TextNode::TextNode(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes, String text)
: Node(id, name, level, attributes), text(text) {}

TextNode::TextNode(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes, 
                    Node* parent, String text)
: Node(id, name, level, attributes, parent), text(text) {}

Node* TextNode::clone() const {
    return new TextNode(*this);
}

const String& TextNode::getText() const {
    return this->text;
}

void TextNode::print() const {
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

    std::cout << this->text;
    std::cout << "</" << getName() << ">" << std::endl;
}