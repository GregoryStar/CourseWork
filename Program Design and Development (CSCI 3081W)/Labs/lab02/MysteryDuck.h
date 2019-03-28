#ifndef LAB02_MYSTERYDUCK_H_
#define LAB02_MYSTERYDUCK_H_

#include <string>
#include "Duck.h"

class MysteryDuck : public Duck {
private:
   std::string descriptionText;
   std::string sound;
public:
    MysteryDuck(std::string d, std::string s);
    std::string getDescription();
    void performQuack();
};



#endif
