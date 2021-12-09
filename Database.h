//
// Created by ejh61 on 2021-10-26.
//

#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H
#include "Relation.h"
#include <map>

class Database {
private:

    std::map<std::string,Relation> database;

public:
    Database (std::string name, Relation relation) {
        database.insert(std::pair<std::string,Relation>(name,relation));
    }
    Database () {}
    ~Database() {}

    void insertRelation (std::string name, Relation relation) {
        database.insert(std::pair<std::string,Relation>(name,relation));
    }

    unsigned int databaseTuplesSize();

    Relation &getRelation (std:: string name);

    std::string toString ();

};


#endif //PROJECT1_STARTER_CODE_DATABASE_H
