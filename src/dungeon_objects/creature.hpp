#ifndef __CREATURE_HPP_INCLUDED__
#define __CREATURE_HPP_INCLUDED__
#include "trigger.hpp"

class Creature{
    private:
        std::string name;
        std::string status;
        std::string description;
        std::vector<std::string> vulnerability;
        std::string attackText;
        std::vector<std::string> attackAction;
        std::string cond_object;
        std::string cond_status;
        Trigger trigger;
        
    public:
        Creature();
        ~Creature();
        void setName(std::string nam);
        std::string getName(void);
        void setStatus(std::string stat);
        std::string getStatus(void);
        void setDescription(std::string desc);
        std::string getDescription(void);
        void addVulnerability(std::string vuln);
        std::vector<std::string> getVulnerability(void);
        void setCondObject(std::string object);
        std::string getCondObject(void);
        void setCondStatus(std::string status);
        std::string getCondStatus(void);
        void setAttackText(std::string text);
        std::string getAttackText(void);
        void addAttackAction(std::string action);
        std::vector<std::string> getAttackAction(void);
        void setTrigger(Trigger trig);
        Trigger getTrigger(void);
};
Creature::Creature(){}
Creature::~Creature(){}
void Creature::setName(std::string nam){name = nam;}
std::string Creature::getName(void){return name;}
void Creature::setStatus(std::string stat){status = stat;}
std::string Creature::getStatus(void){return status;}
void Creature::setDescription(std::string desc){description = desc;}
std::string Creature::getDescription(void){return description;}
void Creature::addVulnerability(std::string vuln){vulnerability.push_back(vuln);}
std::vector<std::string> Creature::getVulnerability(void){return vulnerability;}
void Creature::setCondObject(std::string object){cond_object = object;}
std::string Creature::getCondObject(void){return cond_object;}
void Creature::setCondStatus(std::string status){cond_status = status;}
std::string Creature::getCondStatus(void){return cond_status;}
void Creature::setAttackText(std::string text){attackText = text;}
std::string Creature::getAttackText(void){return attackText;}
void Creature::addAttackAction(std::string action){attackAction.push_back(action);}
std::vector<std::string> Creature::getAttackAction(void){return attackAction;}
void Creature::setTrigger(Trigger trig){trigger = trig;}
Trigger Creature::getTrigger(void){return trigger;}
#endif