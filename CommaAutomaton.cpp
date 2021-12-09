//
// Created by ejh61 on 2021-09-15.
//

#include "CommaAutomaton.h"

void CommaAutomaton::S0(const std::string &input) {
    if (input[index] == ','){
        inputRead = 1;
    }
    else {
        Serr();
    }
}
