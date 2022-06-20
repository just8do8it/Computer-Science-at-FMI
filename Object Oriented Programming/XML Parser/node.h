#ifndef NODE_HH
#define NODE_HH
#include <string>
#include "Vector/vector.h"
#include "PVector/pvector.h"
#include "Dictionary/dictionary.h"

class Node {
	std::string type;
	std::string id;
	std::string name;
	unsigned level;
	Dictionary<std::string, std::string> attributes;
	Node* parent;

	void copyFrom(const Node&);
	void free();
public:
	Node(std::string, std::string, std::string, unsigned, Dictionary<std::string, std::string>, Node*);
	Node(const Node&);
	Node& operator=(const Node&);
	
	const std::string& getType() const;
	const std::string& getId() const;
	const std::string& getName() const;
	const unsigned& getLevel() const;
	const Dictionary<std::string, std::string>& getAttributes() const;
	Node* getParent() const;

	void setParent(Node*);

	virtual ~Node();
	virtual Node* clone() const = 0;
	virtual void streamPrint(std::ostream&) const = 0;
};

#endif