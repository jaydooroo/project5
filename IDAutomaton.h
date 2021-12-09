//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_IDAUTOMATON_H
#define PROJECT1_STARTER_CODE_IDAUTOMATON_H

#include "Automaton.h"

class IDAutomaton : public Automaton {
private:
    void S1 (const std::string& input);

public:
    IDAutomaton() : Automaton(TokenType::ID) {}
   ~ IDAutomaton() {}
    void S0 (const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_IDAUTOMATON_H
