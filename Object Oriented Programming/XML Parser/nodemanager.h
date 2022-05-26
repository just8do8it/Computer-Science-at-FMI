#ifndef NODE_MANAGER_HH
#define NODE_MANAGER_HH
#include <iostream>
#include "node.h"

class NodeManager {
    Node** events;
    size_t capacity;
    size_t size;

    void copyFrom(const NodeManager&);
    void free();
public:
    NodeManager();
    NodeManager(size_t);
    NodeManager(const NodeManager&);
    NodeManager& operator=(const NodeManager&);
    ~NodeManager();

    size_t getCapacity() const;
    size_t getSize() const;
    void resize();

    bool add(const Node* event);
};

#endif