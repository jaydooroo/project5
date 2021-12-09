//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_MULTIPLYAUTOMATON_H
#define PROJECT1_STARTER_CODE_MULTIPLYAUTOMATON_H
#include "Automaton.h"

class MultiplyAutomaton : public Automaton{

public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}
   ~MultiplyAutomaton() {}
    void S0(const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_MULTIPLYAUTOMATON_H
