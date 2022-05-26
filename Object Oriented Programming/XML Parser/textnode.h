#ifndef TEXT_NODE_HH
#define TEXT_NODE_HH
#include <iostream>
#include "node.h"

class TextNode : public Node {
	std::string text;
public:
	Node* clone() const;
};

#endif


