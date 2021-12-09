//
// Created by ejh61 on 2021-09-25.
//

#include "DatalogProgram.h"

void DatalogProgram::setFact (Predicate tempFact) {
    fact.push_back(tempFact);

    for (unsigned int i = 0; i < tempFact.returnParameter().size(); i++) {

        domain.insert(tempFact.returnParameter().at(i).toString());
    }
}

std::string DatalogProgram::toString () {
    std::ostringstream oss;

    oss << "Schemes(" << scheme.size() << "):" << std::endl;

    for (unsigned int i = 0; i < scheme.size(); i++) {
        oss << "  " << scheme.at(i).toString() << std::endl;
    }

    oss << "Facts(" << fact.size() << "):" << std::endl;

    for (unsigned int i = 0; i < fact.size(); i++) {
        oss << "  " << fact.at(i).toString() << "." << std::endl;
    }

    oss << "Rules(" << rule.size() << "):" << std::endl;

    for (unsigned int i = 0; i < rule.size(); i++) {
        oss <<"  " << rule.at(i).toString() << std::endl;
    }

    oss <<"Queries(" << query.size() << "):" << std::endl;

    for (unsigned int i = 0; i < query.size(); i++) {

        oss << "  " << query.at(i).toString() << "?" <<std::endl;
    }

    oss << "Domain(" << domain.size() << "):" << std::endl;

    std::set<std::string>::iterator iter;

    for (iter = domain.begin(); iter != domain.end(); iter++) {
        oss << "  " << *iter << std::endl;
    }

    return oss.str();

}

std::map<int, std::set<int>> DatalogProgram::dependencyGraph () {

    std::map<int,std::set<int>> graph;
    for (unsigned int i = 0; i < rule.size(); i++) { // i는 전체적으로 한번 도는거
        std::set<int> adjacency;
        for (unsigned int h = 0; h < rule.at(i).getPredicateList().size(); h++){ // h는 parameter list도는 용도
            for(unsigned int j = 0; j < rule.size(); j++) {   // j는 전체한번 도는 용도
                if (rule.at(i).getPredicateList().at(h).returnID() == rule.at(j).getPredicate().returnID()) {
                    adjacency.insert(j);  // h마다 한번씩 headpredicate ID 랑 비교해서 맞으면 추가
                }
            }
        }

        graph[i] = adjacency;

    }

    return graph;
}

