//
// Created by ejh61 on 2021-09-25.
//

#include "Rule.h"

std::string Rule::toString () {
    std::ostringstream oss;

    oss << headPredicate.toString() << " :- ";

    for (unsigned int i = 0; i < predicateList.size() - 1; i++) {
        oss << predicateList.at(i).toString() << ",";
    }

    oss << predicateList.at(predicateList.size() - 1).toString() << ".";

    return oss.str();
}