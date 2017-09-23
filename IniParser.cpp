//
// Created by Маргарита on 10.09.2017.
//

#include "IniParser.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "SectionNotFound.h"
#include "ParamNotFound.h"


IniParser::IniParser() {}

IniParser::IniParser(const string &f) {
    fileName = f;
    IniParser::readFile();
}


void IniParser::searchSec(string s, int openIndex, int closeIndex) {
    int i = 0;
    while (i < openIndex) {
        if (s[i] == ' ') {
            i++;
        } else {
            throw runtime_error("Incorrect file syntax.");
        }
    }

    if (i == openIndex) {
        sectionName = s.substr(openIndex + 1, closeIndex - openIndex - 1);

    }
}


bool IniParser::isHaveASec(const string &sec_name) {
    return mySections.find(sec_name) != mySections.end();
}

bool IniParser::isHaveParam(const string &sec_name, const string &param_name) {

    return mySections.at(sec_name).count(param_name) == 1;
}


void IniParser::searchVarName(string s, int equalIndex) {
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


void IniParser::searchVarValue(string s, int equalIndex) {
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


IniParser::myType IniParser::getType(string myS) {
    int dotCount = 0;
    int numcount = 0;
    for (int i = 0; i < myS.size(); i++) {
        if (myS[i] == '.' && i != 0 && i != myS.size() - 1) {
            dotCount++;
        }
        if (myS[i] >= '0' && myS[i] <= '9') {
            numcount++;
        }
    }
    if (myS.size() == numcount) {
        return INT;
    } else if (myS.size() - 1 == numcount && dotCount == 1) {
        return DOUBLE;
    } else {
        return STRING;
    }
}


void IniParser::printMap() {
    for (auto it : mySections) {
        cout << it.first << ": " << endl;
        map<string, pair<string, myType >> &myInnerMap = it.second;
        for (auto it2: myInnerMap) {
            cout << it2.first << " = " << it2.second.first << ". Type:"
                 << it2.second.second << endl;
        }
        cout << endl;
    }
}

void IniParser::readFile() {

    string s;
    ifstream file(fileName);
    if (!file.good()) {
        throw runtime_error("This file does not exist.");
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
                mySections[sectionName][varName] = pair<string, myType>(varValue, getType(varValue));

            }
        } else {
            continue;
        }

    }
    file.close();
}

template<>
string IniParser::GetValue<string>(const string &section_name, const string &param_name)
throw(SectionNotFound, ParamNotFound) {
    if (!isHaveASec(section_name)) {
        throw SectionNotFound(section_name);
    } else if (!isHaveParam(section_name, param_name)) {
        throw ParamNotFound(param_name);
    }
    return mySections[section_name][param_name].first;
}


template<>
int IniParser::GetValue<int>(const string &section_name, const string &param_name)
throw(SectionNotFound, ParamNotFound) {
    if (!isHaveASec(section_name)) {
        throw SectionNotFound(section_name);
    } else if (!isHaveParam(section_name, param_name)) {
        throw ParamNotFound(param_name);

    }

    return stoi(mySections[section_name][param_name].first);
}


template<>
double IniParser::GetValue<double>(const string &section_name, const string &param_name)
throw(SectionNotFound, ParamNotFound) {
    if (!isHaveASec(section_name)) {
        throw SectionNotFound(section_name);
    } else if (!isHaveParam(section_name, param_name)) {
        throw ParamNotFound(param_name);

    }
    return stod(mySections[section_name][param_name].first);
}

