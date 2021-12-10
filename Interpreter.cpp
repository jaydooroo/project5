//
// Created by ejh61 on 2021-10-27.
//

#include "Interpreter.h"


void Interpreter::makesDatabase() {  //일일이 튜플과 헤더 만들어서 relation 만들고 database 만들어야함
    for(unsigned int i = 0; i < datalog.getSchemes().size(); i++){

        Header tempHeader;
        for(unsigned int j = 0; j < datalog.getSchemes().at(i).returnParameter().size(); j++){   // 헤더에 attribute저장
            tempHeader.SetHeader(datalog.getSchemes().at(i).returnParameter().at(j).toString());
        }
        Relation tempRelation ( datalog.getSchemes().at(i).returnID(), tempHeader);  // relation creation

        for(unsigned int j = 0; j < datalog.getFacts().size(); j++) {  // tuple에서 중복이 있으면 어떡하나?
            if(datalog.getFacts().at(j).returnID() == datalog.getSchemes().at(i).returnID()) {   // ID가 같은 tuple 있을시
                Tuple tempTuple;
                for (unsigned int h = 0; h < datalog.getFacts().at(j).returnParameter().size(); h++){
                    tempTuple.SetTuple(datalog.getFacts().at(j).returnParameter().at(h).toString()); // 하나의 튜플에 값들 저장
                }
                tempRelation.addTuple(tempTuple);  // relation에 튜플 추가
            }
        }

        database.insertRelation(datalog.getSchemes().at(i).returnID(),tempRelation); //database 에 추가
    }
}

std::string Interpreter::initiateQueries () {
    std::ostringstream oss;
    for (unsigned int i = 0; i < datalog.getQueries().size(); i++) {
        Relation tempRelation = applyQuery(datalog.getQueries().at(i));

        oss << datalog.getQueries().at(i).toString() << "? ";
        //oss << datalog.getQueries().at(i).returnID() << "("
        // <<database.getRelation(datalog.getQueries().at(i).returnID()).getHeader().toString() << ")? ";
        if (tempRelation.tupleSize() == 0) {
            oss << "No" << std::endl;
        }
        else {
            oss << "Yes(" << tempRelation.tupleSize() << ")" << std::endl;
        }

        oss << tempRelation.toString();
    }
    return oss.str();
}

Relation Interpreter::applyQuery (Predicate query) {   // 한개의 query 만적용

    Relation tempRelation = database.getRelation(query.returnID());
    std::vector <std::string> attributes;
    std::vector <unsigned int> indices;

    for (unsigned int i = 0; i < query.returnParameter().size(); i++) {
        if (query.returnParameter().at(i).getChoice() == "STRING"){
            tempRelation = tempRelation.selectValue(i,query.returnParameter().at(i).toString()); // string 값과 같은것을 골라내는 작업

        } else {
            try {
                for (unsigned int j = 0; j < i; j++) {   // if there is at least one same attributes
                    if (query.returnParameter().at(j).toString() == query.returnParameter().at(i).toString()) {
                        throw j;
                    }
                }
                attributes.push_back(query.returnParameter().at(i).toString());  // save for the later project and rename
                indices.push_back(i);
            }
            catch(unsigned int j) {
                tempRelation = tempRelation.select(j,i); // ??
            }
            //adds
        }
    }
    tempRelation = tempRelation.project(indices);
    tempRelation = tempRelation.rename(attributes);

    return tempRelation;
}

