#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "meeting.h"

#define DEFAULT_CAPACITY 1024

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


Meeting::Meeting(const char *name, const char *comment, const char *date,
                const char *startTime, const char *endTime) {
    
    this->name = new char[strlen(name) + 1];
    this->comment = new char[strlen(comment) + 1];
    
    strcpy(this->name, name);
    strcpy(this->comment, comment);
    
    if (dateIsValid(date)) {
        strcpy(this->date, date);
    } else {
        throw "Invalid date!";
    }

    if (timeIsValid(startTime, endTime)) {
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

void Meeting::setName(const char* name) {
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Meeting::setComment(const char* comment) {
    delete[] this->comment;
    this->comment = new char[strlen(comment) + 1];
    strcpy(this->comment, comment);
}

void Meeting::setDate(const char* date) {
    strcpy(this->date, date);
}

void Meeting::setStartTime(const char* startTime) {
    strcpy(this->startTime, startTime);
}

void Meeting::setEndTime(const char* endTime) {
    strcpy(this->endTime, endTime);
}

ostream& operator<<(ostream& out, const Meeting& meeting) {
    out << meeting.getName() << endl;
    out << meeting.getComment() << endl;
    out << meeting.getDate() << endl;
    out << meeting.getStartTime() << endl;
    out << meeting.getEndTime() << endl;

    return out;
}

istream& operator>>(istream& in, Meeting*& meeting) {
    char nameBuff[DEFAULT_CAPACITY], commentBuff[DEFAULT_CAPACITY], date[DEFAULT_CAPACITY], startTime[DEFAULT_CAPACITY], endTime[DEFAULT_CAPACITY];
    in.getline(nameBuff, DEFAULT_CAPACITY);
    char *name = new char[strlen(nameBuff) + 1];
    strcpy(name, nameBuff);

    in.getline(commentBuff, DEFAULT_CAPACITY);
    char *comment = new char[strlen(commentBuff) + 1];
    strcpy(comment, commentBuff);

    in.getline(date, DEFAULT_CAPACITY);
    in.getline(startTime, DEFAULT_CAPACITY);
    in.getline(endTime, DEFAULT_CAPACITY);

    meeting = new Meeting(name, comment, date, startTime, endTime);
    
    return in;
}

bool operator==(const Meeting& lhs, const Meeting& rhs) {
    bool name = strcmp(lhs.getName(), rhs.getName()) == 0;
    bool comment = strcmp(lhs.getComment(), rhs.getComment()) == 0;
    bool date = strcmp(lhs.getDate(), rhs.getDate()) == 0;
    bool startTime = strcmp(lhs.getStartTime(), rhs.getStartTime()) == 0;
    bool endTime = strcmp(lhs.getEndTime(), rhs.getEndTime()) == 0;

    return name && comment && date && startTime && endTime;
}

bool operator!=(const Meeting& lhs, const Meeting& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Meeting& lhs, const Meeting& rhs) {

    char lhsDay[3], lhsMonth[3], lhsYear[5];
    char rhsDay[3], rhsMonth[3], rhsYear[5];
    
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        else if (i < 2) {
            lhsDay[i] = lhs.getDate()[i];
            rhsDay[i] = rhs.getDate()[i];
        }
        else if (i < 5) {
            lhsMonth[i - 3] = lhs.getDate()[i];
            rhsMonth[i - 3] = rhs.getDate()[i];
        }
        else {
            lhsYear[i - 6] = lhs.getDate()[i];
            rhsYear[i - 6] = rhs.getDate()[i];
        }
    }

    lhsDay[2] = '\0';
    lhsMonth[2] = '\0';
    lhsYear[4] = '\0';
    
    rhsDay[2] = '\0';
    rhsMonth[2] = '\0';
    rhsYear[4] = '\0';

    int lYear = atoi(lhsYear), lMonth = atoi(lhsMonth), lDay = atoi(lhsDay);
    int rYear = atoi(rhsYear), rMonth = atoi(rhsMonth), rDay = atoi(rhsDay);

    if (lYear == rYear) {
        if (lMonth == rMonth) {
            if (lDay == rDay) {
                return getTimeInMinutes(lhs.getEndTime()) <= getTimeInMinutes(rhs.getStartTime());
            } else if (lDay < rDay) {
                return true;
            }
        } else if (lMonth < rMonth) {
            return true;
        }
    } else if (lYear < rYear)  {
        return true;   
    }

    return false;
}

size_t getTimeInMinutes(const char *time) {
    char hour[3], min[3];

    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        else if (i < 2) {
            hour[i] = time[i];
        }
        else {
            min[i - 3] = time[i];
        }
    }

    hour[2] = '\0';
    min[2] = '\0';

    int h = atoi(hour), m = atoi(min);

    return 60 * h + m;
}

bool dateIsValid(const char* date) {
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

bool timeIsValid(const char* start, const char* end) {
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

    if ((h1 >= 0 && h1 <= 23) && (h2 >= 0 && h2 <= 23) &&
        (m1 >= 0 && m1 <= 59) && (m2 >= 0 && m2 <= 59)) {

        if (h1 < h2) return true;
        else if (h1 == h2) {
            if (m1 < m2) return true;
        }
    }

    return false;
}
