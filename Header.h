//
// Created by ejh61 on 2021-10-26.
//

#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H

#include <vector>
#include <string>
#include <sstream>

class Header {
private:
    std::vector <std::string> attributes;

public:
    Header (std::string attribute){
        attributes.push_back(attribute);
    }
    Header() {}
    ~ Header (){ }

    void SetHeader (std::string attribute);

    std::vector<std::string> &GetHeader ();

    unsigned int headerSize() {
        return attributes.size();
    }

    std::string toString ();
};


#endif //PROJECT1_STARTER_CODE_HEADER_H
