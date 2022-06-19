#include "engine.h"

Engine* Engine::instance = nullptr;

void Engine::run() {
    FileManager *fm = FileManager::getInstance();
    CommandManager *cm = fm->open();

    Dictionary<std::string, std::string> attributes1, attributes2, attributes3;

    attributes1.addEntry(new Pair<std::string, std::string>("color", "blue"));
    attributes1.addEntry(new Pair<std::string, std::string>("address", "Sofia"));
    attributes2.addEntry(new Pair<std::string, std::string>("color", "yellow"));
    attributes3.addEntry(new Pair<std::string, std::string>("car", "Nissan GTR"));
    
    Node* node1 = new ComplexNode("1", "people", 0, attributes1, nullptr, PVector<Node>());
    Node* node2 = new ComplexNode("2", "people", 1, attributes2, nullptr, PVector<Node>());
    Node* node3 = new TextNode("3", "flowers", 2, attributes3, nullptr, "innerText");
    
    cm->insertRoot(node1);
    ((ComplexNode*)node1)->addChild(node2);
    ((ComplexNode*)node2)->addChild(node3);


    cm->print();


    
    
    
    fm->free();
}

Engine* Engine::getInstance() {
    if (instance == nullptr) {
        instance = new Engine();
    }

    return instance;
}

void Engine::free() {
    delete instance;
}