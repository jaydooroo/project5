//
// Created by ejh61 on 2021-09-13.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string &input) {

    if((unsigned) index >= input.size()){
        Serr();
    }
    else if(input[index] == '\''){
        inputRead++;
        index++;

        S1(input);
    }
    else{
        Serr();
    }
}

void StringAutomaton::S1(const std::string &input) {

    if((unsigned) index >= input.size()){
        Serr();
    }
    else if(input[index] == '\''){
        inputRead++;
        index++;
        S2(input);
    }
    else if(input[index]=='\n'){
        inputRead++;
        index++;
        newLines++;
        S1(input);
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string &input) {

    if((unsigned) index >= input.size()){

    }
    else if(input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
}
