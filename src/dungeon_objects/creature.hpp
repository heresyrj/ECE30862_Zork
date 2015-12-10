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
        
    public:
        Creature();
        ~Creature();
        void setName(std::string nam);
        std::string getName(void);
        void setStatus(std::string stat);
        std::string getStatus(void);
        void setDescription(std::string desc);
        std::string getDescription(void);
        void setVulnerability(std::string vuln);
        std::string getVulnerability(void);
};
Creature::Creature(){}
Creature::~Creature(){}
void Creature::setName(std::string nam){name = nam;}
std::string Creature::getName(void){return name;}
void Creature::setStatus(std::string stat){status = stat;}
std::string Creature::getStatus(void){return status;}
void Creature::setDescription(std::string desc){description = desc;}
std::string Creature::getDescription(void){return description;}
void Creature::setVulnerability(std::string vuln){vulnerability = vuln;}
std::string Creature::getVulnerability(void){return vulnerability;}
#endif