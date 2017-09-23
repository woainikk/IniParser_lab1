//
// Created by Маргарита on 19.09.2017.
//

#include <string>
#include <iostream>
#include "SectionNotFound.h"
using namespace std;

SectionNotFound::SectionNotFound(const string &s) {
    cout << "Can not find section " << s << endl;
}