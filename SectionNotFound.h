//
// Created by Маргарита on 12.09.2017.
//

#ifndef LAB100P_INITIALIZEEXCEPTION_H
#define LAB100P_INITIALIZEEXCEPTION_H

#include <iostream>

using namespace std;

class SectionNotFound : exception {
public:
    SectionNotFound(const char* section);
    const char *what() const noexcept;
private:
    const char* incorrectSection;
};


#endif //LAB100P_INITIALIZEEXCEPTION_H
