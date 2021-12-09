//
// Created by ejh61 on 2021-09-15.
//

#include "PeriodAutomaton.h"

void PeriodAutomaton::S0(const std::string &input) {
    if (input[index] == '.'){
        inputRead = 1;
    }
    else {
        Serr();
    }
}
