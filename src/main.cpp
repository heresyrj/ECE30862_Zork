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
        //cout<<pNode->name()<<"\n";
        sub_node = pNode->name();
        if(sub_node == "name"){new_room.setName(pNode->value());}
        else if(sub_node == "status"){new_room.setStatus(pNode->value());}
        else if(sub_node == "type"){new_room.setType(pNode->value());}
        else if(sub_node == "description"){new_room.setDescription(pNode->value());}
        else if(sub_node == "item"){new_room.addItemList(pNode->value());}
        else if(sub_node == "container"){new_room.addContainerList(pNode->value());}
        else if(sub_node == "creature"){new_room.addCreatureList(pNode->value());}
        else if(sub_node == "border"){
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
vector<Room> parseXMLRooms(char *filename){
    string node_name;
    string sub_node_name;
    vector<Room> rooms;

    file<> xmlFile(filename);
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *node = doc.first_node("map");
    for(xml_node<> *sib = node->first_node(); sib; sib = sib->next_sibling()){
        node_name = sib->name();
        if(node_name == "room"){
            Room new_room = parseRoom(sib);
            rooms.push_back(new_room);
        }
    }
    
    return rooms;
}

vector<Room> buildDungeon(vector<Room> rooms){
    vector<Border> borders;
    
    for(unsigned i = 0; i < rooms.size(); i++){
        borders = rooms.at(i).getBorder();
        for(unsigned j = 0; j < borders.size(); j++){
            for(unsigned k = 0; k < rooms.size(); k++){
                if(borders.at(j).getName() == rooms.at(k).getName()){
                    if(borders.at(j).getDirection() == "north"){
                        rooms.at(i).setNorth(&rooms.at(k));
                    }
                    else if(borders.at(j).getDirection() == "east"){
                        rooms.at(i).setEast(&rooms.at(k));
                    }
                    else if(borders.at(j).getDirection() == "south"){
                        rooms.at(i).setSouth(&rooms.at(k));
                    }
                    else if(borders.at(j).getDirection() == "west"){
                        rooms.at(i).setWest(&rooms.at(k));
                    }
                }
            }
        }
    }
    return rooms;
}

//main function
int main(int argc, char **argv){
    vector<Room> rooms;
    Room *current_room;
    
    rooms = parseXMLRooms(argv[1]);
    rooms = buildDungeon(rooms);
    current_room = &rooms.at(0);
    while(current_room != NULL){
        cout<<current_room->getName()<<"\n";
        cout<<current_room->getDescription()<<"\n";
        current_room = current_room->getNorth();
    }
    
    return EXIT_SUCCESS;
}

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