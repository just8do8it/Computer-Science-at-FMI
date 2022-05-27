#include "textnode.h"

TextNode::TextNode(String id, String name, unsigned level, String text)
: Node(id, name, level), text(text) {}

TextNode::TextNode(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes, String text)
: Node(id, name, level, attributes), text(text) {}

TextNode::TextNode(String id, String name, unsigned level, Vector<Pair<String, String>>* attributes, 
                    PVector<Node>* parentNodes, String text)
: Node(id, name, level, attributes, parentNodes), text(text) {}

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
    std::cout << tabs << "<" << getName() << ">";
    std::cout << this->text;
    std::cout << "</" << getName() << ">" << std::endl;
}