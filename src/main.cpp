#include <iostream>
#include <vector>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "dungeon_objects/player.hpp"

using namespace std;
using namespace rapidxml;

Room parseRoom(xml_node<> *room_node){
    string sub_node;
    Room new_room;
    
    for(xml_node<> *pNode = room_node->first_node(); pNode; pNode = pNode->next_sibling()){
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

Item parseItem(xml_node<> *item_node){
    string sub_node;
    Item new_item;
    
    for(xml_node<> *pNode = item_node->first_node(); pNode; pNode = pNode->next_sibling()){
        sub_node = pNode->name();
        if(sub_node == "name"){new_item.setName(pNode->value());}
        else if(sub_node == "writing"){new_item.setWriting(pNode->value());}
        else if(sub_node == "description"){new_item.setDescription(pNode->value());}
        else if(sub_node == "status"){new_item.setStatus(pNode->value());}
        else if(sub_node == "turnon"){new_item.setTurnOn(pNode->value());}
    }
    return new_item;
}

Container parseContainer(xml_node<> *container_node){
    string sub_node;
    Container new_container;
    
    for(xml_node<> *pNode = container_node->first_node(); pNode; pNode = pNode->next_sibling()){
        sub_node = pNode->name();
        if(sub_node == "name"){new_container.setName(pNode->value());}
        else if(sub_node == "description"){new_container.setDescription(pNode->value());}
        else if(sub_node == "status"){new_container.setStatus(pNode->value());}
        else if(sub_node == "accept"){new_container.setAccept(pNode->value());}
        else if(sub_node == "item"){new_container.addItemList(pNode->value());}
    }
    return new_container;
}

//function to parse the given xml file for rooms
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

//function to parse the given xml file for items
vector<Item> parseXMLItems(char *filename){
    string node_name, sub_node_name;
    vector<Item> items;
    
    file<> xmlFile(filename);
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *node = doc.first_node("map");
    for(xml_node<> *sib = node->first_node(); sib; sib = sib->next_sibling()){
        node_name = sib->name();
        if(node_name == "item"){
            Item new_item = parseItem(sib);
            items.push_back(new_item);
        }
    }   
    return items;
}

vector<Container> parseXMLContainers(char *filename){
    string node_name, sub_node_name;
    vector<Container> containers;
    
    file<> xmlFile(filename);
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *node = doc.first_node("map");
    for(xml_node<> *sib = node->first_node(); sib; sib = sib->next_sibling()){
        node_name = sib->name();
        if(node_name == "container"){
            Container new_container = parseContainer(sib);
            containers.push_back(new_container);
        }
    }   
    return containers;
}
vector<Room> buildDungeon(vector<Room> rooms, vector<Item> items, vector<Container> containers){
    vector<string> item_list, container_list, creature_list;
    
    //populates the containers with their items
    for(unsigned i = 0; i < containers.size(); i++){
        item_list = containers.at(i).getItemList();
        for(unsigned j = 0; j < item_list.size(); j++){
            for(unsigned k = 0; k < items.size(); k++){
                if(item_list.at(j) == items.at(k).getName()){
                    containers.at(i).addItem(items.at(k));
                }
            }
        }
    }
    //populates the rooms with their appropriate items, containers, and creatures
    for(unsigned i = 0; i < rooms.size(); i++){
        item_list = rooms.at(i).getItemList();
        container_list = rooms.at(i).getContainerList();
        //items
        for(unsigned j = 0; j < item_list.size(); j++){
            for(unsigned k = 0; k < items.size(); k++){
                if(item_list.at(j) == items.at(k).getName()){
                    rooms.at(i).addItem(items.at(k));
                }
            }
        }
        //containers
        for(unsigned j = 0; j < container_list.size(); j++){
            for(unsigned k = 0; k < containers.size(); k++){
                if(container_list.at(j) == containers.at(k).getName()){
                    rooms.at(i).addContainer(containers.at(k));
                }
            }
        }
    }
    
    return rooms;
}

void getPlayerAction(Player *player){
    string command;
    cin>>command;
    
    if(command == "n"){
        if(player->getCurrentRoom()->getNorth() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getNorth());
            //cout<<player->getCurrentRoom()->getName()<<"\n";
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    else if(command == "e"){
        if(player->getCurrentRoom()->getEast() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getEast());
            //cout<<player->getCurrentRoom()->getName()<<"\n";
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    else if(command == "s"){
        if(player->getCurrentRoom()->getSouth() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getSouth());
            //cout<<player->getCurrentRoom()->getName()<<"\n";
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    else if(command == "w"){
        if(player->getCurrentRoom()->getWest() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getWest());
            //cout<<player->getCurrentRoom()->getName()<<"\n";
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    else if(command == "i"){
        if(player->getInventory().size() == 0){
            cout<<"Inventory: empty\n";
        }
        else{
            cout<<"Inventory: "<<player->getInventory().at(1).getName();
            for(unsigned i = 1; i < player->getInventory().size()-1; i++){
                cout<<", "<<player->getInventory().at(i).getName();
            }
            cout<<"\n";
        }
    }
    return;
}

//main function
int main(int argc, char **argv){
    vector<Room> rooms;
    vector<Item> items;
    vector<Container> containers;
    vector<Creature> creatures;
    
    rooms = parseXMLRooms(argv[1]);
    items = parseXMLItems(argv[1]);
    containers = parseXMLContainers(argv[1]);
    rooms = buildDungeon(rooms, items, containers);
    
    //conncects the rooms together
    for(unsigned i = 0; i < rooms.size(); i++){
        vector<Border> borders = rooms.at(i).getBorder();
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
    
    Player player(&rooms.at(0));
    
    cout<<player.getCurrentRoom()->getName()<<"\n";
    cout<<player.getCurrentRoom()->getDescription()<<"\n";
    if(player.getCurrentRoom()->getItem().size() > 0){
        cout<<player.getCurrentRoom()->getItem().at(0).getName()<<"\n";
    }
    
    while(player.getCurrentRoom()->getType() != "exit"){
        getPlayerAction(&player);
        if(player.getCurrentRoom()->getItem().size() > 0){
            cout<<player.getCurrentRoom()->getItem().at(0).getName()<<"\n";
        }
        if(player.getCurrentRoom()->getContainer().size() > 0){
            cout<<player.getCurrentRoom()->getContainer().at(0).getName()<<"\n";
            if(player.getCurrentRoom()->getContainer().at(0).getItemList().size() > 0){
                cout<<player.getCurrentRoom()->getContainer().at(0).getItemList().at(0)<<"\n";
            }
        }
    }
    
    return EXIT_SUCCESS;
}