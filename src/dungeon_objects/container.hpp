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
        std::vector<Trigger> trigger;    
};

#endif