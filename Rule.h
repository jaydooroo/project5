//
// Created by ejh61 on 2021-09-25.
//

#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H
#include "Predicate.h"
#include <vector>
#include <sstream>


class Rule {
private:
    Predicate headPredicate;
    std::vector <Predicate> predicateList;


public:

    Rule(Predicate tempHead): headPredicate(tempHead) { }

    ~Rule() {}

    void setPredicateList (Predicate tempPredicate) {
        predicateList.push_back(tempPredicate);
    }

    Predicate getPredicate () {
        return headPredicate;
    }
    std::vector<Predicate> &getPredicateList () {
        return predicateList;
    }

    std::string toString ();

};


#endif //PROJECT1_STARTER_CODE_RULE_H
