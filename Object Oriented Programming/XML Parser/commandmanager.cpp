#include "commandmanager.h"
#include <stdlib.h>
#include <time.h> 
#include "textnode.h"
#include "complexnode.h"

CommandManager::CommandManager(std::fstream& file) {
    this->rootNodes = PVector<Node>();
    this->levelCount = 0;

    size_t start = file.tellg();
    file.seekg(0, std::ios::end);
    size_t end = file.tellg();
    file.seekg(0, std::ios::beg);

    char *contentStr = new char[end - start + 1];
    size_t formatChar = 0;
    for (int i = 0; i < end-start; ++i) {
        char ch;
        ch = file.get();
        contentStr[i] = ch;
    }
    contentStr[end-start] = '\0';

    std::string content(contentStr);

    size_t opened = 0, closed = 0, level = 0;
    Node *lastNode = nullptr;
    for (int i = 0; i < content.size(); ++i) {
        if (content[i] == '<') {
            if (content[i + 1] != '/') {               
                Vector<std::string> tagAttr;
                size_t currStart = i + 1;
                size_t j = i + 1;
                for (; ; ++j) {
                    if (content[j] == ' ' && tagAttr.getSize() == 0) {
                        tagAttr.add(content.substr(currStart, j - currStart));
                        currStart = j + 1;
                    }
                    else if (content[j] == '"' && content[j + 1] == ' ') {
                        tagAttr.add(content.substr(currStart, j - currStart + 1));
                        j++;
                        currStart = j + 1;
                    }
                    else if (content[j] == '"' && content[j + 1] == '>') {
                        tagAttr.add(content.substr(currStart, j - currStart + 1));
                        break;
                    }
                    else if (content[j] == '>' && content[j - 1] != '"') {
                        tagAttr.add(content.substr(currStart, j - currStart));
                        break;
                    }
                }

                opened++;

                std::string id;
                std::string name;
                unsigned lvl = level;
                Dictionary<std::string, std::string> attributes;
                Node* parent;

                srand(i);
                int randomId = rand() % 100 + 1;
                
                if (tagAttr.getSize() == 1 ||
                    (tagAttr.getSize() > 0 && tagAttr[1].substr(0, 2) != "id")) {
                    name = tagAttr[0];
                    id = std::to_string(randomId);
                } else {
                    name = tagAttr[0];  
                    id = tagAttr[1].substr(4, tagAttr[1].size() - 5);
                    for (int k = 2; k < tagAttr.getSize(); ++k) {
                        size_t start = 0;
                        for (int z = 0; z < tagAttr[k].size(); ++z) {
                            if (tagAttr[k][z] == '=') {
                                attributes.addEntry(new Pair<std::string, std::string>
                                                    (tagAttr[k].substr(start, z - start),
                                                    tagAttr[k].substr(z - start + 2, tagAttr[k].size() - z + start - 3)));
                                break;
                            }
                        }
                    }
                    j++;
                }


                Node *currNode;
                
                if (content[j + 1] < 33) {
                    currNode = new ComplexNode("complex", id, name, lvl, attributes, nullptr, PVector<Node>());
                    i = j - 1;
                } else {
                    std::string text;
                    int h;
                    for (h = 0; content[j + h] != '<'; ++h) {}
                    currNode = new TextNode("text", id, name, lvl, attributes, nullptr, content.substr(j + 1, h - 1));
                    i = j - 1 + h;
                }


                if (lvl == 0) {
                    this->rootNodes.add(currNode);
                }
                else {
                    if (lastNode->getLevel() == lvl) {
                        parent = lastNode->getParent();
                    }
                    else if (lastNode->getLevel() < lvl) {
                        parent = lastNode;
                    }
                    else {
                        parent = lastNode->getParent();
                        while(parent->getLevel() >= lvl) {
                            parent = parent->getParent();
                        }
                    }

                    currNode->setParent(parent);
                    ((ComplexNode*)parent)->addChild(currNode);
                }

                lastNode = currNode;
            }
            else closed++;
        }
        level = opened - closed;
        if (this->levelCount < level) this->levelCount = level;

    }
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
    streamPrintAll(std::cout);
}

void CommandManager::streamPrintAll(std::ostream& out) const {
    for (int i = 0; i < this->rootNodes.getSize(); ++i) {
        this->rootNodes[i]->streamPrint(out);
    }
}

Node* CommandManager::getNode(PVector<Node> nodes, const std::string& id) const {
    for (int i = 0; i < nodes.getSize(); ++i) {
        Node *curr = nodes[i];
        if (curr->getType() == "text") {
            if (curr->getId() == id) {
                return curr;
            }
        } else {
            int size = ((ComplexNode*)curr)->getChildren().getSize();
            for (int j = 0; j < size; ++j) {
                if (curr->getId() == id) {
                    return curr;
                } else {
                    return getNode(((ComplexNode*)curr)->getChildren(), id);
                }
            }
        }
    }

    return nullptr;
}


void CommandManager::select(const std::string& id, const std::string& key) const {
    Node *node = getNode(this->rootNodes, id);
    if (node == nullptr) {
        std::cout << "No such value!" << std::endl;
    } else {
        std::cout << node->getAttributes().getValue(key) << std::endl;
    }
}

void CommandManager::set(const std::string& id, const std::string& key, const std::string& value) {
    Node *node = getNode(this->rootNodes, id);
    if (node == nullptr) {
        std::cout << "No such key!" << std::endl;
    } else {
        node->getAttributes().setValue(key, value);
    }
}

void CommandManager::children(const std::string& id) const {
    Node *node = getNode(this->rootNodes, id);
    if (node == nullptr) {
        std::cout << "No such value!" << std::endl;
    } else {
        node->getAttributes().print();
    }
}

void CommandManager::children(const std::string& id, const unsigned& n) const {
    Node *node = getNode(this->rootNodes, id);
    if (n < node->getLevel() || n > this->levelCount || node->getType() == "text") {
        std::cout << "No such children!" << std::endl;
    } else {
        
    }
}



