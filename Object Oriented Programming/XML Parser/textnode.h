#ifndef TEXT_NODE_HH
#define TEXT_NODE_HH
#include "node.h"

class TextNode : public Node {
	std::string text;
public:
	TextNode(std::string, std::string, unsigned, Dictionary<std::string, std::string>, 
			Node*, std::string);
	
	const std::string& getText() const;
	Node* clone() const override;
	void print() const override;
};

#endif


