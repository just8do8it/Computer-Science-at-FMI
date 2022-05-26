#ifndef NODE_HH
#define NODE_HH
#include <iostream>
#include "nodemanager.h"

class Node {
	std::string id;
	std::string name;
	unsigned level;
	// std::vector<std::pair<std::string, std::string>> attributes;
	NodeManager nodeManager;
public:
	virtual ~Node() = default;
	virtual Node* clone() const = 0;
};

#endif