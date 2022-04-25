#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include "calendar.h"

using namespace std;

int main() {
    char options1[] = "Choose a number for one of the following:\n> add meeting (1)\n> remove meeting (2)\n> daily meetings (3)\n";
    char options2[] = "> edit meeting (4)\n> find a meeting (5)\n> save by duration criteria (6)\n> find free time (7)\n> exit (8)\n";
    char *options = strcat(options1, options2);
    char filename[1024];

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
        cout << options << endl;
        cout << "> ";

        cin >> choice;
        cin.get();

        try {
            if (choice == 1) {
                char *name;
                char *comment;
                char nameBuff[1024];
                char commentBuff[1024];
                char date[11];
                char startTime[6];
                char endTime[6];

                cout << "Name: ";
                cin.getline(nameBuff, 1024);
                name = new char[strlen(nameBuff) + 1];
                strcpy(name, nameBuff);

                cout << "Comment: ";
                cin.getline(commentBuff, 1024);
                comment = new char[strlen(commentBuff) + 1];
                strcpy(comment, commentBuff);

                cout << "Date: ";
                cin >> date;
                cout << "Start time: ";
                cin >> startTime;
                cout << "End time: ";
                cin >> endTime;

                Meeting meeting(name, comment, date, startTime, endTime);
                calendar.addMeeting(meeting);
                calendar.save();
            }
            else if (choice == 2) {
                char *name;
                char *comment;
                char nameBuff[1024];
                char commentBuff[1024];
                char date[11];
                char startTime[6];
                char endTime[6];

                cout << "Name: ";
                cin.getline(nameBuff, 1024);
                name = new char[strlen(nameBuff) + 1];
                strcpy(name, nameBuff);

                cout << "Comment: ";
                cin.getline(commentBuff, 1024);
                comment = new char[strlen(commentBuff) + 1];
                strcpy(comment, commentBuff);

                cout << "Date: ";
                cin >> date;
                cout << "Start time: ";
                cin >> startTime;
                cout << "End time: ";
                cin >> endTime;

                Meeting meeting(name, comment, date, startTime, endTime);
                calendar.removeMeeting(meeting);
                calendar.save();
            }
            else if (choice == 3) {
                char date[1024];
                cout << "Enter a date: ";
                cin >> date;

                char *dynDate = new char[strlen(date) + 1];
                strcpy(dynDate, date);
                if (!Meeting::dateIsValid(dynDate)) {
                    throw "Invalid date!";
                }

                system("clear");
                if (!calendar.printForDay(dynDate)) {
                    throw "No meetings for that day!";
                }
                wait = true;
            }
            else if (choice == 3) {
                
            }
            else if (choice == 4) {
                
            }
            else if (choice == 5) {
                
            }
            else if (choice == 6) {
                
            }
            else if (choice == 7) {
                
            }
            
        } catch (const char *e) {
            // system("clear");
            cout << "Invalid operation: " << e << endl << endl;
            wait = true;
        }
        
    } while(choice != 8);
    
    return 0;
}