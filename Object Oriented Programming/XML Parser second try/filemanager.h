#ifndef FILE_MANAGER_HH
#define FILE_MANAGER_HH
#include <fstream>
#include "commandmanager.h"
#include "node.h"

class FileManager {
	String currFilename;
public:
    FileManager() = default;

    const String& getCurrFilename() const;
    
	void open(String, CommandManager*);
    void save();
    void saveAs(String);
    void close();
    void help() const;
};

#endif