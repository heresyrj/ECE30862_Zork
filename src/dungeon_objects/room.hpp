#ifndef __ROOM_HPP_INCLUDED__
#define __ROOM_HPP_INCLUDED__
#include <iostream>
#include <vector>
#include "dungeon.hpp"
#include "item.hpp"
#include "container.hpp"
#include "creature.hpp"
#include "trigger.hpp"
#include "border.hpp"

class Room: public Dungeon{
    private:
        std::string name, status, type, description;
        std::vector<Border> border;
        std::vector<Container*> container;
        std::vector<std::string> container_list;
        std::vector<Item> item;
        std::vector<std::string> item_list;
        std::vector<Creature> creature;
        std::vector<std::string> creature_list;
        Trigger trigger;
        Room *north;
        Room *east;
        Room *south;
        Room *west;
        
    public:
        Room();
        ~Room();
        void setName(std::string nam);
        void setStatus(std::string stat);
        void setType(std::string ty);
        void setDescription(std::string disc);
        void setNorth(Room *nroom);
        void setEast(Room *eroom);
        void setSouth(Room *sroom);
        void setWest(Room *wroom);
        std::string getName(void);
        std::string getStatus(void);
        std::string getType(void);
        std::string getDescription(void);
        Room * getNorth(void);
        Room * getEast(void);
        Room * getSouth(void);
        Room * getWest(void);
        void addContainer(Container *cont);
        std::vector<Container*> getContainer(void);
        void remContainer(std::string cont);
        void addContainerList(std::string cont);
        std::vector<std::string> getContainerList(void);
        void remContainerList(std::string cont);
        void addItem(Item it);
        std::vector<Item> getItem(void);
        Item remItem(std::string it);
        void delItem(std::string it);
        void addItemList(std::string it);
        std::vector<std::string> getItemList(void);
        void remItemList(std::string it);
        void addCreature(Creature creat);
        std::vector<Creature> getCreature(void);
        void delCreature(std::string creat);
        void addCreatureList(std::string creat);
        std::vector<std::string> getCreatureList(void);
        void remCreatureList(std::string creat);
        void setTrigger(Trigger trig);
        Trigger getTrigger(void);
        void addBorder(Border bord);
        std::vector<Border> getBorder(void);
        void remBorder(std::string bord);
};

Room::Room(){
    north = NULL;
    east = NULL;
    south = NULL;
    west = NULL;
}
Room::~Room(){}

//name functions
void Room::setName(std::string nam){name = nam;}
std::string Room::getName(void){return name;}

//status functions
void Room::setStatus(std::string stat){status = stat;}
std::string Room::getStatus(void){return status;}

//type functions
void Room::setType(std::string ty){type = ty;}
std::string Room::getType(void){return type;}

//description functions
void Room::setDescription(std::string disc){description = disc;}
std::string Room::getDescription(void){return description;}

//direction functions
void Room::setNorth(Room* nroom){north = nroom;}
void Room::setEast(Room* eroom){east = eroom;}
void Room::setSouth(Room* sroom){south = sroom;}
void Room::setWest(Room* wroom){west = wroom;}
Room * Room::getNorth(void){return north;}
Room * Room::getEast(void){return east;}
Room * Room::getSouth(void){return south;}
Room * Room::getWest(void){return west;}

//container functions
void Room::addContainer(Container *cont){container.push_back(cont);}
std::vector<Container*> Room::getContainer(void){return container;}
void Room::remContainer(std::string cont){}

void Room::addContainerList(std::string cont){container_list.push_back(cont);}
std::vector<std::string> Room::getContainerList(void){return container_list;}
void Room::remContainerList(std::string cont){
    for(unsigned i = 0; i < container_list.size(); i++){
        if(container_list.at(i) == cont){
            container_list.erase (container_list.begin()+i);
            return;
        }
    }
}

//item functions
void Room::addItem(Item it){item.push_back(it);}
std::vector<Item> Room::getItem(void){return item;}
Item Room::remItem(std::string it){
    for(unsigned i = 0; i < item.size(); i++){
        if(item.at(i).getName() == it){
            Item taken_item = item.at(i);
            item.erase(item.begin()+i);
            return taken_item;
        }
    }
}
void Room::delItem(std::string it){
    for(unsigned i = 0; i < item.size(); i++){
        if(item.at(i).getName() == it){
            item.erase(item.begin()+i);
            return;
        }
    }
}

void Room::addItemList(std::string it){item_list.push_back(it);}
std::vector<std::string> Room::getItemList(void){return item_list;}
void Room::remItemList(std::string it){
    for(unsigned i = 0; i < item_list.size(); i++){
        if(item_list.at(i) == it){
            item_list.erase (item_list.begin()+i);
            return;
        }
    }
}

//creature functions
void Room::addCreature(Creature creat){creature.push_back(creat);}
std::vector<Creature> Room::getCreature(void){return creature;}
void Room::delCreature(std::string creat){
    for(unsigned i = 0; i < creature.size(); i++){
        if(creat == creature.at(i).getName()){
            creature.erase(creature.begin()+i);
            return;
        }
    }
}

void Room::addCreatureList(std::string creat){creature_list.push_back(creat);}
std::vector<std::string> Room::getCreatureList(void){return creature_list;}
void Room::remCreatureList(std::string creat){
    for(unsigned i = 0; i < creature_list.size(); i++){
        if(creature_list.at(i) == creat){
            creature_list.erase (creature_list.begin()+i);
            return;
        }
    }
}

//border functions
void Room::addBorder(Border bord){border.push_back(bord);}
std::vector<Border> Room::getBorder(void){return border;}
void Room::remBorder(std::string bord){
    for(unsigned i = 0; i < border.size(); i++){
        if(border.at(i).getDirection() == bord){
            border.erase (border.begin()+i);
            return;
        }
    }
}

void Room::setTrigger(Trigger trig){trigger = trig;}
Trigger Room::getTrigger(void){return trigger;}


#endif