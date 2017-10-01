//
// Created by Маргарита on 12.09.2017.
//

#ifndef LAB100P_PARAMNOTFOUND_H
#define LAB100P_PARAMNOTFOUND_H

#include <string>
#include <iostream>
#include "ParamNotFound.h"

using namespace std;

class ParamNotFound : exception {
public:
    ParamNotFound(const char* param);

    const char *what() const noexcept;
private:
    const char* incorrectParam;
};


#endif //LAB100P_PARAMNOTFOUND_H