std::string Interpreter::initiateRules () {
    std::ostringstream oss;
    unsigned int databaseTupleSize;
    unsigned int countLoop = 0;

    oss << "Rule Evaluation" << std::endl;

do {
     databaseTupleSize = database.databaseTuplesSize();
    for (unsigned int i = 0; i < datalog.getRules().size(); i++) { // go over every rules in the data base

        oss << this->datalog.getRules().at(i).toString() << std::endl;

        Relation result;  // Relation which will be updated as it is used to apply relation rule and join.

        for (unsigned int j = 0;
             j < datalog.getRules().at(i).getPredicateList().size(); j++) {  //go over every predicate list in a rule
            // get a relation by applying a predicate from a rule into the database
            Relation tempRelation = applyRule(datalog.getRules().at(i).getPredicateList().at(j)); // 나중에 포인터 쓸수 있음 쓰기

            if (j == 0) {
                result = tempRelation;
            } else {
                result = result.naturalJoin(tempRelation); // result 안에 stringID(즉 relation 이름이 없음)없음
            }

        }
        // 헤드 predicate에 있는 ID 값 넣어드림, 즉 relation 이름 넣음
        result.setName(datalog.getRules().at(i).getPredicate().returnID());
        // 헤드 predicate에 있는대로 Project해서 넣어야함.

        std::vector<unsigned int> indices;

        // result attributes중에 헤드 predicate attributes와 일치하는 것들이 어디있는 지 찾은다음 그 번호를 vector에 저장
        for (unsigned int j = 0; j < datalog.getRules().at(i).getPredicate().returnParameter().size(); j++) {

            for (unsigned int h = 0; h < result.getHeader().headerSize(); h++) {
                if (datalog.getRules().at(i).getPredicate().returnParameter().at(j).toString() ==
                    result.getHeader().GetHeader().at(h)) {
                    indices.push_back(h); //여기서 어떻게 새로운 relation 순서 상관할 필요없음, project에서 알아서 해줌
                }
            }
        }
        // result에서 필요한 부분만 project
         result = result.project(indices);

        for (unsigned int x = 0; x < datalog.getSchemes().size() ;x++) {
            if(datalog.getSchemes().at(x).returnID() == datalog.getRules().at(i).getPredicate().returnID()){
                std::vector<std::string> attributes;   // attribute 이름 똑같이 변경하기
                for(unsigned int j = 0; j <datalog.getSchemes().at(x).returnParameter().size(); j++) {
                    attributes.push_back(datalog.getSchemes().at(x).returnParameter().at(j).toString());
                }
                result = result.rename(attributes);
            }
        }

        Relation tempResult(result.getName(),result.getHeader());
        for(Tuple t: result.getTuples()){
            unsigned int count = 0;
            for (Tuple x: database.getRelation(result.getName()).getTuples()){
                if(t == x) {
                    count ++;
                }
            }
            if (count == 0) {
                tempResult.addTuple(t);
            }
        }


        oss << tempResult.toString();

        // 지금 있는 데이터베이스에 result값 대입
        this->database.getRelation(result.getName()).unionRelations(result);


    }
    countLoop++;
} while(databaseTupleSize != database.databaseTuplesSize());


oss << std::endl << "Schemes populated after " << countLoop << " passes through the Rules." << std::endl << std::endl;

    return oss.str();

}

Relation Interpreter::applyRule (Predicate ruleToApply) {

    Relation tempRelation = database.getRelation(ruleToApply.returnID()); // database에서 ID랑 같은 값들의 Tuples 모아서 relation 만들어서 넣기.
    std::vector <std::string> attributes;  // attribute의 새이름들
    std::vector <unsigned int> indices; //project할 attribute 들

    for (unsigned int i = 0; i < ruleToApply.returnParameter().size(); i++) {
        if (ruleToApply.returnParameter().at(i).getChoice() == "STRING"){
            tempRelation = tempRelation.selectValue(i,ruleToApply.returnParameter().at(i).toString()); // string 값과 같은것을 골라내는 작업

        } else {
            try {
                for (unsigned int j = 0; j < i; j++) {   // if there is at least one same variable
                    if (ruleToApply.returnParameter().at(j).toString() == ruleToApply.returnParameter().at(i).toString()) {
                        throw j;
                    }
                }
                attributes.push_back(ruleToApply.returnParameter().at(i).toString());  // save for the later project and rename
                indices.push_back(i);
            }
            catch(unsigned int j) {
                tempRelation = tempRelation.select(j,i);
            }
            //adds
        }
    }
    tempRelation = tempRelation.project(indices);
    tempRelation = tempRelation.rename(attributes);

    return tempRelation;

}

