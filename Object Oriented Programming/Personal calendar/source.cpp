#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include "calendar.h"

#define DEFAULT_CAPACITY 1024

using namespace std;

Meeting& initMeeting() {
    char *name;
    char *comment;
    char nameBuff[DEFAULT_CAPACITY];
    char commentBuff[DEFAULT_CAPACITY];
    char date[11];
    char startTime[6];
    char endTime[6];

    cout << "Name: ";
    cin.getline(nameBuff, DEFAULT_CAPACITY);
    name = new char[strlen(nameBuff) + 1];
    strcpy(name, nameBuff);

    cout << "Comment: ";
    cin.getline(commentBuff, DEFAULT_CAPACITY);
    comment = new char[strlen(commentBuff) + 1];
    strcpy(comment, commentBuff);

    cout << "Date: ";
    cin >> date;
    cout << "Start time: ";
    cin >> startTime;
    cout << "End time: ";
    cin >> endTime;

    Meeting *meeting = new Meeting(name, comment, date, startTime, endTime);
    return *meeting;
}

int main() {
    char options1[] = "Choose a number for one of the following:\n> add meeting (1)\n> remove meeting (2)\n> daily meetings (3)\n";
    char options2[] = "> edit meeting (4)\n> find a meeting (5)\n> save by duration criteria (6)\n> find free time (7)\n> exit (8)\n";
    char filename[DEFAULT_CAPACITY];

    cout << "Calendar filename: ";
    cin >> filename;

    Calendar calendar(filename);

    bool wait = false;

    size_t choice;
    do {
        if (!wait) {
            system("clear");
        }

        wait = false;
        cout << options1 << options2 << endl;
        cout << "> ";

        cin >> choice;
        cin.get();

        try {
            if (choice == 1) {
                Meeting meeting = initMeeting();
                calendar.addMeeting(meeting);
                calendar.save();
            }
            else if (choice == 2) {
                Meeting meeting = initMeeting();
                calendar.removeMeeting(meeting);
                calendar.save();
            }
            else if (choice == 3) {
                char date[DEFAULT_CAPACITY];
                cout << "Enter a date: ";
                cin >> date;

                char *dynDate = new char[strlen(date) + 1];
                strcpy(dynDate, date);
                if (!dateIsValid(dynDate)) {
                    throw "Invalid date!";
                }

                system("clear");
                calendar.printForDay(dynDate);
                wait = true;
            }
            else if (choice == 4) {
                Meeting meeting = initMeeting();
                char changeOptions1[] = "Choose what to change:\n> name (1)\n> comment (2)\n";
                char changeOptions2[] = "> date (3)\n> start time (4)\n> end time (5)\n";

                size_t num;
                cout << changeOptions1 << changeOptions2 << endl;
                cin >> num;
                cin.ignore();

                if (num == 1) {
                    char nameBuff[DEFAULT_CAPACITY];
                    cout << "New name: ";
                    cin.getline(nameBuff, DEFAULT_CAPACITY);
                    char *name = new char[strlen(nameBuff) + 1];
                    strcpy(name, nameBuff);

                    calendar.changeName(meeting, name);
                    calendar.save();
                }
                else if (num == 2) {
                    char commentBuff[DEFAULT_CAPACITY];
                    cout << "New comment: ";
                    cin.getline(commentBuff, DEFAULT_CAPACITY);
                    char *comment = new char[strlen(commentBuff) + 1];
                    strcpy(comment, commentBuff);

                    calendar.changeComment(meeting, comment);
                    calendar.save();
                }
                else if (num == 3) {
                    char dateBuff[11];
                    cout << "New date: ";
                    cin.getline(dateBuff, 11);
                    char *date = new char[11];
                    strcpy(date, dateBuff);

                    if (!dateIsValid(date)) {
                        throw "Invalid date!";
                    }

                    calendar.changeDate(meeting, date);
                    calendar.save();

                }
                else if (num == 4) {
                    char startTimeBuff[DEFAULT_CAPACITY];
                    cout << "New startTime: ";
                    cin.getline(startTimeBuff, DEFAULT_CAPACITY);
                    char *startTime = new char[strlen(startTimeBuff) + 1];
                    strcpy(startTime, startTimeBuff);

                    if (!timeIsValid(startTime, meeting.getEndTime())) {
                        throw "Invalid time!";
                    }

                    calendar.changeStartTime(meeting, startTime);
                    calendar.save();
                }
                else if (num == 5) {
                    char endTimeBuff[DEFAULT_CAPACITY];
                    cout << "New endTime: ";
                    cin.getline(endTimeBuff, DEFAULT_CAPACITY);
                    char *endTime = new char[strlen(endTimeBuff) + 1];
                    strcpy(endTime, endTimeBuff);

                    if (!timeIsValid(meeting.getStartTime(), endTime)) {
                        throw "Invalid time!";
                    }

                    calendar.changeStartTime(meeting, endTime);
                    calendar.save();
                }
            }
            else if (choice == 5) {
                char findOptions[] = "Choose where to find:\n> in names (1)\n> in comments (2)\n";

                size_t num;
                cout << findOptions << endl;
                cin >> num;
                cin.ignore();

                char strBuff[DEFAULT_CAPACITY];
                cout << "String to search: ";
                cin.getline(strBuff, DEFAULT_CAPACITY);
                char *str = new char[strlen(strBuff) + 1];
                strcpy(str, strBuff);

                if (num == 1) {
                    calendar.printMeetingsByName(str);
                }
                else if (num == 2) {
                    calendar.printMeetingsByComment(str);
                }

                wait = true;
            }
            else if (choice == 6) {
                char startBuff[DEFAULT_CAPACITY], endBuff[DEFAULT_CAPACITY];
                cout << "Start date: ";
                cin.getline(startBuff, DEFAULT_CAPACITY);
                cout << "End date: ";
                cin.getline(endBuff, DEFAULT_CAPACITY);

                char *startDate = new char[strlen(startBuff) + 1];
                strcpy(startDate, startBuff);
                char *endDate = new char[strlen(endBuff) + 1];
                strcpy(endDate, endBuff);

                if (!dateIsValid(startDate) || !dateIsValid(endDate)) {
                    throw "Invalid date!";
                }

                calendar.saveByWorkHours(startDate, endDate);
            }
            else if (choice == 7) {
                char dateBuff[DEFAULT_CAPACITY];
                char rangeStart[DEFAULT_CAPACITY];
                char rangeEnd[DEFAULT_CAPACITY];
                size_t duration;

                cout << "Date: ";
                cin.getline(dateBuff, DEFAULT_CAPACITY);
                char *date = new char[strlen(dateBuff) + 1];
                strcpy(date, dateBuff);
                
                cout << "Duration (in minutes): ";
                cin >> duration;
                cin.ignore();
                
                cout << "Time range start: ";
                cin.getline(rangeStart, DEFAULT_CAPACITY);

                cout << "Time range end: ";
                cin.getline(rangeEnd, DEFAULT_CAPACITY);

                if (!timeIsValid(rangeStart, rangeEnd)) {
                    throw "Invalid time!";
                }

                if (!calendar.isThereTime(date, duration, rangeStart, rangeEnd)) {
                    throw "Free time: 404 (Not Found)";
                }
                wait = true;
            }

        } catch (const char *e) {
            cout << "Invalid operation: " << e << endl << endl;
            wait = true;
        }
        
    } while(choice != 8);
    
    return 0;
}