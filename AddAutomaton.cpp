//
// Created by ejh61 on 2021-09-15.
//

#include "AddAutomaton.h"

void AddAutomaton::S0(const std::string &input) {
    if (input[index] == '+') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}