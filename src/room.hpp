#ifndef __ROOM_HPP_INCLUDED__
#define __ROOM_HPP_INCLUDED__
#include "item.hpp"
#include "container.hpp"
#include "creature.hpp"
#include "trigger.hpp"

class Room{
    private:
        char name, status, type, description;
        std::vector<Room*> border;
        std::vector<Container> container;
        std::vector<Item> item;
        std::vector<Creature> creature;
        std::vector<Trigger> trigger;
};

#endif