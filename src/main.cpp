#include <iostream>
#include <vector>
#include <string>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "dungeon_objects/player.hpp"

using namespace std;
using namespace rapidxml;

vector<Item> master_items;
vector<Creature> master_creatures;

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
        else if(sub_node == "trigger"){
            Trigger trigger;
            trigger.setLive(1);
            for(xml_node<> *tri_node = pNode->first_node(); tri_node; tri_node = tri_node->next_sibling()){
                sub_node = tri_node->name();
                if(sub_node == "print"){trigger.setText(tri_node->value());}
                else if(sub_node == "action"){trigger.addAction(tri_node->value());}
                else if(sub_node == "type"){trigger.setType(tri_node->value());}
                else if(sub_node == "command"){trigger.setCommand(tri_node->value());}
                else if(sub_node == "condition"){
                    for(xml_node<> *cond = tri_node->first_node(); cond; cond = cond->next_sibling()){
                        sub_node = cond->name();
                        if(sub_node == "object"){trigger.setObject(cond->value());}
                        else if(sub_node == "status"){trigger.setStatus(cond->value());}
                        else if(sub_node == "owner"){trigger.setOwner(cond->value());}
                        else if(sub_node == "has"){trigger.setHas(cond->value());}
                    }
                }
            }
            new_room.setTrigger(trigger);
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
        else if(sub_node == "turnon"){
            for(xml_node<> *turn_node = pNode->first_node(); turn_node; turn_node = turn_node->next_sibling()){
                sub_node = turn_node->name();
                if(sub_node == "print"){
                    new_item.setTurnOnText(turn_node->value());
                }
                else if(sub_node == "action"){
                    new_item.addTurnOnAction(turn_node->value());
                }
            }
        }
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
        if(sub_node == "trigger"){
            Trigger trigger;
            trigger.setLive(1);
            for(xml_node<> *tri_node = pNode->first_node(); tri_node; tri_node = tri_node->next_sibling()){
                sub_node = tri_node->name();
                if(sub_node == "print"){trigger.setText(tri_node->value());}
                else if(sub_node == "action"){trigger.addAction(tri_node->value());}
                else if(sub_node == "type"){trigger.setType(tri_node->value());}
                else if(sub_node == "command"){trigger.setCommand(tri_node->value());}
                else if(sub_node == "condition"){
                    for(xml_node<> *cond = tri_node->first_node(); cond; cond = cond->next_sibling()){
                        sub_node = cond->name();
                        if(sub_node == "object"){trigger.setObject(cond->value());}
                        else if(sub_node == "status"){trigger.setStatus(cond->value());}
                        else if(sub_node == "owner"){trigger.setOwner(cond->value());}
                        else if(sub_node == "has"){trigger.setHas(cond->value());}
                    }
                }
            }
            new_container.setTrigger(trigger);
        }
    }
    return new_container;
}

