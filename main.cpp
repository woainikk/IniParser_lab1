#include <iostream>
#include "IniParser.h"
#include <string>
#include "SectionNotFound.h"
#include "ParamNotFound.h"

using namespace std;

int main() {
    string fale_name;
    cin >> fale_name;
    IniParser myParser(fale_name);
    myParser.printMap();
    string ifindsec;
    string ifindparam;
    /*cin >> ifindsec;
    myParser.isHaveASec(ifindsec);
    if (myParser.isHaveASec(ifindsec)){

        cin >> ifindparam;
        myParser.isHaveParam(ifindsec, ifindparam);
    }*/
    cin >> ifindsec >> ifindparam;
    string s = myParser.GetValue<string>(ifindsec, ifindparam);
    cout << s;
}




