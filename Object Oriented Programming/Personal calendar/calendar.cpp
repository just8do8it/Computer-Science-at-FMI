#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "calendar.h"
using namespace std;

#define DEFAULT_CAPACITY 4

void Calendar::copyFrom(const Calendar& other) {
    this->filename = new char[strlen(other.filename) + 1];
    this->meetings = new Meeting*[other.capacity];
    strcpy(this->filename, other.filename);
    
    for (int i = 0; i < other.size; ++i) {
        this->meetings[i] = new Meeting(*other.meetings[i]);
    }

    this->size = other.size;
    this->capacity = other.capacity;
}

void Calendar::free() {
    delete[] this->filename;
    
    for (int i = 0; i < this->size; ++i) {
        delete this->meetings[i];
    }

    delete[] this->meetings;
    this->size = 0;
    this->capacity = 0;
}

Calendar::Calendar(const char *filename) {
    this->filename = new char[strlen(filename) + 1];
    strcpy(this->filename, filename);

    this->capacity = DEFAULT_CAPACITY;
    this->meetings = new Meeting*[this->capacity];

    this->size = 0;
}

Calendar::Calendar(const char* filename, Meeting** meetings, size_t size, size_t capacity) {
    this->filename = new char[strlen(filename) + 1];
    strcpy(this->filename, filename);

    this->capacity = capacity;
    this->meetings = new Meeting*[this->capacity];
    
    for (int i = 0; i < this->capacity; ++i) {
        this->meetings[i] = new Meeting(*meetings[i]);
    }

    this->size = size;
}

Calendar::Calendar(const Calendar& other) {
    copyFrom(other);
}

Calendar& Calendar::operator=(const Calendar& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

Calendar::~Calendar() {
    free();
}

const char* Calendar::getFilename() const {
    return this->filename;
}

Meeting** Calendar::getMeetings() const {
    return this->meetings;
}

size_t Calendar::getSize() const {
    return this->size;
}

size_t Calendar::getCapacity() const {
    return this->capacity;
}

void Calendar::resize(size_t newCapacity) {
    Calendar copy(*this);
    copy.capacity = newCapacity;
    copyFrom(copy);
}

void Calendar::sort() {
    if (this->size == 1) return;

    for (int i = this->size - 1; i > 0; --i) {
        if (*this->meetings[i] < *this->meetings[i - 1]) {
            Meeting *temp = this->meetings[i];
            this->meetings[i] = this->meetings[i - 1];
            this->meetings[i - 1] = temp;
        }
    }
}

bool Calendar::addMeeting(const Meeting& meeting) {
    if (this->size + 1 == this->capacity) {
        resize(this->capacity * 2);
    }


    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            return false;
        }
    }

    this->meetings[this->size] = new Meeting(meeting);
    this->size++;
    sort();
    return true;
}

bool Calendar::removeMeeting(const Meeting& meeting) {
    if (this->size - 1 <= this->capacity / 3) {
        resize(this->capacity / 2);
    }

    bool found = false;

    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            found = true;
            delete this->meetings[i];
        }
        if (found) {
            if (i == this->size - 2) {
                this->meetings[i] = new Meeting(*this->meetings[i + 1]);
                break;
            } else if (i == this->size - 1) {
                this->size--;
                return true;
            }
            this->meetings[i] = this->meetings[i + 1];
        }
    }

    if (found) {
        delete this->meetings[this->size - 1];
        this->size--;
        return true;
    }
    
    return false;
}

bool Calendar::save() {
    ofstream file(this->filename);

    if (file.fail()) {
        return false;
    }

    file << "Number of meetings: " << this->size << endl << endl;

    for (int i = 0; i < this->size; ++i) {
        file << *this->meetings[i] << endl;
    }

    file.close();

    return true;
}

bool Calendar::printFile() const {
    ifstream file(this->filename);

    if (file.fail()) {
        return false;
    }

    while (!file.eof()) {
        char buff[1024];
        file.getline(buff, 1024);
        cout << buff << endl;
    }

    file.close();

    return true;
}

void Calendar::changeName(const Meeting& meeting, const char* name) {
    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            this->meetings[i]->setName(name);
            break;
        }
    }
}

void Calendar::changeComment(const Meeting& meeting, const char* comment) {
    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            this->meetings[i]->setComment(comment);
            break;
        }
    }
}

bool Calendar::changeDate(const Meeting& meeting, const char* date) {
    if (!Meeting::dateIsValid(date)) return false;

    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            this->meetings[i]->setDate(date);
            Meeting *temp = new Meeting(*meetings[i]);
            removeMeeting(*temp);
            addMeeting(*temp);
            sort();
            break;
        }
    }
    
    return true;
}

bool Calendar::changeStartTime(const Meeting& meeting, const char* startTime) {

    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            if (!Meeting::timeIsValid(startTime, this->meetings[i]->getEndTime()))
                return false;
            
            this->meetings[i]->setStartTime(startTime);
            Meeting *temp = new Meeting(*meetings[i]);
            removeMeeting(*temp);
            addMeeting(*temp);
            sort();
            break;
        }
    }

    return true;
}

bool Calendar::changeEndTime(const Meeting& meeting, const char* endTime) {
    
    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            if (!Meeting::timeIsValid(this->meetings[i]->getStartTime(), endTime))
                return false;
            
            this->meetings[i]->setEndTime(endTime);
            Meeting *temp = new Meeting(*meetings[i]);
            removeMeeting(*temp);
            addMeeting(*temp);
            sort();
            break;
        }
    }

    return true;
}

void Calendar::printMeetingsByName(const char* name) {
    for (int i = 0; i < this->size; ++i) {
        if (strstr(this->meetings[i]->getName(), name)) {
            cout << *this->meetings[i] << endl;
        }
    }
}

void Calendar::printMeetingsByComment(const char* comment) {
    for (int i = 0; i < this->size; ++i) {
        if (strstr(this->meetings[i]->getComment(), comment)) {
            cout << *this->meetings[i] << endl;
        }
    }
}

bool saveByWorkHours(const char* startTime, const char* endTime) {
    
}

char** findDate(const char*, size_t, const char*, const char*);
