#include <iostream>
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

    PVector<Node> children;
    PVector<Node> parents;
    Vector<Pair<String, String>> attributes1;
    Vector<Pair<String, String>> attributes2;

    Node* node1 = new ComplexNode("0", "people", 0, &attributes1, &children);
    Node* node2 = new TextNode("1", "human", 1, &attributes2, &parents, "text");

    parents.add(node1);
    children.add(node2);
    attributes2.add(Pair<String, String>("color", "green"));

    PVector<Node> nodes;
    nodes.add(node2);
    nodes.add(node1);

    for (int i = 0; i < nodes.getSize(); ++i) {
        if (nodes[i]->getLevel() == 0)
            nodes[i]->print();
    }

    return 0;
}