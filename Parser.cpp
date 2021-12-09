
//
// Created by ejh61 on 2021-09-23.
//

#include "Parser.h"
#include <iostream>


std::string Parser::toString () {
    std::ostringstream oss;

    for (unsigned int i = 0; i < tokens.size(); i++) {

        oss << tokens.at(i) << std::endl;
    }

    return oss.str();
}

void Parser::printDatalog () {
    std::cout << datalog.toString();
}


std::string Parser::datalogParse() {
    int i = 0;
    try {

        if (match(i,TokenType::SCHEMES)) {
            i++;
            if (match(i,TokenType::COLON)) {
                i++;
                schemeParse(i);
                schemeListParse(i);
                if (match(i,TokenType::FACTS)) {
                    i++;
                    if (match(i,TokenType::COLON)) {
                        i++;
                        factListParse(i);
                        if (match(i,TokenType::RULES)) {
                            i++;
                            if (match(i,TokenType::COLON)) {
                                i++;
                                ruleListParse(i);
                                if (match(i,TokenType::QUERIES)) {
                                    i++;
                                    if (match(i,TokenType::COLON)){
                                        i++;
                                        queryParse(i);
                                        queryListParse(i);
                                        if (match(i,TokenType::_EOF)){

                                            std::string tempString = "Success!";
                                            return tempString;

                                        } else throw i;
                                    }else throw i;
                                } else throw i;
                            } else throw i;
                        } else throw i;
                    } else throw i;
                } else throw i;
            } else throw i;
        } else throw i;
    }
    catch (int index) {
        std::ostringstream oss;
        oss << "Failure!" << std::endl;
        oss << "  (" << tokens.at(index)->dayToString(tokens.at(index)->getTokenType()) << ",\"" << tokens.at(index)->getDescription() << "\","
            << tokens.at(index)->getLine() <<")";
        return oss.str();
    }
}


void Parser::schemeListParse(int &index){

    if (match(index,TokenType::ID)){
        schemeParse(index);
        schemeListParse(index);
    }
    else {
        return;
    }
}

void Parser::factListParse(int &index) {

    if (match(index,TokenType::ID)) {
        factParse(index);
        factListParse(index);
    }
    else {
        return;
    }
}

void Parser::ruleListParse (int &index) {

    if(match(index,TokenType::ID)) {
        ruleParse(index);
        ruleListParse(index);
    }
    else return;
}

void Parser::queryListParse (int &index) {

    if (match(index,TokenType::ID)) {
        queryParse(index);
        queryListParse(index);
    }
    else return;
}


void Parser::schemeParse (int &index) {

    if(match(index,TokenType::ID)) {
        Predicate tempScheme(tokens.at(index)->getDescription());
        index++;
        if (match(index,TokenType::LEFT_PAREN)) {
            index++;
            if (match(index,TokenType::ID)){
                tempScheme.setID(tokens.at(index)->getDescription());
                index++;
                idListParse(index, tempScheme);
                if(match(index,TokenType::RIGHT_PAREN)){

                    datalog.setScheme(tempScheme);
                    index++;
            }
            else throw index;

        }
        else throw index;

    }
    else throw index;
}
else throw index;
}

void Parser::factParse (int &index) {
    if (match(index,TokenType::ID)) {
        Predicate tempFact(tokens.at(index)->getDescription());
        index ++;
        if(match(index,TokenType::LEFT_PAREN)){
            index ++;
            if(match(index,TokenType::STRING)) {
                tempFact.setString(tokens.at(index)->getDescription()); // string datalog에 집어넣자 우리 (string list 참조)
                index++;
                stringListParse(index, tempFact);
                if(match(index,TokenType::RIGHT_PAREN)){
                    index++;
                    if (match(index,TokenType::PERIOD)) {
                        datalog.setFact(tempFact);
                        index++;
                    }
                    else throw index;

                }
                else throw index;
            }
            else throw index;
        }
        else throw index;
    }
    else throw index;
}

