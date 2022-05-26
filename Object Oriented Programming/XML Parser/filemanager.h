#ifndef FILE_MANAGER_HH
#define FILE_MANAGER_HH
#include <fstream>
#include "node.h"

class FileManager {
	String filename;
public:
    FileManager() = default;

	void open(String);
    void save();
    void saveAs(String);
    void close();
    void help() const;
};

#endif