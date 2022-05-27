#include "filemanager.h"

const String& FileManager::getCurrFilename() const {
    return this->currFilename;
}

void FileManager::open(String currFilename, CommandManager* cm) {
    this->currFilename = currFilename;
    std::fstream file(this->currFilename.getData());

    if (file.fail()) {
        throw "Can't open the file!";
    }


    cm = new CommandManager(file);
}

// void FileManager::save();

// void FileManager::saveAs(String filename) {

// }

// void FileManager::close();

void FileManager::help() const {
    std::cout << "The following commands are supported: " << std::endl;
    std::cout << "open <file>           opens <file>" << std::endl;
    std::cout << "close                 closes currently opened file" << std::endl;
    std::cout << "save                  saves the currently open file" << std::endl;
    std::cout << "saveas <file>         saves the currently open file in <file>" << std::endl;
    std::cout << "exit                  exists the program" << std::endl;
}