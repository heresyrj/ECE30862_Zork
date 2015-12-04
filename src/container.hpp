#ifndef __CONTAINER_HPP_INCLUDED__
#define __CONTAINER_HPP_INCLUDED__
#include "item.hpp"
#include "trigger.hpp"

class Container{
    private:
        char name[10];
        char status[10];
        char description[10];
        char accept[10];
        std::vector<Item> item;
        std::vector<Trigger> trigger;    
};

#endif