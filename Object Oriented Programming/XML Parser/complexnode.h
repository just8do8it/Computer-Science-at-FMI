#ifndef COMPLEX_NODE_HH
#define COMPLEX_NODE_HH
#include "node.h"

class ComplexNode : public Node {
	PVector<Node> children;
public:
	ComplexNode(std::string, std::string, unsigned, Dictionary<std::string, std::string>, Node*, PVector<Node>);
	ComplexNode(const ComplexNode&);
	const PVector<Node>& getChildren() const;
	void addChild(Node*);
	Node* clone() const override;
	void print() const override;
};

#endif


