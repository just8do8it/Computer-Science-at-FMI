#ifndef COMMAND_MANAGER_HH
#define COMMAND_MANAGER_HH
#include "node.h"

class CommandManager {
	PVector<Node> nodes;
	unsigned levelCount;
public:
	void print() const;
	void select(const unsigned& id, const String& key) const;
	void set(const unsigned& id, const String& key, const String& value);
	void children(const unsigned& id) const;
};

#endif