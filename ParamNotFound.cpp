//
// Created by Маргарита on 19.09.2017.
//
#include <string>
#include <iostream>
#include "ParamNotFound.h"
using namespace std;

ParamNotFound::ParamNotFound(const string &p) {
    cout << "Can not find parameter " << p << endl;
}