void Parser::ruleParse (int &index) {
    Predicate tempPredicate;
    headPredicateParse(index, tempPredicate);

    Rule tempRule(tempPredicate);

    if(match(index,TokenType::COLON_DASH)){
        index++;
        predicateParse(index,tempRule);
        predicateListParse(index, tempRule);
        if(match(index,TokenType::PERIOD)){
            datalog.setRule(tempRule);
            index++;
        }
        else throw index;
    }
    else throw index;
}

void Parser::queryParse (int &index) {
    Predicate tempPredicate;
    predicateParse(index, tempPredicate);

    if (match(index,TokenType::Q_MARK)){
        index++;

        datalog.setQuery(tempPredicate);
    }
    else throw index;
}


void Parser::headPredicateParse (int &index, Predicate &tempPredicate) {

    if (match(index,TokenType::ID)) {
        tempPredicate.setMainID(tokens.at(index)->getDescription());
        index++;
        if (match(index,TokenType::LEFT_PAREN)){
            index++;
            if(match(index,TokenType::ID)){
                tempPredicate.setID(tokens.at(index)->getDescription());
                index++;
                idListParse(index, tempPredicate);
                if(match(index,TokenType::RIGHT_PAREN)) {
                    index++;
                }
                else throw index;
            }
            else throw index;
        }
        else throw index;
    }
    else throw index;
}

void Parser::predicateParse (int &index, Rule &tempRule) {
    Predicate tempPredicate;

    if (match(index,TokenType::ID)) {
        tempPredicate.setMainID(tokens.at(index)->getDescription());
        index++;
        if (match(index,TokenType::LEFT_PAREN)) {
            index++;
            parameterParse(index, tempPredicate);
            parameterListParse(index, tempPredicate);
            if(match(index,TokenType::RIGHT_PAREN)) {
                tempRule.setPredicateList(tempPredicate);
                index++;
            }
            else throw index;
        }
        else throw index;
    }
    else throw index;
}

void Parser::predicateParse (int &index, Predicate &tempPredicate) {
    if (match(index,TokenType::ID)) {
        tempPredicate.setMainID(tokens.at(index)->getDescription());
        index++;
        if (match(index,TokenType::LEFT_PAREN)) {
            index++;
            parameterParse(index, tempPredicate);
            parameterListParse(index, tempPredicate);
            if(match(index,TokenType::RIGHT_PAREN)) {
                index++;
            }
            else throw index;
        }
        else throw index;
    }
    else throw index;
}

void Parser::predicateListParse (int &index, Rule &tempRule) {

    if (match(index,TokenType::COMMA)) {
        index++;
        predicateParse(index, tempRule);
        predicateListParse(index, tempRule);
    }
    else return;
}

void Parser::parameterListParse (int &index, Predicate &tempPredicate) {

    if(match(index,TokenType::COMMA)) {
        index ++;
        parameterParse(index, tempPredicate);
        parameterListParse(index, tempPredicate);
    }
    else return;
}

void Parser::stringListParse (int &index, Predicate &tempFact) {
    if(match(index,TokenType::COMMA)) {
        index++;
        if (match(index,TokenType::STRING)){
            tempFact.setString(tokens.at(index)->getDescription());
            index ++;
            stringListParse(index, tempFact);
        }
        else throw index;
    }
    else {
        return;
    }
}

void Parser::idListParse (int &index, Predicate &tempPredicate) {

    if (match(index,TokenType::COMMA)){
        index++;
        if(match(index,TokenType::ID)) {
            tempPredicate.setID(tokens.at(index)->getDescription());
            index++;
            idListParse(index, tempPredicate);
        }
        else throw index;
    }
    else {
        return;
    }
}

void Parser::parameterParse (int &index, Predicate &tempPredicate) {
    if(match(index,TokenType::STRING)){

        tempPredicate.setString(tokens.at(index)->getDescription());
        index++;
    }
    else if (match(index,TokenType::ID)){

        tempPredicate.setID(tokens.at(index)->getDescription());
        index++;
    }
    else throw index;
}

bool Parser::match(int &index, TokenType tempToken) {
    while (tokens.at(index)->getTokenType()  ==  TokenType::COMMENT ) {
        index++;
    }
    if (tokens.at(index)->getTokenType() == tempToken) {
        return true;
    }
    else {
        return false;
    }
}
