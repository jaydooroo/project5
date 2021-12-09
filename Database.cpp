//
// Created by ejh61 on 2021-10-26.
//

#include "Database.h"

Relation &Database::getRelation (std::string name) {
    return database[name];
}
unsigned int Database::databaseTuplesSize(){
    unsigned int tuplesSize = 0;
    std::map<std::string, Relation>::iterator iter;

    for(iter = database.begin(); iter != database.end(); iter++) {
        tuplesSize += iter->second.tupleSize();
    }

    return tuplesSize;
}

std::string Database::toString () {
    std::ostringstream oss;
    std::map<std::string, Relation>::iterator iter;

    for(iter = database.begin(); iter != database.end(); iter++){
        oss << "Key: " << iter ->first << "value " << std::endl << iter->second.toString() << std::endl;
    }
    return oss.str();
}