    //
// Created by ejh61 on 2021-09-25.
//

#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include <vector>
#include <set>
#include <map>

class DatalogProgram {
private:
    std::vector <Predicate> scheme;
    std::vector<Predicate> fact;
    std::vector<Rule> rule;
    std::vector<Predicate> query;
    std::set<std::string> domain;

public:

    DatalogProgram() { }

   void setScheme (Predicate tempScheme) {
        scheme.push_back(tempScheme);
    }

    void setFact (Predicate tempFact) ;

    void setRule (Rule tempRule) {
        rule.push_back(tempRule);
    }

    void setQuery (Predicate tempQuery) {
        query.push_back(tempQuery);
    }

    std::vector<Predicate> &getSchemes () {
        return scheme;
    }

    std::vector<Predicate> &getFacts () {
        return fact;
    }

    std::vector<Rule> &getRules () {
        return rule;
    }

    std::vector<Predicate> &getQueries () {
        return query;
    }

    std::string toString ();

    std::map<int, std::set<int>> dependencyGraph ();


};


#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
