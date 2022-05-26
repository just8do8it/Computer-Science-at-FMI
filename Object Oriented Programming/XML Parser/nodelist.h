#ifndef NODE_LIST_HH
#define NODE_LIST_HH
#include <iostream>
#include "node.h"

class NodeList {
    Node** nodes;
    size_t capacity;
    size_t size;

    void copyFrom(const NodeList&);
    void free();
public:
    NodeList();
    NodeList(size_t);
    NodeList(const NodeList&);
    NodeList& operator=(const NodeList&);
    ~NodeList();

    size_t getCapacity() const;
    size_t getSize() const;
    void resize();

    void add(const Node*);
};

#endif