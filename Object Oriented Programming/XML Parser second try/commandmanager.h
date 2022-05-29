#ifndef COMMAND_MANAGER_HH
#define COMMAND_MANAGER_HH
#include <iostream>
#include <fstream>
#include "node.h"
#include "dictionary.h"

class CommandManager {
	Dictionary<String, Node*>* nodes;
	unsigned levelCount;
public:
	CommandManager(std::fstream&);
	void insert(const Node*);

	void print() const;
	void select(const unsigned& id, const String& key) const;
	void set(const unsigned& id, const String& key, const String& value);
	void children(const unsigned& id) const;
	void children(const unsigned& id, const unsigned& n) const;
	void text(const unsigned& id) const;
	void del(const unsigned& id, const String& key) const;
	void newChild(const unsigned& id);
	void xPath(const unsigned& id, const String& path);
};

#endif