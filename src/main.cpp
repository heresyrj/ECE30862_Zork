#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "room.hpp"

using namespace std;
using namespace rapidxml;

void parseXML(){
    file<> xmlFile("sample.txt.xml");
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
    rapidxml::xml_node<> *node = doc.first_node("map");
    cout << "Node map has value " << node->value() << "\n";
}

int main(){
    parseXML();
    return EXIT_SUCCESS;
}