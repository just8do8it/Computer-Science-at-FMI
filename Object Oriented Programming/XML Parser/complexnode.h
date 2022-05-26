#ifndef COMPLEX_NODE_HH
#define COMPLEX_NODE_HH
#include <iostream>
#include "node.h"

class ComplexNode : public Node {
	PVector<Node> childNodes;
public:
    ComplexNode(String, String, PVector<Node>);
	ComplexNode(String, String, Vector<Pair<String, String>>, PVector<Node>);
	ComplexNode(String, String, Vector<Pair<String, String>>, PVector<Node>, PVector<Node>);
	Node* clone() const override;
};

#endif


