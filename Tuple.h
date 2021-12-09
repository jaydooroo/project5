//
// Created by ejh61 on 2021-10-26.
//

#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H

#include <vector>
#include <string>
#include <sstream>

class Tuple {

private:
    std::vector<std::string> values;

public:
    Tuple (std::string value) {
        values.push_back(value);
    }
    Tuple() {}

    ~Tuple() {}

   void SetTuple (std::string value);

    std::vector<std::string> &getTuple ();

    bool operator == (const Tuple &rhs) const {
        return values == rhs.values;
    }

    bool operator < (const Tuple &rhs) const{
        return values < rhs.values;
    }

    std::string toString ();

};


#endif //PROJECT1_STARTER_CODE_TUPLE_H
