#ifndef __TRIGGER_HPP_INCLUDED__
#define __TRIGGER_HPP_INCLUDED__

class Trigger{
    private:
        std::vector<std::string> actions;
        std::string command;
        std::string text;
        std::string owner;
        std::string status;
        std::string has;
        std::string object;
        std::string type;
        int triggerFlag;
        int live;
        
    public:
        Trigger();
        ~Trigger();
        void setText(std::string txt);
        std::string getText(void);
        void setCommand(std::string com);
        std::string getCommand(void);
        void setOwner(std::string own);
        std::string getOwner(void);
        void setStatus(std::string stat);
        std::string getStatus(void);
        void setHas(std::string hs);
        std::string getHas(void);
        void setObject(std::string obj);
        std::string getObject(void);
        void setType(std::string ty);
        std::string getType(void);
        void addAction(std::string action);
        std::vector<std::string> getAction(void);
        void remAction(std::string action);
        void setTriggerFlag(int flag);
        int getTriggerFlag(void);
        void setLive(int liv);
        int getLive(void);
};

Trigger::Trigger(){triggerFlag = 0;}
Trigger::~Trigger(){}
void Trigger::setText(std::string txt){text = txt;}
std::string Trigger::getText(void){return text;}
void Trigger::setCommand(std::string com){command = com;}
std::string Trigger::getCommand(void){return command;}
void Trigger::setOwner(std::string own){owner = own;}
std::string Trigger::getOwner(void){return owner;}
void Trigger::setStatus(std::string stat){status = stat;}
std::string Trigger::getStatus(void){return status;}
void Trigger::setHas(std::string hs){has = hs;}
std::string Trigger::getHas(void){return has;}
void Trigger::setObject(std::string obj){object = obj;}
std::string Trigger::getObject(void){return object;}
void Trigger::setType(std::string ty){type = ty;}
std::string Trigger::getType(void){return type;}
void Trigger::addAction(std::string action){actions.push_back(action);}
std::vector<std::string> Trigger::getAction(void){return actions;}
void Trigger::remAction(std::string action){
    for(unsigned i = 0; i < actions.size(); i++){
        if(action == actions.at(i)){
            actions.erase(actions.begin()+i);
            return;
        }
    }
}
void Trigger::setTriggerFlag(int flag){triggerFlag = flag;}
int Trigger::getTriggerFlag(void){return triggerFlag;}
void Trigger::setLive(int liv){live = liv;}
int Trigger::getLive(void){return live;}

#endif