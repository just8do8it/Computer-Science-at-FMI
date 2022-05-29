#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "textnode.h"
#include "commandmanager.h"
#include "filemanager.h"

int main() {
    String filename;
    FileManager fm;

    std::cout << "Filename: ";
    std::cin >> filename;

    CommandManager *cm;

    fm.open(filename, cm);

    Vector<Pair<String, Node*>> nodes;
    String id1("1");
    String id2("2");
    // String id3("3");

    Vector<Pair<String, String>> attributes1;
    Vector<Pair<String, String>> attributes2;

    attributes1.add(Pair<String, String>("color", "blue"));
    attributes1.add(Pair<String, String>("address", "Sofia"));
    attributes2.add(Pair<String, String>("color", "yellow"));
    
    Node* node1 = new Node("people", id1, 0, &attributes1, nullptr);
    Node* node2 = new Node("people", id2, 1, &attributes2, node1);
    nodes.add(Pair<String, Node*>(id1, node1));
    nodes.add(Pair<String, Node*>(id2, node2));

    for (int i = 0; i < nodes.getSize(); ++i) {
        if (nodes[i].getValue()->getParent() != nullptr && 
            nodes[i].getValue()->getParent()->getId() == id1) {
            nodes[i].getValue()->getParent()->print();
        }
    }

    return 0;
}