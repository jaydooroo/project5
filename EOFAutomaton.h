//
// Created by ejh61 on 2021-09-16.
//

#ifndef PROJECT1_STARTER_CODE_EOFAUTOMATON_H
#define PROJECT1_STARTER_CODE_EOFAUTOMATON_H
#include "Automaton.h"

class EOFAutomaton : public Automaton {
public:
    EOFAutomaton() : Automaton(TokenType::_EOF){}
    ~EOFAutomaton() {}
    void S0(const std::string& input);

};


#endif //PROJECT1_STARTER_CODE_EOFAUTOMATON_H
