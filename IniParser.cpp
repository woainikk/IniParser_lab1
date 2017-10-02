//
// Created by Маргарита on 10.09.2017.
//

#include "IniParser.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdio.h>
#include "SectionNotFound.h"
#include "ParamNotFound.h"


IniParser::IniParser() {}

IniParser::IniParser(const std::string &f) {
    fileName = f;
    IniParser::readFile();
}


void IniParser::searchSec(const std::string &s, int openIndex, int closeIndex) {
    int i = 0;
    while (i < openIndex) {
        if (s[i] == ' ') {
            i++;
        } else {
            throw std::runtime_error("Incorrect file syntax.");
        }
    }

    if (i == openIndex) {
        sectionName = s.substr(openIndex + 1, closeIndex - openIndex - 1);

    }
}


bool IniParser::isHaveASec(const std::string &secName) {
    return mySections.find(secName) != mySections.end();
}

bool IniParser::isHaveParam(const std::string &secName, const std::string &paramName) {

    return mySections.at(secName).count(paramName) == 1;
}


void IniParser::searchVarName(std::string s, int equalIndex) {
    int p = 0;
    varName = "";
    while (p < equalIndex && s[p] == ' ') {
        p++;
    }
    while (p < equalIndex and ((s[p] >= 'A' and s[p] <= 'Z') or (s[p] >= 'a' and s[p] <= 'z'))) {
        varName += s[p];
        p++;
    }


}


void IniParser::searchVarValue(std::string s, int equalIndex) {
    int p = equalIndex + 1;
    varValue = "";
    while (p < s.size() && s[p] == ' ') {
        p++;
    }
    while (p < s.size() && (s[p] != ' ')) {
        varValue += s[p];
        p++;
    }

}


IniParser::myType IniParser::getType(std::string myS) {
    int dotCount = 0;
    int numCount = 0;
    for (int i = 0; i < myS.size(); i++) {
        if (myS[i] == '.' && i != 0 && i != myS.size() - 1) {
            dotCount++;
        }
        if (myS[i] >= '0' && myS[i] <= '9') {
            numCount++;
        }
    }
    if (myS.size() == numCount) {
        return INT;
    } else if (myS.size() - 1 == numCount && dotCount == 1) {
        return DOUBLE;
    } else {
        return STRING;
    }
}


void IniParser::printMap() {
    for (auto it : mySections) {
        std::cout << it.first << ": " <<std::endl;
        std::map<std::string, std::pair<std::string, myType >> &myInnerMap = it.second;
        for (auto it2: myInnerMap) {
            std::cout << it2.first << " = " << it2.second.first << ". Type:"
                 << it2.second.second << std::endl;
        }
        std::cout << std::endl;
    }
}

void IniParser::readFile() {

    std::string s;
    std::ifstream file(fileName);
    if (!file.good()) {
        throw std::runtime_error("This file does not exist.");
    }


    while (!file.eof()) {
        getline(file, s);
        int openIndex = s.find('[');
        int closeIndex = s.find(']');
        int equalIndex = s.find('=');
        int commentIndex = s.find(';');
        if (commentIndex != -1) {
            s.erase(commentIndex, s.length());
        }
        if (s.length() >= 3) {

            if (openIndex != -1 && closeIndex != -1) {
                searchSec(s, openIndex, closeIndex);
            }
            if (equalIndex != -1) {
                searchVarName(s, equalIndex);
                searchVarValue(s, equalIndex);
                mySections[sectionName][varName] = std::pair<std::string, myType>(varValue, getType(varValue));

            }
        } else {
            continue;
        }

    }
    file.close();
}

template<>
std::string IniParser::GetValue<std::string>(const std::string &sectionName, const std::string &paramName)
throw(SectionNotFound, ParamNotFound) {
    if (!isHaveASec(sectionName)) {
        throw SectionNotFound(sectionName.c_str());
    } else if (!isHaveParam(sectionName, paramName)) {
        throw ParamNotFound(paramName.c_str());
    }
    return mySections[sectionName][paramName].first;
}


template<>
int IniParser::GetValue<int>(const std::string &sectionName, const std::string &paramName)
throw(SectionNotFound, ParamNotFound) {
    if (!isHaveASec(sectionName)) {
        throw SectionNotFound(sectionName.c_str());
    } else if (!isHaveParam(sectionName, paramName)) {
        throw ParamNotFound(paramName.c_str());

    }

    return stoi(mySections[sectionName][paramName].first);
}


template<>
double IniParser::GetValue<double>(const std::string &sectionName, const std::string &paramName)
throw(SectionNotFound, ParamNotFound) {
    if (!isHaveASec(sectionName)) {
        throw SectionNotFound(sectionName.c_str());
    } else if (!isHaveParam(sectionName, paramName)) {
        throw ParamNotFound(paramName.c_str());

    }
    return stod(mySections[sectionName][paramName].first);
}

