//
// Created by Маргарита on 10.09.2017.
//
#pragma once

#include <map>
#include "SectionNotFound.h"
#include "ParamNotFound.h"

class IniParser
{
public:
    std::string fileName;
    IniParser( const std::string& f);
    IniParser();
    void printMap();
    bool isHaveASec(const std::string& sec_name );
    bool isHaveParam (const std::string &sec_name, const std::string& param_name);

    template<typename T>
    T GetValue(const std::string &sectionName, const std::string &paramName)
    throw (SectionNotFound, ParamNotFound) ;


private:
    enum typesOfValues {STRING = 0, INT = 1, DOUBLE = 2 };
    std::map <std::string, std::map <std::string, std::pair < std::string, typesOfValues >>> mySections;
    std::string varName, varValue, sectionName;
    void searchSec (const std::string &s, int openIndex , int closeIndex);
    void searchVarName (std::string s, int equalIndex);
    void searchVarValue (std::string s, int equalIndex);
    void removeSpaces(std::string &s);
    void removeComments (std::string &s);
    typesOfValues getTypeOfValue(std::string myS);
    void readFile();


};

