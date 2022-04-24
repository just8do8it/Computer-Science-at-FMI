#include <iostream>
#include <cstring>
#include <fstream>
#include "calendar.h"

using namespace std;

int main() {
    try {
        Meeting meeting1("name", "comment", "28-02-1900", "19:15", "19:26");
        Meeting meeting2(meeting1);
    } catch (const char* e) {
        cout << e << endl;
    }

    Calendar calendar1("file.txt");
    Calendar calendar2("calendar1.txt");

    calendar2 = calendar1;
    cout << calendar1.getFilename() << endl;
    
    return 0;
}