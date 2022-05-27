#include "commandmanager.h"

CommandManager::CommandManager(std::fstream& file) {
    this->nodes = new PVector<Node>();
    this->levelCount = 0;

    size_t start = file.tellg();
    file.seekg(0, std::ios::end);
    size_t end = file.tellg();
    file.seekg(0, std::ios::beg);
}

void CommandManager::print() const {
    for (int i = 0; i < this->nodes.getSize(); ++i) {
        if (this->nodes[i]->getLevel() == 0)
            this->nodes[i]->print();
    }
}
