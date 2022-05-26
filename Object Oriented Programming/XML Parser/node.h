#ifndef NODE_HH
#define NODE_HH
#include <iostream>
#include "string.h"
#include "vector.h"
#include "pvector.h"
#include "pair.h"

class Node {
	String id;
	String name;
	unsigned level;
	Vector<Pair<String, String>> attributes;
	PVector<Node> parentNodes;
public:
	virtual ~Node() = default;
	virtual Node* clone() const = 0;
};

#endif