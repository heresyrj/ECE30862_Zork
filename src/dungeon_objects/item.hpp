#ifndef __ITEM_HPP_INCLUDED__
#define __ITEM_HPP_INCLUDED__
#include "dungeon.hpp"
#include "trigger.hpp"

class Item{
    private:
        std::string name;
        std::string status;
        std::string description;
        std::string writing;
        std::string turn_on;
        std::vector<Trigger> trigger;
        
    public:
        Item();
        ~Item();
        void setName(std::string nam);
        std::string getName(void);
        void setStatus(std::string stat);
        std::string getStatus(void);
        void setDescription(std::string desc);
        std::string getDescription(void);
        void setWriting(std::string writ);
        std::string getWriting(void);
        void setTurnOn(std::string turn);
        std::string getTurnOn(void);
};

Item::Item(){}
Item::~Item(){}
void Item::setName(std::string nam){name = nam;}
std::string Item::getName(void){return name;}
void Item::setStatus(std::string stat){status = stat;}
std::string Item::getStatus(void){return status;}
void Item::setDescription(std::string desc){description = desc;}
std::string Item::getDescription(void){return description;}
void Item::setWriting(std::string writ){writing = writ;}
std::string Item::getWriting(void){return writing;}
void Item::setTurnOn(std::string turn){turn_on = turn;}
std::string Item::getTurnOn(void){return turn_on;}

#endif