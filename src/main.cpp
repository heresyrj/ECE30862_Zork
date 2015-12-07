#include <iostream>
#include <vector>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "dungeon_objects/room.hpp"

using namespace std;
using namespace rapidxml;

Room parseRoom(xml_node<> *room_node){
    string sub_node;
    Room new_room;
    
    for(xml_node<> *pNode = room_node->first_node(); pNode; pNode = pNode->next_sibling()){
        cout<<pNode->name()<<"\n";
        sub_node = pNode->name();
        if(sub_node == "border"){
            Border border;
            sub_node = pNode->first_node()->name();
            if(sub_node == "direction"){
            border.setDirection(pNode->first_node()->value());
            border.setName(pNode->last_node()->value());
            }
            else{
                border.setName(pNode->first_node()->value());
                border.setDirection(pNode->last_node()->value());
            }
            new_room.addBorder(border);
        }
    }
    return new_room;
}

//function to parse the given xml file
void parseXML(){
    string node_name;
    string sub_node_name;
    vector<Room> rooms;
    vector<Border> borders;
    
    file<> xmlFile("sample.txt.xml");
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
    xml_node<> *node = doc.first_node("map");
    for(xml_node<> *sib = node->first_node(); sib; sib = sib->next_sibling()){
        node_name = sib->name();
        if(node_name == "room"){
            /*
            cout<<"Node is a Room\n";
            for(xml_node<> *pNode = sib->first_node(); pNode; pNode = pNode->next_sibling()){
                cout<<pNode->name()<<"\n";
                sub_node_name = pNode->name();
                if(sub_node_name == "border"){
                    Border border;
                    border.setDirection(pNode->first_node()->value());
                    border.setName(pNode->last_node()->value());
                    borders.push_back(border);
                }
            }
            */
            Room new_room = parseRoom(sib);
            rooms.push_back(new_room);
        }
        else if(node_name == "item"){
            cout<<"Node is an Item\n";
        }
        else if(node_name == "container"){
            cout<<"Node is a Container\n";
        }
        else if(node_name == "creature"){
            cout<<"Node is a Creature\n";
        }
    }
    
    borders = rooms[1].getBorder();
    for(int i = 0; i < borders.size(); i++){
        cout<<borders[i].getName()<<"\n";
        cout<<borders[i].getDirection()<<"\n";
    }
}

//main function
int main(){
    parseXML();
    return EXIT_SUCCESS;
}