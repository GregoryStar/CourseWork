#include <iostream>
#include <string>
#include "MysteryDuck.h"

using std::cout;
using std::endl;
using std::string;

MysteryDuck::MysteryDuck(string d, string s) {
    descriptionText = d;
    sound = s;
}

string MysteryDuck::getDescription() {
    return descriptionText;
}

void MysteryDuck::performQuack(){
     cout << sound << endl;
}
