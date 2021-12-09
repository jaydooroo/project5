//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_UNDEFINEDAUTOMATON_H
#define PROJECT1_STARTER_CODE_UNDEFINEDAUTOMATON_H
#include "Automaton.h"

class UndefinedAutomaton: public Automaton {

public:
    UndefinedAutomaton() : Automaton(TokenType::UNDEFINED) {}
   ~ UndefinedAutomaton() { }
    void S0 (const std::string& input);

};


#endif //PROJECT1_STARTER_CODE_UNDEFINEDAUTOMATON_H
