//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_LEFTPARENAUTOMATON_H
#define PROJECT1_STARTER_CODE_LEFTPARENAUTOMATON_H
#include "Automaton.h"

class LeftParenAutomaton: public Automaton {

public:
    LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}
   ~ LeftParenAutomaton() {}
    void S0(const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_LEFTPARENAUTOMATON_H
