//
// Created by ejh61 on 2021-09-15.
//

#ifndef PROJECT1_STARTER_CODE_SCHEMESAUTOMATON_H
#define PROJECT1_STARTER_CODE_SCHEMESAUTOMATON_H

#include "Automaton.h"

class SchemesAutomaton : public Automaton {

private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);
    void S5(const std::string& input);
    void S6(const std::string& input);

public:
    SchemesAutomaton() : Automaton(TokenType::SCHEMES){}
   ~ SchemesAutomaton() {}
    void S0(const std::string& input);

};


#endif //PROJECT1_STARTER_CODE_SCHEMESAUTOMATON_H
