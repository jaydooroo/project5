//
// Created by ejh61 on 2021-09-13.
//

#ifndef PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
#define PROJECT1_STARTER_CODE_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton: public Automaton {

private:
    void S1(const std:: string& input);
    void S2(const std:: string& input);

public:
    StringAutomaton() : Automaton(TokenType::STRING){}
   ~ StringAutomaton() {}
    void S0(const std::string &input);

};


#endif //PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
