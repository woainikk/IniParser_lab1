//
// Created by Маргарита on 10.09.2017.
//



#ifndef LAB100P_INIPARSER_H
#define LAB100P_INIPARSER_H

#include <map>
#include "SectionNotFound.h"
#include "ParamNotFound.h"
using namespace std;

class IniParser
{
public:
    string fileName;
    IniParser( const string& f);
    IniParser();
    void printMap();
    bool isHaveASec(const string& sec_name );
    bool isHaveParam (const string &sec_name, const string& param_name);

    template<typename T>
    T GetValue(const string &section_name, const string &param_name)
    throw (SectionNotFound, ParamNotFound) ;



private:
    enum myType {STRING = 0, INT = 1, DOUBLE = 2 };
    map <string, map <string, pair < string, myType >>> mySections;
    string varName, varValue, sectionName;
    void searchSec (string s, int openIndex , int closeIndex);
    void searchVarName (string s, int equalIndex);
    void searchVarValue (string s, int equalIndex);
    myType getType (string myS);
    void readFile();


};

#endif //LAB100P_INIPARSER_H
