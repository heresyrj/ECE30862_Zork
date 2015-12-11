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
        std::string turn_on_text;
        std::vector<std::string> turn_on_action;
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
        void setTurnOnText(std::string turn);
        std::string getTurnOnText(void);
        void addTurnOnAction(std::string action);
        std::vector<std::string> getTurnOnAction(void);
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
void Item::setTurnOnText(std::string turn){turn_on_text = turn;}
std::string Item::getTurnOnText(void){return turn_on_text;}
void Item::addTurnOnAction(std::string action){turn_on_action.push_back(action);}
std::vector<std::string> Item::getTurnOnAction(void){return turn_on_action;}

#endif