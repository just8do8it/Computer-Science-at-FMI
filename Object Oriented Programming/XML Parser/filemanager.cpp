#include "filemanager.h"

FileManager* FileManager::instance = nullptr;

FileManager* FileManager::getInstance() {
    if (instance == nullptr) {
        instance = new FileManager();
    }

    return instance;
}

void FileManager::free() {
    delete instance;
}

const std::string& FileManager::getCurrFilename() const {
    return this->currFilename;
}

void FileManager::open(std::string filename) {
    this->currFilename = filename;
}

// void FileManager::save();

// void FileManager::saveAs(std::string filename) {

// }

// void FileManager::close();

void FileManager::help() const {
    std::cout << "The following commands are supported: " << std::endl << std::endl;
    std::cout << "open <file>           opens <file>" << std::endl;
    std::cout << "close                 closes currently opened file" << std::endl;
    std::cout << "save                  saves the currently open file" << std::endl;
    std::cout << "saveas <file>         saves the currently open file in <file>" << std::endl;
    std::cout << "exit                  exists the program" << std::endl;
}