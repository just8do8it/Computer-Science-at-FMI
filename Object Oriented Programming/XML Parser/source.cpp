#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "textnode.h"
#include "complexnode.h"
#include "commandmanager.h"
#include "filemanager.h"

int main() {
    String filename;
    FileManager fm;

    std::cout << "Filename: ";
    std::cin >> filename;

    CommandManager *cm;

    fm.open(filename, cm);

    Vector<Pair<String, String>> attributes1;
    Vector<Pair<String, String>> attributes2;

    attributes2.add(Pair<String, String>("color", "green"));
    attributes2.add(Pair<String, String>("shape", "circle"));
    attributes1.add(Pair<String, String>("color", "green"));

    PVector<Node> nodes;
    PVector<Node> children;
    PVector<Node> parentNodes1;

    Node* node1 = new ComplexNode("0", "people", 0, &attributes1, &children);
    Node* node2 = new TextNode("1", "human", 1, &attributes2, &parentNodes1, "text");

    nodes.add(node1);
    nodes.add(node2);

    
    parentNodes1.copyWithSharedPointers(nodes);
    parentNodes1.set(0, nullptr);

    for (int i = 0; i < parentNodes1.getSize(); ++i) {
        if (parentNodes1[i] != nullptr)
            parentNodes1[i]->print();
        
        // std::cout << 
    }

    return 0;
}