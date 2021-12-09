//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_COMMAAUTOMATON_H
#define PROJECT1_STARTER_CODE_COMMAAUTOMATON_H
#include "Automaton.h"

class CommaAutomaton : public Automaton {
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}
    ~ CommaAutomaton() {}
    void S0(const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_COMMAAUTOMATON_H
