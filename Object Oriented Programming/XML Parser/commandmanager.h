#ifndef COMMAND_MANAGER_HH
#define COMMAND_MANAGER_HH
#include "nodemanager.h"

class CommandManager {
	NodeManager nodeManager;
	unsigned levelCount;
public:
	void print() const;
	void select(const unsigned& id, const String& key) const;
	void set(const unsigned& id, const String& key, const String& value);
	void children(const unsigned& id) const;
};

#endif