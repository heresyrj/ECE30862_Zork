#ifndef __TRIGGER_HPP_INCLUDED__
#define __TRIGGER_HPP_INCLUDED__

class Trigger{
    private:
        std::vector<std::string> actions;
        std::string text;
        std::string owner;
        std::string status;
        std::string has;
        std::string object;
        
    public:
        Trigger();
        ~Trigger();
        void setText(std::string txt);
        std::string getText(void);
        void setOwner(std::string own);
        std::string getOwner(void);
        void setStatus(std::string stat);
        std::string getStatus(void);
        void setHas(std::string hs);
        std::string getHas(void);
        void setObject(std::string obj);
        std::string getObject(void);
};

Trigger::Trigger();
Trigger::~Trigger();
void Trigger::setText(std::string txt);
std::string Trigger::getText(void);
void Trigger::setOwner(std::string own);
std::string Trigger::getOwner(void);
void Trigger::setStatus(std::string stat);
std::string Trigger::getStatus(void);
void Trigger::setHas(std::string hs);
std::string Trigger::getHas(void);
void Trigger::setObject(std::string obj);
std::string Trigger::getObject(void);
#endif