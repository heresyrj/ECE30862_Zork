#include <iostream>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "dungeon_objects/room.hpp"

using namespace std;
using namespace rapidxml;

//function to parse the given xml file
void parseXML(){
    string node_name;
    
    file<> xmlFile("sample.txt.xml");
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
    xml_node<> *node = doc.first_node("map");
    cout << "Node map has value " << node->value() << "\n";
    for (xml_node<> *sib = node->first_node();
         sib; sib = sib->next_sibling()){
        node_name = sib->name();
        if(node_name == "room"){
            cout<<"Node is a Room\n";
            xml_node<> *sub_node = sib->first_node(sib->name());
            if(sub_node == NULL){
                cout<<"NULL\n";
            }

        }
        else if(node_name == "item"){
            cout<<"Node is an Item\n";
        }
        else if(node_name == "Container"){
            cout<<"Node is a container\n";
        }
        else if(node_name == "Creature"){
            cout<<"Node is a creature\n";
        }
    }
    
}

//main function
int main(){
    parseXML();
    return EXIT_SUCCESS;
}