#ifndef __CREATURE_HPP_INCLUDED__
#define __CREATURE_HPP_INCLUDED__
#include "trigger.hpp"

class Creature{
    private:
        char name[10];
        char status[10];
        char description[10];
        char vulnerability[10];
        char attack[10];
        std::vector<Trigger> trigger;    
};

#endif