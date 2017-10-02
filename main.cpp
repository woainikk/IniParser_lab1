#include <iostream>
#include "IniParser.h"
#include <string>
#include "SectionNotFound.h"
#include "ParamNotFound.h"

using namespace std;

int main() {
    try {
        string file_name;
        cin >> file_name;
        IniParser myParser(file_name);
        myParser.printMap();
        string ifindsec;
        string ifindparam;
        cin >> ifindsec >> ifindparam;
        string s = myParser.GetValue<string>(ifindsec, ifindparam);
        cout << s;
    } catch (const SectionNotFound &e) {
        cerr << e.what() << endl;
    } catch (const ParamNotFound &e) {
        cerr << e.what() << endl;
    }
}




