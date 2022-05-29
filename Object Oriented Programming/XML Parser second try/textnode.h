#ifndef TEXT_NODE_HH
#define TEXT_NODE_HH
#include <iostream>
#include "node.h"

class TextNode : public Node {
	String text;
public:
	TextNode(String, String, unsigned, String);
	TextNode(String, String, unsigned, Vector<Pair<String, String>>*, String);
	TextNode(String, String, unsigned, Vector<Pair<String, String>>*, Node*, String);
	
	const String& getText() const;
	Node* clone() const override;
	void print() const override;
};

#endif


