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
};

#endif