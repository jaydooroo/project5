//
// Created by ejh61 on 2021-09-25.
//

#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H
#include <vector>
#include <string>
#include <sstream>
#include "Parameter.h"

class Predicate {
private:
    std::string ID;
    std::vector <Parameter> insideString;

public:
Predicate (std::string tempID): ID(tempID) {}
Predicate() {}

~Predicate() {}

void setMainID (std::string tempID) {
    ID = tempID;
}

void setID (std::string tempID) {
    Parameter tempSet("ID",tempID);
    insideString.push_back(tempSet);
}

void setString (std::string tempString) {
    Parameter tempSet("STRING", tempString);
    insideString.push_back(tempSet);
}

std::vector<Parameter> &returnParameter () {
    return insideString;
}

std::string returnID() {
    return ID;
}

std::string toString ();
};


#endif //PROJECT1_STARTER_CODE_PREDICATE_H
