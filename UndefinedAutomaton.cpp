//
// Created by ejh61 on 2021-09-15.
//

#include "UndefinedAutomaton.h"

void UndefinedAutomaton::S0(const std::string& input) {
    if(input[index] == '\'') {
        while((unsigned) index < input.size()){

            if(input[index] == '\n')
                newLines++;

            inputRead++;
            index++;
        }
    }
    else if(input[index] == '#' && input[index + 1] == '|'){
        while((unsigned) index < input.size()){

            if(input[index] == '\n')
                newLines++;

            inputRead++;
            index++;
        }
    }
}
