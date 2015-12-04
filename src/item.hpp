#ifndef __ITEM_HPP_INCLUDED__
#define __ITEM_HPP_INCLUDED__
#include "trigger.hpp"

class Item{
    private:
        char name[10];
        char status[10];
        char description[10];
        char writing[10];
        char turn_on[10];
        std::vector<Trigger> trigger;    
};

#endif