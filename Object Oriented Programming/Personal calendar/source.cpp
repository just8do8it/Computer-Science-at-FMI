#include <iostream>
#include <cstring>
#include <fstream>
#include "calendar.h"

using namespace std;

int main() {
    // try {
    //     Meeting meeting1("name", "comment", "28-02-1900", "19:15", "19:26");
    //     Meeting meeting2(meeting1);
    // } catch (const char* e) {
    //     cout << e << endl;
    // }

    Meeting meeting1("name1", "Annual event", "28-02-1900", "19:15", "19:26");
    Meeting meeting2("family gathering", "Pretty much Annual", "08-12-1100", "15:59", "16:05");
    Meeting meeting3("name3", "comment3", "15-09-2002", "20:20", "23:00");
    Meeting meeting4("gathering", "comment4", "31-05-1995", "07:30", "09:45");
    Meeting meeting5("name5", "Annual", "15-09-2002", "17:09", "19:00");

    Calendar calendar("calendar1.txt");

    calendar.addMeeting(meeting1);
    calendar.addMeeting(meeting2);
    calendar.addMeeting(meeting3);
    calendar.addMeeting(meeting4);
    calendar.addMeeting(meeting5);

    calendar.save();

    calendar.saveByWorkHours("30-04-1995", "16-09-2002");
    
    return 0;
}