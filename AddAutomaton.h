//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_ADDAUTOMATON_H
#define PROJECT1_STARTER_CODE_ADDAUTOMATON_H
#include "Automaton.h"

class AddAutomaton : public Automaton {

public:
    AddAutomaton() : Automaton(TokenType::ADD) { }
    ~AddAutomaton() {}

    void S0(const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_ADDAUTOMATON_H
