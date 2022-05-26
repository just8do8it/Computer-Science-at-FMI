#include "textnode.h"

TextNode::TextNode(String id, String name, String text)
: Node(id, name), text(text) {}

TextNode::TextNode(String id, String name, Vector<Pair<String, String>> attributes, String text)
: Node(id, name, attributes), text(text) {}

TextNode::TextNode(String id, String name, Vector<Pair<String, String>> attributes, 
                    PVector<Node> parentNodes, String text)
: Node(id, name, attributes, parentNodes), text(text) {}

Node* TextNode::clone() const {
    return new TextNode(*this);
}