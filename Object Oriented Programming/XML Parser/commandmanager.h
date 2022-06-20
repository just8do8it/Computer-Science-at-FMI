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

	Node* getNode(PVector<Node> nodes, const std::string&) const;
	void print() const;
	void streamPrintAll(std::ostream&) const;
	void select(const std::string& id, const std::string& key) const;
	void set(const std::string& id, const std::string& key, const std::string& value);
	void children(const std::string& id) const;
	void children(const std::string& id, const unsigned& n) const;
	void text(const std::string& id) const;
	void del(const std::string& id, const std::string& key) const;
	void newChild(const std::string& id);
	void xPath(const std::string& id, const std::string& path);
};

#endif