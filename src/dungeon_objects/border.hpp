#ifndef __BORDER_HPP_INCLUDED__
#define __BORDER_HPP_INCLUDED__

class Border{
    private:
        std::string direction;
        std::string name;
        
    public:
        Border();
        ~Border();
        void setDirection(std::string dir);
        void setName(std::string nam);
        std::string getDirection(void);
        std::string getName(void);
};

Border::Border(){}
Border::~Border(){}
void Border::setDirection(std::string dir){direction = dir;}
void Border::setName(std::string nam){name = nam;}
std::string Border::getDirection(void){return direction;}
std::string Border::getName(void){return name;}

#endif