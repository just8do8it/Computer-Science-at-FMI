#include <iostream>
#include <cstring>
#include <fstream>
#include "meeting.h"

using namespace std;

void Meeting::copyFrom(const Meeting& other) {
    this->name = new char[strlen(other.name) + 1];
    this->comment = new char[strlen(other.comment) + 1];
    strcpy(this->name, other.name);
    strcpy(this->comment, other.comment);
    strcpy(this->date, other.date);
    strcpy(this->startTime, other.startTime);
    strcpy(this->endTime, other.endTime);
}

void Meeting::free() {
    delete[] this->name, this->comment;
}

bool Meeting::dateIsValid(const char* date) {
    if (date[2] != '-' || date[5] != '-' || strlen(date) != 10) {
        return false;
    }

    char day[3], month[3], year[5];
    
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        else if (i < 2) day[i] = date[i];
        else if (i < 5) month[i - 3] = date[i];
        else year[i - 6] = date[i];
    }

    day[2] = '\0';
    month[2] = '\0';
    year[4] = '\0';

    for (int i = 0; i < 4; ++i) {
        if (i < 2) {
            if (day[i] < '0' || day[i] > '9' ||
                month[i] < '0' || month[i] > '9' ||
                year[i] < '0' || year[i] > '9') {

                return false;
            }
        } else {
            if (year[i] < '0' || year[i] > '9') return false;
        }
    }
    
    int d = atoi(day), m = atoi(month), y = atoi(year);
    if (d && m && y) {
        if (m >= 1 && m <= 12) {
            if (d >= 1) {
                if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 ||
                    m == 10 || m == 12) && d <= 31) {

                    return true;
                }
                else if ((m == 4 || m == 6 || m == 9 || m == 11) && d <= 30) {
                    return true;
                }
                else {
                    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
                        if (d <= 29) return true;
                    } else {
                        if (d <= 28) return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Meeting::timeIsValid(const char* start, const char* end) {
    if (start[2] != ':' || end[2] != ':' ||
        strlen(start) != 5 || strlen(end) != 5) {
        return false;
    }

    char stHour[3], stMin[3], endHour[3], endMin[3];

    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        else if (i < 2) {
            stHour[i] = start[i];
            endHour[i] = end[i];
        }
        else {
            stMin[i - 3] = start[i];
            endMin[i - 3] = end[i];
        }
    }

    stHour[2] = '\0';
    stMin[2] = '\0';
    endHour[2] = '\0';
    endMin[2] = '\0';

    for (int i = 0; i < 2; ++i) {
        if (stHour[i] < '0' || stHour[i] > '9' ||
            stMin[i] < '0' || stMin[i] > '9' ||
            endHour[i] < '0' || endHour[i] > '9' ||
            endMin[i] < '0' || endMin[i] > '9') {

            return false;
        }
    }

    int h1 = atoi(stHour), m1 = atoi(stMin);
    int h2 = atoi(endHour), m2 = atoi(endMin);

    cout << h1 << ":" << m1 << endl;
    cout << h2 << ":" << m2 << endl;

    if ((h1 >= 0 && h1 <= 23) && (h2 >= 0 && h2 <= 23) &&
        (m1 >= 0 && m1 <= 59) && (m2 >= 0 && m2 <= 59)) {

        if (h1 < h2) return true;
        else if (h1 == h2) {
            if (m1 < m2) return true;
        }
    }

    return false;
}

Meeting::Meeting(const char *name, const char *comment, const char *date,
                const char *startTime, const char *endTime) {
    
    this->name = new char[strlen(name) + 1];
    this->comment = new char[strlen(comment) + 1];
    
    strcpy(this->name, name);
    strcpy(this->comment, comment);
    
    if (dateIsValid(date)) {
        cout << "Valid date!" << endl;
        strcpy(this->date, date);
    } else {
        throw "Invalid date!";
    }

    if (timeIsValid(startTime, endTime)) {
        cout << "Valid time!" << endl;
        strcpy(this->startTime, startTime);
        strcpy(this->endTime, endTime);
    } else {
        throw "Invalid time!";
    }
}

Meeting::Meeting(const Meeting& other) {
    copyFrom(other);
}

Meeting& Meeting::operator=(const Meeting& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

Meeting::~Meeting() {
    free();
}

const char* Meeting::getName() const {
    return this->name;
}

const char* Meeting::getComment() const {
    return this->comment;
}

const char* Meeting::getDate() const {
    return this->date;
}

const char* Meeting::getStartTime() const {
    return this->startTime;
}

const char* Meeting::getEndTime() const {
    return this->endTime;
}