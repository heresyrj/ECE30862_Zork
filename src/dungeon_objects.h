class Trigger{
    
}

class Creature{
    private:
        char name[10];
        char status[10];
        char description[10];
        char vulnerability[10];
        char attack[10];
        Trigger trigger;    
}

class Item{
    private:
        char name[10];
        char status[10];
        char description[10];
        char writing[10];
        char turn_on[10];
        Trigger trigger;    
}

class Container{
    private:
        char name[10];
        char status[10];
        char description[10];
        char accept[10];
        Item item;
        Trigger trigger;    
}

class Room {
    private:
        char name[10];
        char status[10];
        char type[10];
        char description[10];
        Container container;
        Item item;
        Creature creature;
        Trigger trigger;
}