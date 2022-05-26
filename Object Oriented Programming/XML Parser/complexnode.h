#ifndef COMPLEX_NODE_HH
#define COMPLEX_NODE_HH
#include <iostream>
#include "node.h"

class ComplexNode : public Node {
	NodeManager childNodes;
public:
    Node* clone() const;
};

#endif


