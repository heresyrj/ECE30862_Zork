#ifndef __PLAYER_HPP_INCLUDED__
#define __PLAYER_HPP_INCLUDED__
#include <vector>
#include "room.hpp"

class Player{
    private:
        Room *current_room;
        std::vector<Item> inventory;
        
    public:
        Player(Room *current);
        ~Player();
        void setCurrentRoom(Room *current);
        Room* getCurrentRoom(void);
        void addItem(Item item);
        std::vector<Item> getInventory(void);
        Item remItem(std::string item);
};

Player::Player(Room *current){
    current_room = current;
}
Player::~Player(){}

//current room functions
void Player::setCurrentRoom(Room *current){current_room = current;}
Room* Player::getCurrentRoom(void){return current_room;}

//inventory functions
void Player::addItem(Item item){inventory.push_back(item);}
std::vector<Item> Player::getInventory(void){return inventory;}
Item Player::remItem(std::string item){
    Item dropped_item;
    for(unsigned i; i < inventory.size(); i++){
        if(inventory.at(i).getName() == item){
            dropped_item = inventory.at(i);
            inventory.erase(inventory.begin()+i);
            return dropped_item;
        }
    }
}


/*
This is how you would check if the player had the item in their inventory

Item dropped_item = player.remItem("bomb");
    if(dropped_item.getName() == "\0"){
        cout<<"No such item in your inventory\n";
    }
    else{
        player.getCurrentRoom->addItem(dropped_item);
    }
*/
#endif