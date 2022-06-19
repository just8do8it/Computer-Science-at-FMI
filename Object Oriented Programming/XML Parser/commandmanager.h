#ifndef COMMAND_MANAGER_HH
#define COMMAND_MANAGER_HH
#include <fstream>
#include "node.h"

class CommandManager {
	PVector<Node> rootNodes;
	unsigned levelCount;
public:
	CommandManager(std::fstream&);

	const PVector<Node>& getRootNodes() const;
	unsigned getLevelCount() const;

	void insertRoot(Node*);

	void print() const;
	void select(const unsigned& id, const std::string& key) const;
	void set(const unsigned& id, const std::string& key, const std::string& value);
	void children(const unsigned& id) const;
	void children(const unsigned& id, const unsigned& n) const;
	void text(const unsigned& id) const;
	void del(const unsigned& id, const std::string& key) const;
	void newChild(const unsigned& id);
	void xPath(const unsigned& id, const std::string& path);
};

#endif