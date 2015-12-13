#ifndef __CONTAINER_HPP_INCLUDED__
#define __CONTAINER_HPP_INCLUDED__
#include "item.hpp"
#include "trigger.hpp"

class Container{
    private:
        std::string name;
        std::string status;
        std::string description;
        std::string accept;
        std::vector<Item> item;
        Trigger trigger;
        std::vector<std::string> item_list;
        int open_flag;
        
    public:
        Container();
        ~Container();
        void setName(std::string nam);
        std::string getName(void);
        void setStatus(std::string stat);
        std::string getStatus(void);
        void setDescription(std::string desc);
        std::string getDescription(void);
        void setAccept(std::string stat);
        std::string getAccept(void);
        void addItem(Item item);
        std::vector<Item> getItem(void);
        Item remItem(std::string item);
        void addItemList(std::string it);
        std::vector<std::string> getItemList(void);
        void remItemList(std::string it);
        void setOpenFlag(int flag);
        int getOpenFlag(void);
        void setTrigger(Trigger trig);
        Trigger getTrigger(void);
        
};

Container::Container(){open_flag = 0;}
Container::~Container(){}
void Container::setName(std::string nam){name = nam;}
std::string Container::getName(void){return name;}
void Container::setStatus(std::string stat){status = stat;}
std::string Container::getStatus(void){return status;}
void Container::setDescription(std::string desc){description = desc;}
std::string Container::getDescription(void){return description;}
void Container::setAccept(std::string acc){accept = acc;}
std::string Container::getAccept(void){return accept;}
void Container::setOpenFlag(int flag){open_flag = flag;}
int Container::getOpenFlag(void){return open_flag;}
void Container::setTrigger(Trigger trig){trigger = trig;}
Trigger Container::getTrigger(void){return trigger;}
//container functions
void Container::addItem(Item it){item.push_back(it);}
std::vector<Item> Container::getItem(void){return item;}
Item Container::remItem(std::string it){
    for(unsigned i = 0; i < item.size(); i++){
        if(item.at(i).getName() == it){
            Item new_item = item.at(i);
            item.erase(item.begin()+i);
            return new_item;
        }
    }
}

void Container::addItemList(std::string it){item_list.push_back(it);}
std::vector<std::string> Container::getItemList(void){return item_list;}
void Container::remItemList(std::string it){
    for(unsigned i = 0; i < item_list.size(); i++){
        if(item_list.at(i) == it){
            item_list.erase (item_list.begin()+i);
            return;
        }
    }
}


#endif