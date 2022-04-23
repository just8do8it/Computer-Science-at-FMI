#include <iostream>
#include <cstring>
#include <fstream>
#include "meeting.h"

using namespace std;

int main() {
    try {
        Meeting meeting1("name", "comment", "28-02-1900", "19:27", "19:26");
        Meeting meeting2(meeting1);
    } catch (const char* e) {
        cout << e << endl;
    }
    
    return 0;
}