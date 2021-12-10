//
// Created by ejh61 on 2021-10-27.
//

#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"
#include <iostream>
#include <algorithm>
class Interpreter {
private:
    DatalogProgram datalog;
    Database database;

public:
    Interpreter(DatalogProgram &tempDatalog){
        datalog = tempDatalog;
        makesDatabase();
    }
    ~ Interpreter() {}

    void makesDatabase();

    std::string initiateQueries ();

    Relation applyQuery (Predicate query);  // Predicate query를 database에 적용해서 Relation으로 만들어 반환시켜줌.

    std::string toString () {
        return database.toString(); // database 값들 축력
    }

    std::string initiateRules ();

    Relation applyRule (Predicate ruleToApply); // 하나의 룰을 가지고 database의 값들을 적용해서 relation으로 만들어 변환시켜줌.

    std::vector<std::set<int>> findSCCs(Graph &forwardGraph);

    void DFS_postOrder(Graph &graph, std::vector<bool> &isVisited, int startNode,std::vector<int> &postOrder);

    std::vector<int> DFSF_postOrder(Graph &graph);

    void reversePostOrder (std::vector<int> &postOrder);

    std::vector<std::set<int>> DFSF_trees(Graph &graph, std::vector<int> &postOrder);

    void DFS_trees (Graph &graph, std::vector<bool> &isVisited, int startNode, std::set<int> &SCC);

    std::string EvaluateSCCRules ();

    std::string fixedPoint(std::set<int> SCC,bool isSelfDependant);

    void printGraph (Graph &graph);
};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
