#ifndef NODE_HH
#define NODE_HH
#include <iostream>
#include "String/string.h"
#include "Vector/vector.h"
#include "PVector/pvector.h"
#include "Pair/pair.h"

class Node {
	String id;
	String name;
	unsigned level;
	Vector<Pair<String, String>>* attributes;
	Node* parent;
public:
	Node(String, String, unsigned);
	Node(String, String, unsigned, Vector<Pair<String, String>>*);
	Node(String, String, unsigned, Vector<Pair<String, String>>*, Node*);

	const String& getId() const;
	const String& getName() const;
	const unsigned& getLevel() const;
	const Vector<Pair<String, String>>* getAttributes() const;
	const Node* getParent() const;

	virtual ~Node() = default;
	virtual Node* clone() const;
	virtual void print() const;
};

#endif