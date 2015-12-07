#ifndef __CREATURE_HPP_INCLUDED__
#define __CREATURE_HPP_INCLUDED__
#include "trigger.hpp"

class Creature{
    private:
        std::string name;
        std::string status;
        std::string description;
        std::string vulnerability;
        std::string attack;
        std::vector<Trigger> trigger;    
};

#endif