std::vector<std::set<int>> Interpreter::findSCCs(Graph &forwardGraph) {


    forwardGraph = datalog.dependencyGraph(); // init dependency Graph

    printGraph(forwardGraph); // print forwardGraph

    Graph reverseGraph = forwardGraph.reverseGraph(); // init reverse graph

    std::vector<int> postOrder = DFSF_postOrder(reverseGraph); // calculate post order of reverse graph

    reversePostOrder(postOrder); // reverse postOrder;

    return DFSF_trees(forwardGraph, postOrder); // calculate SCC and return it.

}

void Interpreter::DFS_postOrder(Graph &graph, std::vector<bool> &isVisited, int startNode, std::vector<int> &postOrder) {
    for(int elem: graph.getGraph()[startNode]) {
        if (isVisited.at(elem) == false) {
            isVisited.at(elem) = true;
            DFS_postOrder(graph, isVisited, elem, postOrder);
            postOrder.push_back(elem);
        }
    }
}

std::vector<int> Interpreter::DFSF_postOrder (Graph &graph) {
    std::vector<bool> isVisited(graph.getGraph().size(), false);
    std::vector<int> postOrder;

    for(unsigned int i = 0; i < graph.getGraph().size(); i++) {
        if(isVisited.at(i) == false) {
            isVisited.at(i) = true;
            DFS_postOrder(graph,isVisited,(int)i,postOrder);
            postOrder.push_back(i);
        }
    }

    return postOrder;
}

void Interpreter::reversePostOrder (std::vector<int> &postOrder) {
    std::reverse(postOrder.begin(), postOrder.end());
}

std::vector<std::set<int>> Interpreter::DFSF_trees(Graph &graph, std::vector<int> &postOrder) {
    std::vector<bool> isVisited(graph.getGraph().size(), false);

    std::vector<std::set<int>> SCCs;

    for(int i = 0; i < (int)postOrder.size(); i++) {
        std::set<int> SCC;
        if(isVisited.at(postOrder.at(i)) == false) {
            isVisited.at(postOrder.at(i)) = true;
            SCC.insert(postOrder.at(i));
            DFS_trees(graph,isVisited,postOrder.at(i),SCC);
        }
        if(SCC.size()>0) {
            SCCs.push_back(SCC);
        }
    }
    return SCCs;
}

void Interpreter::DFS_trees (Graph &graph, std::vector<bool> &isVisited, int startNode, std::set<int> &SCC) {
    for (int elem: graph.getGraph()[startNode]) {
        if(isVisited.at(elem) == false) {
            isVisited.at(elem) = true;
            SCC.insert(elem);
            DFS_trees(graph,isVisited,elem,SCC);
        }
    }
}

std::string Interpreter::EvaluateSCCRules () {
    Graph forwardGraph;
    std::vector<std::set<int>> SCCs = findSCCs(forwardGraph);
    std::stringstream oss;
    oss << "Rule Evaluation" << std::endl;

    for (std::set<int> SCC: SCCs) {
        bool isSelfDependant = false;
        if(SCC.size() == 1) {
            for(int elem1: SCC) {
               std::set<int> edges = forwardGraph.getEdge(elem1);
               for(int elem2: edges) {
                   if(elem2 == elem1) {
                       isSelfDependant = true;
                   }
               }
            }
        }

        oss <<"SCC: ";
        for(int elem: SCC) {
            oss << "R" << elem << ",";
        }
        if (SCC.size() > 0)
            oss.seekp(-1,oss.cur);
        oss << std::endl;
        oss << fixedPoint(SCC,isSelfDependant);
        for(int elem: SCC) {
            oss << "R" << elem << ",";
        }
        if (SCC.size() > 0)
            oss.seekp(-1,oss.cur);
        oss << std::endl;
    }

    return oss.str();
}

