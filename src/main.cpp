#include <iostream>
#include <vector>
#include <string>
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

//function to parse the given xml file for containers
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

vector<Container> buildContainers(vector<Container> containers, vector<Item> items){
    vector<string> item_list, container_list;
    
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
    return containers;
}

//populates the rooms with their items, containers, and creatures
vector<Room> buildDungeon(vector<Room> rooms, vector<Item> items, vector<Container*> containers){
    vector<string> item_list, container_list, creature_list;
    
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
                if(container_list.at(j) == containers.at(k)->getName()){
                    rooms.at(i).addContainer(containers.at(k));
                }
            }
        }
    }
    
    return rooms;
}

//function that handles player commands
void getPlayerAction(Player *player, vector<Item> master_items, vector<Creature> master_creatures){
    string command;
    vector<Item> items;
    vector<Container*> containers;
    Item moved_item;
    getline(cin,command);

    if(command == "n"){
        if(player->getCurrentRoom()->getNorth() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getNorth());
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    
    else if(command == "e"){
        if(player->getCurrentRoom()->getEast() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getEast());
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    
    else if(command == "s"){
        if(player->getCurrentRoom()->getSouth() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getSouth());
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    
    else if(command == "w"){
        if(player->getCurrentRoom()->getWest() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getWest());
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
            cout<<"Inventory: "<<player->getInventory().at(0).getName();
            for(unsigned i = 1; i < player->getInventory().size(); i++){
                cout<<", "<<player->getInventory().at(i).getName();
            }
            cout<<"\n";
        }
    }
    
    else if(command.find("open") != string::npos){
        if(command.find("exit") != string::npos){
            if(player->getCurrentRoom()->getType() == "exit"){
                player->setExitFlag(1);
            }
        }
        else{
            containers = player->getCurrentRoom()->getContainer();
            for(unsigned i = 0; i < containers.size(); i++){
                if(command.find(containers.at(i)->getName()) != string::npos){
                    items = containers.at(i)->getItem();
                    containers.at(i)->setOpenFlag(1);
                    if(items.size() > 0){
                        cout<<containers.at(i)->getName()<<" contains "<<items.at(0).getName();
                        for(unsigned j = 1; j < items.size(); j++){
                            cout<<", "<<items.at(j).getName();
                        }
                        cout<<"\n";
                    }
                    else{
                        cout<<containers.at(i)->getName()<<" is empty.\n";
                    }
                }
                
            }
        }
    }
    
    else if(command.find("take") != string::npos){
        items = player->getCurrentRoom()->getItem();
        if(items.size() > 0){
            for(unsigned i = 0; i < items.size(); i++){
                if(command.find(items.at(i).getName()) != string::npos){
                    moved_item = player->getCurrentRoom()->remItem(items.at(i).getName());
                    player->addItem(moved_item);
                    cout<<"Item "<<moved_item.getName()<<" added to inventory.\n";
                    return;
                }
            }
        }
        if(player->getCurrentRoom()->getContainer().size() > 0){
            containers = player->getCurrentRoom()->getContainer();
            for(unsigned i = 0; i < containers.size(); i++){
                items = player->getCurrentRoom()->getContainer().at(i)->getItem();
                for(unsigned j = 0; j < items.size(); j++){
                    if(command.find(items.at(j).getName())!= string::npos
                       && containers.at(i)->getOpenFlag() > 0){
                        moved_item = player->getCurrentRoom()->getContainer().at(i)->remItem(items.at(j).getName());
                        player->addItem(moved_item);
                        cout<<"Item "<<moved_item.getName()<<" added to inventory.\n";
                        return;
                    }
                }
            }
        }
        cout<<"That item is not here.\n";
    }
    
    else if(command.find("drop") != string::npos){
        items = player->getInventory();
        for(unsigned i = 0; i < items.size(); i++){
            if(command.find(items.at(i).getName()) != string::npos){
                moved_item = player->remItem(items.at(i).getName());
                player->getCurrentRoom()->addItem(moved_item);
                cout<<moved_item.getName()<<" dropped.\n";
                return;
            }
        }
    }
    
    
    else if(command.find("read") != std::string::npos){
        for(unsigned i = 0; i < player->getInventory().size(); i++){
            if(command.find(player->getInventory().at(i).getName()) != string::npos){
                if(player->getInventory().at(i).getWriting() != "\0"){
                    cout<<player->getInventory().at(i).getWriting()<<"\n";
                    return;
                }
                else{
                    cout<<"Nothing written.\n";
                    return;
                }
            }
        }
        cout<<"That is not in your inventory.\n";
    }
    
    else if(command.find("put") != string::npos){
        for(unsigned i = 0; i < player->getInventory().size(); i++){
            if(command.find(player->getInventory().at(i).getName()) != string::npos){
                for(unsigned j = 0; i < player->getCurrentRoom()->getContainer().size(); j++){
                    if(command.find(player->getCurrentRoom()->getContainer().at(j)->getName()) != string::npos){
                        moved_item = player->remItem(player->getInventory().at(i).getName());
                        player->getCurrentRoom()->getContainer().at(j)->addItem(moved_item);
                        cout<<"Item "<<moved_item.getName()<<" moved to "<<player->getCurrentRoom()->getContainer().at(j)->getName()<<"\n";
                        return;
                    }
                }
            }
        }
        cout<<"That is not in your inventory.\n";
    }
    
    return;
}

//main function
int main(int argc, char **argv){
    vector<Room> rooms;
    vector<Item> items;
    vector<Container> containers;
    vector<Container*> cont_refs;
    vector<Creature> creatures;
    
    rooms = parseXMLRooms(argv[1]);
    items = parseXMLItems(argv[1]);
    containers = parseXMLContainers(argv[1]);
    for(unsigned i = 0; i < containers.size(); i++){
        cont_refs.push_back(&containers.at(i));
    }
    containers = buildContainers(containers, items);
    rooms = buildDungeon(rooms, items, cont_refs);
    
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
    
    cout<<player.getCurrentRoom()->getDescription()<<"\n";
    while(player.getExitFlag() == 0){
        getPlayerAction(&player, items, creatures);
    }
    cout<<"Game Over\n";
    
    return EXIT_SUCCESS;
}