#include "engine.h"

Engine* Engine::instance = nullptr;

void Engine::run() {
    FileManager *fm = FileManager::getInstance();
    CommandManager *cm = fm->open();

    cm->streamPrintAll(std::cout);
    
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