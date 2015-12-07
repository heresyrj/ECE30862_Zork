#ifndef __ROOM_HPP_INCLUDED__
#define __ROOM_HPP_INCLUDED__
#include "item.hpp"
#include "container.hpp"
#include "creature.hpp"
#include "trigger.hpp"
#include "border.hpp"

class Room{
    private:
        std::string name, status, type, description;
        std::vector<Border> border;
        std::vector<Container> container;
        std::vector<Item> item;
        std::vector<Creature> creature;
        std::vector<Trigger> trigger;
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
        std::string getName(void);
        std::string getStatus(void);
        std::string getType(void);
        std::string getDescription(void);
        void addBorder(Border bord);
        void addContainer(Container cont);
        void addItem(Item it);
        void addCreature(Creature creat);
        void addTrigger(Trigger trig);
        void remBorder(Border bord);
        void remContainer(Container cont);
        void remItem(Item it);
        void remCreature(Creature creat);
        void remTrigger(Trigger trig);
        std::vector<Border> getBorder(void);
};

Room::Room(){
    north = NULL;
    east = NULL;
    south = NULL;
    west = NULL;
}
Room::~Room(){}
void Room::setName(std::string nam){name = nam;}
void Room::setStatus(std::string stat){status = stat;}
void Room::setType(std::string ty){type = ty;}
void Room::setDescription(std::string disc){description = disc;}
std::string Room::getName(void){return name;}
std::string Room::getStatus(void){return status;}
std::string Room::getType(void){return type;}
std::string Room::getDescription(void){return description;}

void Room::addBorder(Border bord){border.push_back(bord);}
void Room::addContainer(Container cont){container.push_back(cont);}
void Room::addItem(Item it){item.push_back(it);}
void Room::addCreature(Creature creat){creature.push_back(creat);}
void Room::addTrigger(Trigger trig){trigger.push_back(trig);}
void Room::remBorder(Border bord){border.push_back(bord);}
void Room::remContainer(Container cont){container.push_back(cont);}
void Room::remItem(Item it){item.push_back(it);}
void Room::remCreature(Creature creat){creature.push_back(creat);}
void Room::remTrigger(Trigger trig){trigger.push_back(trig);}
std::vector<Border> Room::getBorder(void){return border;}


#endif