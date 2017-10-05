//
// Created by Маргарита on 10.09.2017.
//

#include "IniParser.h"
#include <fstream>
#include "SectionNotFound.h"
#include "ParamNotFound.h"


IniParser::IniParser() {}

IniParser::IniParser(const std::string &f) {
    fileName = f;
    IniParser::readFile();
}


void IniParser::searchSec(const std::string &s, int openIndex, int closeIndex) {
    int index = 0;
    while (index < openIndex) {
        if (s[index] == ' ') {
            index++;
        } else {
            throw std::runtime_error("Incorrect file syntax.");
        }
    }
    if (index == openIndex) {
        sectionName = s.substr(openIndex + 1, closeIndex - openIndex - 1);
    }
}

void IniParser::removeSpaces(std::string &s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            s.erase(i, 1);
        }
    }
}

bool IniParser::isHaveASec(const std::string &secName) {
    return mySections.find(secName) != mySections.end();
}

bool IniParser::isHaveParam(const std::string &secName, const std::string &paramName) {
    return mySections.at(secName).count(paramName) == 1;
}

void IniParser::searchVarName(std::string s, int equalIndex) {
    int index = 0;
    varName = "";
    while (index < equalIndex and ((s[index] >= 'A' and s[index] <= 'Z') or (s[index] >= 'a' and s[index] <= 'z'))) {
        varName += s[index];
        index++;
    }
}


void IniParser::searchVarValue(std::string s, int equalIndex) {
    int index = equalIndex + 1;
    varValue = "";
    while (index < s.size()) {
        varValue += s[index];
        index++;
    }
}


IniParser::typesOfValues IniParser::getTypeOfValue(std::string value) {
    int dotCount = 0;
    int numCount = 0;
    for (int i = 0; i < value.size(); i++) {
        if (value[i] == '.' && i != 0 && i != value.size() - 1) {
            dotCount++;
        }
        if (value[i] >= '0' && value[i] <= '9') {
            numCount++;
        }
    }
    if (value.size() == numCount) {
        return INT;
    } else if (value.size() - 1 == numCount && dotCount == 1) {
        return DOUBLE;
    } else {
        return STRING;
    }
}


void IniParser::printMap() {
    for (auto it : mySections) {
        std::cout << it.first << ": " << std::endl;
        std::map<std::string, std::pair<std::string, typesOfValues >> &myInnerMap = it.second;
        for (auto it2: myInnerMap) {
            std::cout << it2.first << " = " << it2.second.first << ". Type:"
                      << it2.second.second << std::endl;
        }
        std::cout << std::endl;
    }
}

void IniParser::removeComments(std::string &s) {
    int commentIndex = s.find(';');
    if (commentIndex != -1) {
        s.erase(commentIndex, s.length());
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
        removeComments(s);
        removeSpaces(s);
        int openIndex = s.find('[');
        int closeIndex = s.find(']');
        int equalIndex = s.find('=');
        if (s.length() > 2) {
            if (openIndex != -1 && closeIndex != -1) {
                searchSec(s, openIndex, closeIndex);
            }
            if (equalIndex != -1) {
                searchVarName(s, equalIndex);
                searchVarValue(s, equalIndex);
                mySections[sectionName][varName] = std::pair<std::string, typesOfValues>(varValue, getTypeOfValue(varValue));
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

