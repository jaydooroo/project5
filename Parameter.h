//
// Created by ejh61 on 2021-09-25.
//

#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H
#include <string>
#include <sstream>

class Parameter {
private:
    std::string ID;
    std::string STRING;

    std::string choice;
public:

    Parameter(std::string tempChoice, std::string tempString);
    ~Parameter() {}

    std::string getChoice () {
        return choice;
    }

    std::string toString();


};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H
