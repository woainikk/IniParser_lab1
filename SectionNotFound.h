//
// Created by Маргарита on 12.09.2017.
//

#ifndef LAB100P_INITIALIZEEXCEPTION_H
#define LAB100P_INITIALIZEEXCEPTION_H

using namespace std;

class SectionNotFound : exception {
public:
    SectionNotFound (const string & s);

};


#endif //LAB100P_INITIALIZEEXCEPTION_H