Creature parseCreature(xml_node<> *creature_node){
    string sub_node;
    Creature new_creature;
    
    for(xml_node<> *pNode = creature_node->first_node(); pNode; pNode = pNode ->next_sibling()){
        sub_node = pNode->name();
        if(sub_node == "name"){new_creature.setName(pNode->value());}
        else if(sub_node == "status"){new_creature.setStatus(pNode->value());}
        else if(sub_node == "description"){new_creature.setDescription(pNode->value());}
        else if(sub_node == "vulnerability"){new_creature.addVulnerability(pNode->value());}
        if(sub_node == "attack"){
            for(xml_node<> *att_node = pNode->first_node(); att_node; att_node = att_node->next_sibling()){
                sub_node = att_node->name();
                if(sub_node == "print"){new_creature.setAttackText(att_node->value());}
                if(sub_node == "action"){new_creature.addAttackAction(att_node->value());}
                if(sub_node == "condition"){
                    for(xml_node<> *cond = att_node->first_node(); cond; cond = cond->next_sibling()){
                        sub_node = cond->name();
                        if(sub_node == "object"){new_creature.setCondObject(cond->value());}
                        else if(sub_node == "status"){new_creature.setCondStatus(cond->value());}
                    }
                }
            }
        }
        if(sub_node == "trigger"){
            Trigger trigger;
            trigger.setLive(1);
            for(xml_node<> *tri_node = pNode->first_node(); tri_node; tri_node = tri_node->next_sibling()){
                sub_node = tri_node->name();
                if(sub_node == "print"){trigger.setText(tri_node->value());}
                else if(sub_node == "action"){trigger.addAction(tri_node->value());}
                else if(sub_node == "type"){trigger.setType(tri_node->value());}
                else if(sub_node == "command"){trigger.setCommand(tri_node->value());}
                else if(sub_node == "condition"){
                    for(xml_node<> *cond = tri_node->first_node(); cond; cond = cond->next_sibling()){
                        sub_node = cond->name();
                        if(sub_node == "object"){trigger.setObject(cond->value());}
                        else if(sub_node == "status"){trigger.setStatus(cond->value());}
                        else if(sub_node == "owner"){trigger.setOwner(cond->value());}
                        else if(sub_node == "has"){trigger.setHas(cond->value());}
                    }
                }
            }
            new_creature.setTrigger(trigger);
        }
    }
    return new_creature;
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
    string node_name;
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
    string node_name;
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

//parse the xml document for creatures
vector<Creature> parseXMLCreatures(char *filename){
    string node_name;
    vector<Creature> creatures;
    
    file<> xmlFile(filename);
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *node = doc.first_node("map");
    for(xml_node<> *sib = node->first_node(); sib; sib = sib->next_sibling()){
        node_name = sib->name();
        if(node_name == "creature"){
            Creature new_creature = parseCreature(sib);
            creatures.push_back(new_creature);
        }
    }   
    return creatures;
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
vector<Room> buildDungeon(vector<Room> rooms, vector<Item> items, vector<Container*> containers, vector<Creature*> creatures){
    vector<string> item_list, container_list, creature_list;
    
    //populates the rooms with their appropriate items, containers, and creatures
    for(unsigned i = 0; i < rooms.size(); i++){
        item_list = rooms.at(i).getItemList();
        container_list = rooms.at(i).getContainerList();
        creature_list = rooms.at(i).getCreatureList();
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
        //creatures
        for(unsigned j = 0; j < creature_list.size(); j++){
            for(unsigned k = 0; k < creatures.size(); k++){
                if(creature_list.at(j) == creatures.at(k)->getName()){
                    rooms.at(i).addCreature(creatures.at(k));
                }
            }
        }
    }
    
    return rooms;
}

//function that handles internal commands
void interiorCommand(string command, Player *player, Room *currentRoom){

    if(command.find("update") != string::npos || command.find("Update") != string::npos){
        size_t found = command.find_last_of(" ");
        for(unsigned i = 0; i < player->getInventory().size(); i++){
            if(command.find(player->getInventory().at(i).getName()) != string::npos){
                Item temp_item = player->remItem(player->getInventory().at(i).getName());
                temp_item.setStatus(command.substr(found+1));
                player->addItem(temp_item);
                return;
            }
        }
        for(unsigned i = 0; i < player->getCurrentRoom()->getContainer().size(); i++){
            if(command.find(player->getCurrentRoom()->getContainer().at(i)->getName()) != string::npos){
                player->getCurrentRoom()->getContainer().at(i)->setStatus(command.substr(found+1));
                return;
            }
            else{
                for(unsigned j = 0; j < player->getCurrentRoom()->getContainer().at(i)->getItem().size(); j++){
                    if(command.find(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getName()) != string::npos){
                        Item temp_item = player->getCurrentRoom()->getContainer().at(i)->remItem(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getName());
                        temp_item.setStatus(command.substr(found+1));
                        player->getCurrentRoom()->getContainer().at(i)->addItem(temp_item);
                        return;
                    }
                }
            }
        }
        return;
    }
    
    else if(command.find("add") != string::npos || command.find("Add") != string::npos){
        for(unsigned i = 0; i < master_items.size(); i++){
            if(command.find(master_items.at(i).getName()) != string::npos){
                player->getCurrentRoom()->addItem(master_items.at(i));
                return;
            }
        }
        for(unsigned i = 0; i < master_creatures.size(); i++){
            if(command.find(master_creatures.at(i).getName()) != string::npos){
                player->getCurrentRoom()->addCreature(&master_creatures.at(i));
                return;
            }
        }
        return;
    }
    
    else if(command.find("delete") != string::npos || command.find("Delete") != string::npos){
        for(unsigned i = 0; i < currentRoom->getItem().size(); i++){
            if(command.find(currentRoom->getItem().at(i).getName()) != string::npos){
                currentRoom->delItem(currentRoom->getItem().at(i).getName());
                return;
            }
        }
        for(unsigned i = 0; i < currentRoom->getCreature().size(); i++){
            if(command.find(currentRoom->getCreature().at(i)->getName()) != string::npos){
                currentRoom->delCreature(currentRoom->getCreature().at(i)->getName());
                return;
            }
        }
    }
    
    else if(command.find("drop") != string::npos || command.find("Drop") != string::npos){
        for(unsigned i = 0; i < player->getInventory().size(); i++){
            if(command.find(player->getInventory().at(i).getName()) != string::npos){
                Item temp_item = player->remItem(player->getInventory().at(i).getName());
                player->getCurrentRoom()->addItem(temp_item);
                return;
            }
        }
    }
    
    else if(command.find("Game Over") != string::npos){
        player->setExitFlag(1);
    }
    
    else if(command == "n"){
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
    
    return;
}

//function to check triggers
int checkTriggers(Player *player, Trigger *trigger, string command){
    Room *currentRoom = player->getCurrentRoom();
    if(trigger->getTriggerFlag() == 1){return 0;}
    
    else if(trigger->getCommand() != "\0"){//trigger has a specific command
        if(command == trigger->getCommand()){
            if(trigger->getHas() != "\0"){
                if(trigger->getHas() == "yes"){
                    if(trigger->getOwner() == "inventory"){
                        for(unsigned i = 0; i < player->getInventory().size(); i++){
                            if(player->getInventory().at(i).getName() == trigger->getObject()){
                                cout<<trigger->getText()<<"\n";
                                for(unsigned j = 0; j < trigger->getAction().size(); j++){
                                    interiorCommand(trigger->getAction().at(j), player, currentRoom);
                                }
                                if(trigger->getType() != "permanent"){
                                    trigger->setTriggerFlag(1);
                                }
                                return 1;
                            }
                        }
                        return 0;
                    }
                    else{
                        for(unsigned i = 0; i < player->getCurrentRoom()->getContainer().size(); i++){
                            if(player->getCurrentRoom()->getContainer().at(i)->getName() == trigger->getOwner()){
                                for(unsigned j = 0; j < player->getCurrentRoom()->getContainer().at(i)->getItem().size(); j++){
                                    if(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getName() == trigger->getObject()){
                                        cout<<trigger->getText()<<"\n";
                                        for(unsigned k = 0; k < trigger->getAction().size(); k++){
                                            interiorCommand(trigger->getAction().at(k), player, currentRoom);
                                        }
                                        if(trigger->getType() != "permanent"){
                                            trigger->setTriggerFlag(1);
                                        }
                                        return 1;
                                    }
                                }
                                return 0;
                            }
                        }
                    }
                }
                else if(trigger->getHas() == "no"){
                    if(trigger->getOwner() == "inventory"){
                        for(unsigned i = 0; i < player->getInventory().size(); i++){
                            if(player->getInventory().at(i).getName() == trigger->getObject()){return 0;}
                        }
                        cout<<trigger->getText()<<"\n";
                        for(unsigned j = 0; j < trigger->getAction().size(); j++){
                            interiorCommand(trigger->getAction().at(j), player, currentRoom);
                        }
                        if(trigger->getType() != "permanent"){
                            trigger->setTriggerFlag(1);
                        }
                        return 1;
                    }
                    else{
                        for(unsigned i = 0; i < player->getCurrentRoom()->getContainer().size(); i++){
                            if(player->getCurrentRoom()->getContainer().at(i)->getName() == trigger->getOwner()){
                                for(unsigned j = 0; j < player->getCurrentRoom()->getContainer().at(i)->getItem().size(); j++){
                                    if(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getName() == trigger->getObject()){return 0;}
                                }
                                cout<<trigger->getText()<<"\n";
                                for(unsigned j = 0; j < trigger->getAction().size(); j++){
                                    interiorCommand(trigger->getAction().at(j), player, currentRoom);
                                }
                                if(trigger->getType() != "permanent"){
                                    trigger->setTriggerFlag(1);
                                }
                                return 1;
                            }
                        }
                    }         
                }
                return 0;
            }
            else{//trigger is an object status condition
                for(unsigned i = 0; i < player->getInventory().size(); i++){
                    if(player->getInventory().at(i).getName() == trigger->getObject()){
                        if(player->getInventory().at(i).getStatus() == trigger->getStatus()){
                            cout<<trigger->getText()<<"\n";
                            for(unsigned j = 0; j < trigger->getAction().size(); j++){
                                interiorCommand(trigger->getAction().at(j), player, currentRoom);
                            }
                            if(trigger->getType() != "permanent"){
                                trigger->setTriggerFlag(1);
                            }
                            return 1;
                        }
                        return 0;
                    }
                }
                for(unsigned i = 0; i < player->getCurrentRoom()->getContainer().size(); i++){
                    if(player->getCurrentRoom()->getContainer().at(i)->getName() == trigger->getObject()){
                        if(player->getCurrentRoom()->getContainer().at(i)->getStatus() == trigger->getStatus()){
                            cout<<trigger->getText()<<"\n";
                            for(unsigned j = 0; j < trigger->getAction().size(); j++){
                                interiorCommand(trigger->getAction().at(j), player, currentRoom);
                            }
                            if(trigger->getType() != "permanent"){
                                trigger->setTriggerFlag(1);
                            }
                            return 1;
                        }
                        return 0;
                    }
                    else{
                        for(unsigned j = 0; j < player->getCurrentRoom()->getContainer().at(i)->getItem().size(); j++){
                            if(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getName() == trigger->getObject()){
                                if(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getStatus() == trigger->getStatus()){
                                    cout<<trigger->getText()<<"\n";
                                    for(unsigned k = 0; k < trigger->getAction().size(); k++){
                                        interiorCommand(trigger->getAction().at(k), player, currentRoom);
                                    }
                                    if(trigger->getType() != "permanent"){
                                        trigger->setTriggerFlag(1);
                                    }
                                    return 1;
                                }
                                return 0;
                            }
                        }
                    }
                }
                return 0;
            }
        }
        else{return 0;}
    }
    else{//trigger has no command
        if(trigger->getHas() != "\0"){ //trigger is object has/not have condition
            if(trigger->getHas() == "yes"){
                if(trigger->getOwner() == "inventory"){
                    for(unsigned i = 0; i < player->getInventory().size(); i++){
                        if(player->getInventory().at(i).getName() == trigger->getObject()){
                            cout<<trigger->getText()<<"\n";
                            for(unsigned j = 0; j < trigger->getAction().size(); j++){
                                interiorCommand(trigger->getAction().at(j), player, currentRoom);
                            }
                            if(trigger->getType() != "permanent"){
                                trigger->setTriggerFlag(1);
                            }
                            return 1;
                        }
                    }
                    return 0;
                }
                else{
                    for(unsigned i = 0; i < player->getCurrentRoom()->getContainer().size(); i++){
                        if(player->getCurrentRoom()->getContainer().at(i)->getName() == trigger->getOwner()){
                            for(unsigned j = 0; j < player->getCurrentRoom()->getContainer().at(i)->getItem().size(); j++){
                                if(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getName() == trigger->getObject()){
                                    cout<<trigger->getText()<<"\n";
                                    for(unsigned k = 0; k < trigger->getAction().size(); k++){
                                        interiorCommand(trigger->getAction().at(k), player, currentRoom);
                                    }
                                    if(trigger->getType() != "permanent"){
                                        trigger->setTriggerFlag(1);
                                    }
                                    return 1;
                                }
                            }
                            return 0;
                        }
                    }
                }
            }
            else if(trigger->getHas() == "no"){
                if(trigger->getOwner() == "inventory"){
                    for(unsigned i = 0; i < player->getInventory().size(); i++){
                        if(player->getInventory().at(i).getName() == trigger->getObject()){return 0;}
                    }
                    cout<<trigger->getText()<<"\n";
                    for(unsigned j = 0; j < trigger->getAction().size(); j++){
                        interiorCommand(trigger->getAction().at(j), player, currentRoom);
                    }
                    if(trigger->getType() != "permanent"){
                        trigger->setTriggerFlag(1);
                    }
                    return 1;
                }
                else{
                    for(unsigned i = 0; i < player->getCurrentRoom()->getContainer().size(); i++){
                        if(player->getCurrentRoom()->getContainer().at(i)->getName() == trigger->getOwner()){
                            for(unsigned j = 0; j < player->getCurrentRoom()->getContainer().at(i)->getItem().size(); j++){
                                if(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getName() == trigger->getObject()){return 0;}
                            }
                            cout<<trigger->getText()<<"\n";
                            for(unsigned j = 0; j < trigger->getAction().size(); j++){
                                interiorCommand(trigger->getAction().at(j), player, currentRoom);
                            }
                            if(trigger->getType() != "permanent"){
                                trigger->setTriggerFlag(1);
                            }
                            return 1;
                        }
                    }
                }         
            }
        }
        else{//trigger is object status condition
            for(unsigned i = 0; i < player->getInventory().size(); i++){
                if(player->getInventory().at(i).getName() == trigger->getObject()){
                    if(player->getInventory().at(i).getStatus() == trigger->getStatus()){
                        cout<<trigger->getText()<<"\n";
                        for(unsigned j = 0; j < trigger->getAction().size(); j++){
                            interiorCommand(trigger->getAction().at(j), player, currentRoom);
                        }
                        if(trigger->getType() != "permanent"){
                            trigger->setTriggerFlag(1);
                        }
                        return 1;
                    }
                    return 0;
                }
            }
            for(unsigned i = 0; i < player->getCurrentRoom()->getContainer().size(); i++){
                if(player->getCurrentRoom()->getContainer().at(i)->getName() == trigger->getObject()){
                    if(player->getCurrentRoom()->getContainer().at(i)->getStatus() == trigger->getStatus()){
                        cout<<trigger->getText()<<"\n";
                        if(trigger->getType() != "permanent"){
                            trigger->setTriggerFlag(1);
                        }
                        for(unsigned j = 0; j < trigger->getAction().size(); j++){
                            interiorCommand(trigger->getAction().at(j), player, currentRoom);
                        }
                        return 1;
                    }
                    return 0;
                }
                else{
                    for(unsigned j = 0; j < player->getCurrentRoom()->getContainer().at(i)->getItem().size(); j++){
                        if(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getName() == trigger->getObject()){
                            if(player->getCurrentRoom()->getContainer().at(i)->getItem().at(j).getStatus() == trigger->getStatus()){
                                cout<<trigger->getText()<<"\n";
                                for(unsigned k = 0; k < trigger->getAction().size(); k++){
                                    interiorCommand(trigger->getAction().at(k), player, currentRoom);
                                }
                                if(trigger->getType() != "permanent"){
                                    trigger->setTriggerFlag(1);
                                }
                                return 1;
                            }
                            return 0;
                        }
                    }
                }
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

//function that handles player commands
void getPlayerAction(Player *player){
    string command;
    vector<Item> items;
    vector<Container*> containers;
    Item moved_item;
    getline(cin,command);
    int trig1 = 0, trig2 = 0, trig3 = 0;
    Room* currentRoom = player->getCurrentRoom();
    
    Trigger temp_trigger = player->getCurrentRoom()->getTrigger();
    trig1 = checkTriggers(player, &temp_trigger, command);
    player->getCurrentRoom()->setTrigger(temp_trigger);
    
    for(unsigned i = 0; i < currentRoom->getCreature().size(); i++){
        temp_trigger = currentRoom->getCreature().at(i)->getTrigger();
        trig2 = checkTriggers(player, &temp_trigger, command);
        currentRoom->getCreature().at(i)->setTrigger(temp_trigger);
        
    }
    
    for(unsigned i = 0; i < currentRoom->getContainer().size(); i++){
        temp_trigger = currentRoom->getContainer().at(i)->getTrigger();
        trig3 = checkTriggers(player, &temp_trigger, command);
        currentRoom->getContainer().at(i)->setTrigger(temp_trigger);
        
    }

    if(command == "n"){
        if(trig1 == 1 || trig2 == 1 || trig3 == 1){return;}
        if(player->getCurrentRoom()->getNorth() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getNorth());
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    
    else if(command == "e"){
        if(trig1 == 1 || trig2 == 1 || trig3 == 1){return;}
        if(player->getCurrentRoom()->getEast() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getEast());
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    
    else if(command == "s"){
        if(trig1 == 1 || trig2 == 1 || trig3 == 1){return;}
        if(player->getCurrentRoom()->getSouth() != NULL){
            player->setCurrentRoom(player->getCurrentRoom()->getSouth());
            cout<<player->getCurrentRoom()->getDescription()<<"\n";
        }
        else{
            cout<<"Can't go that way.\n";
        }
    }
    
    else if(command == "w"){
        if(trig1 == 1 || trig2 == 1 || trig3 == 1){return;}
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
                for(unsigned j = 0; j < player->getCurrentRoom()->getContainer().size(); j++){
                    if(command.find(player->getCurrentRoom()->getContainer().at(j)->getName()) != string::npos){
                        if(player->getCurrentRoom()->getContainer().at(j)->getAccept() == "\0"
                        && player->getCurrentRoom()->getContainer().at(j)->getOpenFlag() > 0){
                            moved_item = player->remItem(player->getInventory().at(i).getName());
                            player->getCurrentRoom()->getContainer().at(j)->addItem(moved_item);
                            cout<<"Item "<<moved_item.getName()<<" moved to "<<player->getCurrentRoom()->getContainer().at(j)->getName()<<"\n";
                            return;
                        }
                        else if(player->getCurrentRoom()->getContainer().at(j)->getAccept() != "\0"
                        && player->getInventory().at(i).getName() == player->getCurrentRoom()->getContainer().at(j)->getAccept()){
                            moved_item = player->remItem(player->getInventory().at(i).getName());
                            player->getCurrentRoom()->getContainer().at(j)->addItem(moved_item);
                            cout<<"Item "<<moved_item.getName()<<" moved to "<<player->getCurrentRoom()->getContainer().at(j)->getName()<<"\n";
                            return;
                        }
                        else{
                            cout<<player->getInventory().at(i).getName()<<" cannot go into "<<player->getCurrentRoom()->getContainer().at(j)->getName()<<"\n";
                            return;
                        }
                    }
                }
            }
        }
        cout<<"That is not in your inventory.\n";
    }
    
    else if(command.find("turn") != string::npos){
        for(unsigned i = 0; i < player->getInventory().size(); i++){
            if(command.find(player->getInventory().at(i).getName()) != string::npos){
                if(player->getInventory().at(i).getTurnOnText() != "\0"){
                    cout<<player->getInventory().at(i).getTurnOnText()<<"\n";
                }
                for(unsigned j = 0; j < player->getInventory().at(i).getTurnOnAction().size(); j++){
                    interiorCommand(player->getInventory().at(i).getTurnOnAction().at(j), player, currentRoom);
                    if(player->getInventory().size() == 0){return;}
                }
                return;
            }
        }
        cout<<"That is not in your inventory.\n";
    }
    
    else if(command.find("attack") != string::npos){
        for(unsigned i = 0; i < player->getCurrentRoom()->getCreature().size(); i++){
            if(command.find(player->getCurrentRoom()->getCreature().at(i)->getName()) != string::npos){
                for(unsigned j = 0; j < player->getCurrentRoom()->getCreature().at(i)->getVulnerability().size(); j++){
                    if(command.find(player->getCurrentRoom()->getCreature().at(i)->getVulnerability().at(j)) != string::npos){
                        for(unsigned k = 0; k < player->getInventory().size(); k++){
                            if(player->getInventory().at(k).getName() == player->getCurrentRoom()->getCreature().at(i)->getCondObject()){
                                if(player->getInventory().at(k).getStatus() == player->getCurrentRoom()->getCreature().at(i)->getCondStatus()){
                                    if(currentRoom->getCreature().at(i)->getAttackText() != "\0"){cout<<currentRoom->getCreature().at(i)->getAttackText()<<"\n";}
                                    Creature creature = *currentRoom->getCreature().at(i);
                                    for(unsigned l = 0; l < creature.getAttackAction().size(); l++){
                                        interiorCommand(creature.getAttackAction().at(l), player, currentRoom);
                                    }
                                    return;
                                }
                                return;
                            }
                            else if(player->getCurrentRoom()->getCreature().at(i)->getCondObject() == "\0"){
                                if(command.find(player->getInventory().at(k).getName()) != string::npos){
                                    if(currentRoom->getCreature().at(i)->getAttackText() != "\0"){
                                        cout<<currentRoom->getCreature().at(i)->getAttackText()<<"\n";
                                    }
                                    Creature creature = *currentRoom->getCreature().at(i);
                                    for(unsigned l = 0; l < creature.getAttackAction().size(); l++){
                                        interiorCommand(creature.getAttackAction().at(l), player, currentRoom);
                                    }
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            return;
        } 
        return;
    }
}

//main function
int main(int argc, char **argv){
    vector<Room> rooms;
    vector<Item*> item_refs;
    vector<Container> containers;
    vector<Container*> cont_refs;
    vector<Creature*> creat_refs;
    int trig = 0;
    
    rooms = parseXMLRooms(argv[1]);
    master_items = parseXMLItems(argv[1]);
    for(unsigned i = 0; i < master_items.size(); i++){
        item_refs.push_back(&master_items.at(i));
    }
    containers = parseXMLContainers(argv[1]);
    for(unsigned i = 0; i < containers.size(); i++){
        cont_refs.push_back(&containers.at(i));
    }
    master_creatures = parseXMLCreatures(argv[1]);
    for(unsigned i = 0; i < master_creatures.size(); i++){
        creat_refs.push_back(&master_creatures.at(i));
    }
    containers = buildContainers(containers, master_items);
    rooms = buildDungeon(rooms, master_items, cont_refs, creat_refs);
    
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
        getPlayerAction(&player);
        
        Trigger temp_trigger = player.getCurrentRoom()->getTrigger();
        trig = checkTriggers(&player, &temp_trigger, "");
        player.getCurrentRoom()->setTrigger(temp_trigger);
        
        for(unsigned i = 0; i < player.getCurrentRoom()->getCreature().size(); i++){
            temp_trigger = player.getCurrentRoom()->getCreature().at(i)->getTrigger();
            trig = checkTriggers(&player, &temp_trigger, "");
            player.getCurrentRoom()->getCreature().at(i)->setTrigger(temp_trigger);
            
        }
        
        for(unsigned i = 0; i < player.getCurrentRoom()->getContainer().size(); i++){
            temp_trigger = player.getCurrentRoom()->getContainer().at(i)->getTrigger();
            trig = checkTriggers(&player, &temp_trigger, "");
            player.getCurrentRoom()->getContainer().at(i)->setTrigger(temp_trigger);
            
        }
    }
    
    cout<<"Game Over\n";
    
    return EXIT_SUCCESS;
}