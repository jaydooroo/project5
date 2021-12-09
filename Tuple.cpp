//
// Created by ejh61 on 2021-10-26.
//

#include "Tuple.h"


void Tuple::SetTuple(std::string value) {

    values.push_back(value);

}

std::vector<std::string> & Tuple::getTuple (){
    return values;
}

std::string Tuple::toString () {
    std::ostringstream oss;

    for (unsigned int i = 0; i < values.size(); i++)  {

        oss << values.at(i) << " ";

    } // how should I implement this.

    return oss.str();
}