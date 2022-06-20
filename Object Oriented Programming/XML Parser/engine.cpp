#include "engine.h"
#include <stdlib.h>

Engine* Engine::instance = nullptr;

void Engine::run() {
    // FileManager *fm = FileManager::getInstance();
    // CommandManager *cm;
    // std::fstream *file;

    // char buff[100];
    // Vector<std::string> args;
    
    // while(buff != "exit") {
    //     system("clear");
    //     fm->help();
    //     std::cout << "\n> ";
    //     std::cin.getline(buff, 100);

    //     std::string buffer(buff);

    //     std::cout << buffer;

    //     int currStart = 0;
    //     for (int i = 0; i < buffer.size(); ++i) {
    //         if (buffer[i] == ' ') {
    //             args.add(buffer.substr(currStart, i));
    //             currStart = i + 1;
    //         }
    //     }

    //     if (args[0] == "open") {
    //         file->open(args[1]);

    //         if (file->fail()) {
    //             throw "Can't open the file!";
    //         }

    //         cm = new CommandManager(*file);
    //     }
    //     else if (args[0] == "close") {
    //         file->close();
    //     }
    //     else if (args[0] == "save") {

    //         file->close();
    //     }
    //     else if (args[0] == "saveas") {
    //         file->close();
    //     }
    // }
    
    // fm->free();

    FileManager *fm = FileManager::getInstance();

    std::fstream file("data.xml");
    fm->open("data.xml");
    CommandManager *cm = new CommandManager(file);

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