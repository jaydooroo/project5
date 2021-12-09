//
// Created by ejh61 on 2021-09-15.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string &input) {

    if(input[index] == '#'){
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string &input) {

    if(input[1] == '|'){    // #| 인 경우
        inputRead++;
        index++;  // |가 바로 왔ㅇ
        S2(input);
    }
    else if(input[index] != '\n'){
        inputRead++;
        index++;
        S1(input);
    }
}

void CommentAutomaton::S2(const std::string &input) {
    if((unsigned) index >= input.size()){
        Serr();
    }
    else if(input[index] != '|') {
        if(input[index] == '\n') {
            newLines++;
        }
        inputRead++;
        index++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S3(input);
    }
}

void CommentAutomaton::S3(const std::string &input) {
    if((unsigned) index >= input.size()){
        Serr();
    }
    else if(input[index] == '\n'){
        newLines++;
        inputRead++;
        index++;
        S2(input);
    }
    else if((input[index] != '#') && (input[index] != '|')) {

        inputRead++;
        index++;
        S2(input);
    }
    else if(input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if(input[index] == '#'){
        inputRead++;
    }
}


