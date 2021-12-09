//
// Created by ejh61 on 2021-10-26.
//

#include "Header.h"

void Header::SetHeader (std::string attribute) {
    attributes.push_back(attribute);
}

std::vector<std::string> &Header::GetHeader () {
    return attributes;
}

std::string Header::toString() {

    std::ostringstream oss;

    for (unsigned int i = 0; i < attributes.size(); i++) {
        if ( i < attributes.size() - 1) {
            oss << attributes.at(i) << ",";
        }
        else {
            oss << attributes.at(i);
        }
    }

    return oss.str();
}