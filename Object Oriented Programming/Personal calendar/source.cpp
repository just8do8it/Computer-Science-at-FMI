// #include <iostream>
// #include <cstring>
// #include <fstream>
// #include "calendar.h"

// using namespace std;

// int main() {
//     // try {
//     //     Meeting meeting1("name", "comment", "28-02-1900", "19:15", "19:26");
//     //     Meeting meeting2(meeting1);
//     // } catch (const char* e) {
//     //     cout << e << endl;
//     // }

//     Meeting meeting2("name2", "comment2", "08-12-1100", "15:59", "16:05");
//     Meeting meeting1("name1", "comment1", "28-02-1900", "19:15", "19:26");
//     Meeting meeting4("name4", "comment4", "31-05-1995", "07:30", "09:45");
//     Meeting meeting5("name5", "comment5", "15-09-2002", "17:09", "19:00");
//     Meeting meeting3("name3", "comment3", "15-09-2002", "20:20", "23:00");

//     Calendar calendar1("calendar1.txt");
//     Calendar calendar2("calendar2.txt");

//     calendar1.addMeeting(meeting1);
//     calendar1.addMeeting(meeting2);
//     calendar1.addMeeting(meeting3);
//     calendar1.addMeeting(meeting4);
//     calendar1.addMeeting(meeting5);

//     cout << calendar1.getMeetings()[0]->getStartTime() << endl;
//     cout << calendar1.getMeetings()[1]->getStartTime() << endl;
//     cout << calendar1.getMeetings()[2]->getStartTime() << endl;
//     cout << calendar1.getMeetings()[3]->getStartTime() << endl;
//     cout << calendar1.getMeetings()[4]->getStartTime() << endl;

//     calendar1.removeMeeting(meeting1);
    
//     cout << calendar1.getMeetings()[1]->getDate() << endl;
    
//     return 0;
// }