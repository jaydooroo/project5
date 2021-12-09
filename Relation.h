//
// Created by ejh61 on 2021-10-26.
//

#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <string>
#include <set>
#include <sstream>

class Relation {

private:
    std::string name;
    Header header;
    std::set<Tuple> tuples;

public:

    Relation (std::string tempName, Header tempHeader) {
        name = tempName;
        header = tempHeader;
    }
    Relation(std::string tempName) {
        name = tempName;
    }

    Relation() {}
    ~Relation() { }

    void setName (std::string tempName) {
        name = tempName;
    }

    std::string getName () {
        return name;
    }

    void addTuple (Tuple tempTuple);

    Header getHeader () {
        return header;
    }

    int tupleSize () {
        return tuples.size();
    }
    std::set<Tuple> getTuples () {
        return tuples;
    }



    Relation selectValue (unsigned int index, std::string value);   // parameters are index and value

    Relation select(unsigned int index1, unsigned int index2);  // parameters are index and index?? 만약 attributes가 같은값이 있는게 있을때 같은 값인 경우에만 relation에추가해서 반환

    Relation project ( std::vector<unsigned int> indices);

    Relation rename (std::vector<std::string> attributes);

    Relation naturalJoin(Relation &tempRelation);

    Header combineHeader(Header tempHeader, std::vector<std::pair<unsigned int, unsigned int >> &tempNumbers);

    bool isJoinable (Tuple &compareTuples1,Tuple &compareTuples2,std:: vector<std::pair<unsigned  int, unsigned  int>> &tempNumbers);

    Tuple combineTuples (Tuple compareTuples1, Tuple compareTuples2, std:: vector<std::pair<unsigned int, unsigned int>> &tempNumbers);

    void unionRelations (Relation &tempRelation);

    std::string toString();

};


#endif //PROJECT1_STARTER_CODE_RELATION_H
