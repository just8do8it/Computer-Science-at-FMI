#include "engine.h"

int main() {
    Engine *engine = Engine::getInstance();
    engine->run();
    engine->free();

    return 0;
}