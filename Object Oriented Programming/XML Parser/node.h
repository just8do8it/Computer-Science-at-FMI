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
	Vector<Pair<String, String>>* attributes;
	PVector<Node>* parentNodes;
public:
	Node(String, String, unsigned);
	Node(String, String, unsigned, Vector<Pair<String, String>>*);
	Node(String, String, unsigned, Vector<Pair<String, String>>*, PVector<Node>*);

	const String& getId() const;
	const String& getName() const;
	const unsigned& getLevel() const;
	const Vector<Pair<String, String>>* getAttributes() const;
	const PVector<Node>* getParentNodes() const;

	virtual ~Node() = default;
	virtual Node* clone() const = 0;
	virtual void print() const = 0;
};

#endif