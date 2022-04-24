#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include "calendar.h"

using namespace std;

int main() {
    char options1[] = "Choose one of the following:\n> add meeting\n> remove meeting\n> daily meetings\n";
    char options2[] = "> edit meeting\n> find a meeting\n> save by duration criteria\n> find free time\n";
    char *options = strcat(options1, options2);
    char filename[1024];

    cout << "Calendar filename: ";
    cin >> filename;

    Calendar calendar(filename);

    char buff[1024];

    while(strcmp(buff, "exit") != 0) {
        system("clear");
        cout << options << endl;
        cout << "> ";
        cin.getline(buff, 1024);

        try {
            if (strcmp(buff, "add meeting") == 0) {
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
            else if (strcmp(buff, "remove meeting") == 0) {
                
            }
            else if (strcmp(buff, "daily meetings") == 0) {
                
            }
            else if (strcmp(buff, "edit meeting") == 0) {
                
            }
            else if (strcmp(buff, "find a meeting") == 0) {
                
            }
            else if (strcmp(buff, "save by duration criteria") == 0) {
                
            }
            else if (strcmp(buff, "find free time") == 0) {
                
            }
        } catch (const char *e) {
            cout << e << endl << "Invalid operation!" << endl;
        }
        
    }
    
    return 0;
}