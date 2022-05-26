#ifndef COMMAND_MANAGER_HH
#define COMMAND_MANAGER_HH
#include <fstream>
#include "node.h"

class CommandManager {
	PVector<Node> nodes;
	unsigned levelCount;
public:
	CommandManager(std::fstream&);

	void print() const;
	void select(const unsigned& id, const String& key) const;
	void set(const unsigned& id, const String& key, const String& value);
	void children(const unsigned& id) const;
	void children(const unsigned& id, const unsigned& n) const;
	void text(const unsigned& id) const;
	void del(const unsigned& id, const String& key) const;
	void newChild(const unsigned& id);
	void newChild(const unsigned& id, const String& xPath);
};

#endif