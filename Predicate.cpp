//
// Created by ejh61 on 2021-09-25.
//

#include "Predicate.h"

std::string Predicate::toString () {

    std::ostringstream oss;
    oss << ID << "(" ;
    for (unsigned int i = 0; i < insideString.size() - 1; i++) {
        oss << insideString.at(i).toString() << ",";
    }
    oss << insideString.at(insideString.size() - 1).toString() ;

    oss << ")";

    return oss.str();
}