std::string Interpreter::fixedPoint(std::set<int> SCC, bool isSelfDependant) {
    std::ostringstream oss;
    unsigned int databaseTupleSize;
    unsigned int countLoop = 0;
    bool isDependent = false;
    if(SCC.size() > 1)
        isDependent = true;

    do {
        databaseTupleSize = database.databaseTuplesSize();
        for (int elem: SCC) { // go over every rules in the data base

            oss << this -> datalog.getRules().at(elem).toString() << std::endl;

            Relation result;  // Relation which will be updated as it is used to apply relation rule and join.

            for (unsigned int j = 0;
                 j < datalog.getRules().at(elem).getPredicateList().size(); j++) {  //go over every predicate list in a rule
                // get a relation by applying a predicate from a rule into the database
                Relation tempRelation = applyRule(datalog.getRules().at(elem).getPredicateList().at(j)); // 나중에 포인터 쓸수 있음 쓰기

                if (j == 0) {
                    result = tempRelation;
                } else {
                    result = result.naturalJoin(tempRelation); // result 안에 stringID(즉 relation 이름이 없음)없음
                }
            }
            // 헤드 predicate에 있는 ID 값 넣어드림, 즉 relation 이름 넣음
            result.setName(datalog.getRules().at(elem).getPredicate().returnID());
            // 헤드 predicate에 있는대로 Project해서 넣어야함.

            std::vector<unsigned int> indices;

            // result attributes중에 헤드 predicate attributes와 일치하는 것들이 어디있는 지 찾은다음 그 번호를 vector에 저장
            for (unsigned int j = 0; j < datalog.getRules().at(elem).getPredicate().returnParameter().size(); j++) {

                for (unsigned int h = 0; h < result.getHeader().headerSize(); h++) {
                    if (datalog.getRules().at(elem).getPredicate().returnParameter().at(j).toString() ==
                        result.getHeader().GetHeader().at(h)) {
                        indices.push_back(h); //여기서 어떻게 새로운 relation 순서 상관할 필요없음, project에서 알아서 해줌
                    }
                }
            }
            // result에서 필요한 부분만 project
            result = result.project(indices);

            for (unsigned int x = 0; x < datalog.getSchemes().size() ;x++) {
                if(datalog.getSchemes().at(x).returnID() == datalog.getRules().at(elem).getPredicate().returnID()){
                    std::vector<std::string> attributes;   // attribute 이름 똑같이 변경하기
                    for(unsigned int j = 0; j <datalog.getSchemes().at(x).returnParameter().size(); j++) {
                        attributes.push_back(datalog.getSchemes().at(x).returnParameter().at(j).toString());
                    }
                    result = result.rename(attributes);
                }
            }

            Relation tempResult(result.getName(),result.getHeader());
            for(Tuple t: result.getTuples()){
                unsigned int count = 0;
                for (Tuple x: database.getRelation(result.getName()).getTuples()){
                    if(t == x) {
                        count ++;
                    }
                }
                if (count == 0) {
                    tempResult.addTuple(t);
                }
            }


            oss << tempResult.toString();

            // 지금 있는 데이터베이스에 result값 대입
            this->database.getRelation(result.getName()).unionRelations(result);


        }
        countLoop++;
    } while(databaseTupleSize != database.databaseTuplesSize() && (isDependent || isSelfDependant) );


    oss  << countLoop << " passes: ";

    return oss.str();


}

void Interpreter::printGraph (Graph &graph) {
std::stringstream oss;
    oss << "Dependency Graph" << std::endl;
    for(unsigned int i = 0; i < graph.getGraph().size(); i++) {
        oss << "R" << i << ":";
        for(int elem: graph.getGraph()[i]) {
            oss << "R" << elem << ",";
        }
        if (graph.getGraph()[i].size() > 0)
            oss.seekp(-1,oss.cur);
        oss << std::endl;
    }

    oss << std::endl;

    std::cout << oss.str();
}