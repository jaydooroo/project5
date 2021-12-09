//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_Q_MARKAUTOMATON_H
#define PROJECT1_STARTER_CODE_Q_MARKAUTOMATON_H
#include "Automaton.h"

class Q_MarkAutomaton: public Automaton {

public:
    Q_MarkAutomaton() : Automaton(TokenType::Q_MARK) {}
   ~ Q_MarkAutomaton() {}
    void S0(const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_Q_MARKAUTOMATON_H
