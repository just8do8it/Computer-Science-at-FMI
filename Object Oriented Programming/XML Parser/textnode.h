#ifndef TEXT_NODE_HH
#define TEXT_NODE_HH
#include <iostream>
#include "node.h"

class TextNode : public Node {
	String text;
public:
	TextNode(String, String, String);
	TextNode(String, String, Vector<Pair<String, String>>, String);
	TextNode(String, String, Vector<Pair<String, String>>, PVector<Node>, String);
	Node* clone() const override;
};

#endif


