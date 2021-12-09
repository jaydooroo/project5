//
// Created by ejh61 on 2021-09-25.
//

#include "Parameter.h"


Parameter:: Parameter(std::string tempChoice, std::string tempString): choice(tempChoice) {
    if (choice == "STRING") {
        STRING = tempString;
    } else {
        ID = tempString;
    }
}

std::string Parameter::toString() {
    std::ostringstream oss;
    if (choice == "STRING") {
        oss << STRING;
    }
    else {
        oss << ID;
    }

    return oss.str();
}