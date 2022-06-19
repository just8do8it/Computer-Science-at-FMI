#ifndef FILE_MANAGER_HH
#define FILE_MANAGER_HH
#include "commandmanager.h"

class FileManager {
    static FileManager *instance;
	std::string currFilename;
    FileManager() = default;
public:
    FileManager(const FileManager&) = delete;
    FileManager(FileManager&&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    FileManager& operator=(FileManager&&) = delete;

    static FileManager* getInstance();
    void free();
    const std::string& getCurrFilename() const;

	CommandManager* open();
    void save();
    void saveAs(std::string);
    void close();
    void help() const;
};

#endif