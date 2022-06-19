#include "commandmanager.h"

CommandManager::CommandManager(std::fstream& file) {
    this->rootNodes = PVector<Node>();
    this->levelCount = 0;

    size_t start = file.tellg();
    file.seekg(0, std::ios::end);
    size_t end = file.tellg();
    file.seekg(0, std::ios::beg);
}

const PVector<Node>& CommandManager::getRootNodes() const {
    return this->rootNodes;
}

unsigned CommandManager::getLevelCount() const {
    return this->levelCount;
}
	
void CommandManager::insertRoot(Node* node) {
    this->rootNodes.add(node);
}

void CommandManager::print() const {
    for (int i = 0; i < this->rootNodes.getSize(); ++i) {
        this->rootNodes[i]->print();
    }
}
