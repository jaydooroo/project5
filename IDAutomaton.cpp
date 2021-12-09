//
// Created by ejh61 on 2021-09-15.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string &input) {
    if(isalpha(input[index])){
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string &input) {

    if((unsigned) index < input.size()) {
        while (isalpha(input[index]) || isalnum(input[index])) {
            inputRead++;
            index++;
        }
        // discern if it is the strings
        if(input.substr(0,inputRead) == "Schemes" ||input.substr(0,inputRead) == "Facts"
        ||input.substr(0,inputRead) == "Rules"||input.substr(0,inputRead) == "Queries"){
            Serr();
        }
    }
}
