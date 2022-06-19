#ifndef ENGINE_HH
#define ENGINE_HH

#include "textnode.h"
#include "complexnode.h"
#include "filemanager.h"

#include <string>

class Engine {
    static Engine *instance;
    Engine() = default;
public:
    Engine(const Engine& other) = delete;
	Engine(Engine&& other) = delete;
	Engine& operator=(const Engine& other) = delete;
	Engine& operator=(Engine&& other) = delete;

    void run();
	static Engine* getInstance();
	static void free();
};

#endif