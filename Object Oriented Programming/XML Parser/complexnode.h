#ifndef COMPLEX_NODE_HH
#define COMPLEX_NODE_HH
#include <iostream>
#include "node.h"

class ComplexNode : public Node {
	PVector<Node>* childNodes;
public:
    ComplexNode(String, String, unsigned, PVector<Node>*);
	ComplexNode(String, String, unsigned, Vector<Pair<String, String>>*, PVector<Node>*);
	ComplexNode(String, String, unsigned, Vector<Pair<String, String>>*, PVector<Node>*, PVector<Node>*);
	
	const PVector<Node>* getChildNodes() const;
	Node* clone() const override;
	void print() const override;
};

#endif


