//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_PERIODAUTOMATON_H
#define PROJECT1_STARTER_CODE_PERIODAUTOMATON_H
#include "Automaton.h"

class PeriodAutomaton: public Automaton {

public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD){}
   ~ PeriodAutomaton() {}
        void S0(const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_PERIODAUTOMATON_H
