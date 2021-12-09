//
// Created by ejh61 on 2021-09-23.
//

#ifndef PROJECT1_STARTER_CODE_PARSER_H
#define PROJECT1_STARTER_CODE_PARSER_H
#include "Token.h"
#include <vector>
#include <sstream>
#include "DatalogProgram.h"

class Parser {

private:
    std::vector<Token *> tokens;
    DatalogProgram datalog;



public:
    Parser(std::vector<Token *> tempToken) {
        tokens = tempToken;
    }

    ~ Parser() {}

    DatalogProgram &getDatalog () {
        return datalog;
    }

    std::string datalogParse();

    std::string toString();

    void printDatalog ();

    void schemeParse (int &index);
    void schemeListParse(int &index);
    void factListParse (int &index);
    void factParse (int &index);
    void idListParse (int &index);
    void stringListParse (int &index);
    void ruleListParse (int &index);
    void ruleParse (int &index);
    void headPredicateParse (int &index);
    void predicateParse (int &index);
    void predicateListParse (int &index);
    void parameterParse (int &index);
    void parameterListParse (int &index);
    void queryParse (int &index);
    void queryListParse (int &index);

    void idListParse (int &index, Predicate &tempPredicate);
    void stringListParse (int &index, Predicate &tempFact);
    void headPredicateParse (int &index, Predicate &tempRule);
    void predicateParse (int &index, Rule &tempRule);
    void parameterParse (int &index, Predicate &tempPredicate);
    void parameterListParse (int &index, Predicate &tempPredicate);
    void predicateListParse (int &index, Rule &tempRule);
    void predicateParse (int &index, Predicate &tempPredicate);
    bool match(int &index, TokenType tempToken);
};

#endif //PROJECT1_STARTER_CODE_PARSER_H
