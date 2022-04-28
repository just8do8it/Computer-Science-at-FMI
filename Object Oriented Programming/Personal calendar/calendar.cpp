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
    ifstream file(filename);
    size_t start = file.tellg();
    file.seekg(0, ios::end);
    size_t end = file.tellg();
    file.seekg(0, ios::beg);

    if (end - start == 0) {
        this->filename = new char[strlen(filename) + 1];
        strcpy(this->filename, filename);

        this->capacity = DEFAULT_CAPACITY;
        this->meetings = new Meeting*[this->capacity];

        this->size = 0;
    } else {
        size_t size;
        file >> size;
        file.ignore(2);

        this->filename = new char[strlen(filename) + 1];
        strcpy(this->filename, filename);

        this->size = size;
        this->capacity = this->size * 2;
        this->meetings = new Meeting*[this->capacity];
        for (int i = 0; i < size; ++i) {
            file >> this->meetings[i];
            file.ignore();
        }
    }
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

void Calendar::addMeeting(const Meeting& meeting) {
    if (this->size + 1 == this->capacity) {
        resize(this->capacity * 2);
    }

    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            throw "Meeting already in calendar!";
        }
    }

    for (int i = 0; i < this->size; ++i) {
        if (strcmp(this->meetings[i]->getDate(), meeting.getDate()) == 0) {
            size_t currStartTime = getTimeInMinutes(this->meetings[i]->getStartTime());
            size_t currEndTime = getTimeInMinutes(this->meetings[i]->getEndTime());
            size_t newStartTime = getTimeInMinutes(meeting.getStartTime());
            size_t newEndTime = getTimeInMinutes(meeting.getEndTime());

            if ((newStartTime > currStartTime && newStartTime < currEndTime) || 
                (newEndTime > currStartTime && newEndTime < currEndTime)) {
                    throw "Meeting overlapping with other meetings!";
                }
        }
    }

    this->meetings[this->size] = new Meeting(meeting);
    this->size++;
    sort();
}

void Calendar::removeMeeting(const Meeting& meeting) {
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
                return;
            }
            this->meetings[i] = this->meetings[i + 1];
        }
    }

    if (found) {
        delete this->meetings[this->size - 1];
        this->size--;
    } else {
        throw "Such meeting doesn't exist!";
    }
}

bool Calendar::save() {
    ofstream file(this->filename);

    if (file.fail()) {
        return false;
    }

    file << this->size << endl << endl;

    for (int i = 0; i < this->size; ++i) {
        file << *this->meetings[i] << endl;
    }

    file << endl;

    file.close();

    return true;
}


void Calendar::printForDay(const char* date) {
    bool exists = false;
    cout << endl;
    for (int i = 0; i < this->size; ++i) {
        if (strcmp(this->meetings[i]->getDate(), date) == 0) {
            if (!exists) exists = true;
            cout << *this->meetings[i] << endl;
        }
    }

    cout << endl;

    if (!exists) {
        throw "No meetings for that day!";
    }
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
    if (!dateIsValid(date)) return false;

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
            if (!timeIsValid(startTime, this->meetings[i]->getEndTime()))
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
            if (!timeIsValid(this->meetings[i]->getStartTime(), endTime))
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

void Calendar::printMeetingsByName(const char* str) {
    bool found = false;
    cout << endl;
    for (int i = 0; i < this->size; ++i) {
        if (strstr(this->meetings[i]->getName(), str)) {
            if (!found) found = true;
            cout << *this->meetings[i] << endl;
        }
    }
    cout << endl;

    if (!found) {
        throw "No matching meetings!";
    }
}

void Calendar::printMeetingsByComment(const char* str) {
    bool found = false;
    cout << endl;
    for (int i = 0; i < this->size; ++i) {
        if (strstr(this->meetings[i]->getComment(), str)) {
            if (!found) found = true;
            cout << *this->meetings[i] << endl;
        }
    }

    cout << endl;

    if (!found) {
        throw "No matching meetings!";
    }
}

void Calendar::saveByWorkHours(const char* startDate, const char* endDate) {
    bool first = true;
    Calendar result("yyyy-mm-dd.txt");

    for (int i = 0; i < this->size; ++i) {
        Meeting tempStart(this->meetings[i]->getName(), this->meetings[i]->getComment(), startDate,
                        this->meetings[i]->getStartTime(), this->meetings[i]->getEndTime());

        Meeting tempEnd(this->meetings[i]->getName(), this->meetings[i]->getComment(), endDate,
                        this->meetings[i]->getStartTime(), this->meetings[i]->getEndTime());

        if (tempStart < *this->meetings[i] && *this->meetings[i] < tempEnd) {
            first = false;            
            result.addMeeting(*this->meetings[i]);
        }
    }

    if (first) throw "No meetings in that period!";

    for (int i = 0; i < result.size - 1; ++i) {
        for (int j = 0; j < result.size - i - 1; ++j) {
            size_t diff1 = getTimeInMinutes(result.meetings[j]->getEndTime()) - 
                            getTimeInMinutes(result.meetings[j]->getStartTime());

            size_t diff2 = getTimeInMinutes(result.meetings[j + 1]->getEndTime()) - 
                            getTimeInMinutes(result.meetings[j + 1]->getStartTime());

            if (diff1 > diff2) {
                Meeting *temp = result.meetings[j];
                result.meetings[j] = result.meetings[j + 1];
                result.meetings[j + 1] = temp;
            }
        }
    }

    char str[5] = ".txt";
    char filename[15];
    char copy[11], newDate[11];
    strcpy(copy, result.getMeetings()[0]->getDate());

    for (int i = 0; i < 10; ++i) {
        if (i < 4) {
            newDate[i] = copy[i + 6];
        } 
        else if (i < 8) {
            newDate[i] = copy[i - 2];
        }
        else {
            newDate[i] = copy[i - 8];
        }
    }
    newDate[10] = '\0';

    strcpy(filename, strcat(newDate, str));
    strcpy(result.filename, filename);

    result.save();
}

bool Calendar::isThereTime(const char* startDate, const char* endDate, size_t duration, const char* startTime, const char* endTime) {    bool found = false;
    size_t startDateDays = getDateInDays(startDate);
    size_t endDateDays = getDateInDays(endDate);
    size_t startMinutes = getTimeInMinutes(startTime);
    size_t endMinutes = getTimeInMinutes(endTime);

    Calendar **chosen = new Calendar*[7];
    size_t size = 0;
    chosen[0] = new Calendar("");
    chosen[0]->addMeeting(*this->meetings[0]);

    
    for (int i = 1, j = 0, k = 0; i < this->size; ++i) {
        if (startDateDays < getDateInDays(this->meetings[i]->getDate()) &&
            getDateInDays(this->meetings[i]->getDate()) < endDateDays) {
            
            if (strcmp(this->meetings[i]->getDate(), chosen[j]->meetings[k]->getDate()) != 0) {
                j++;
                chosen[j] = new Calendar("");
                chosen[j]->addMeeting(*this->meetings[i]);
                k = 0;
                size++;
            } else {
                chosen[j]->addMeeting(*this->meetings[i]);
                k++;
            }
        }
    }

    cout << "here" << endl;

    for (int i = 0; i < size; ++i) {
        for (int i = 0; i < chosen[i]->size; ++i) {
            size_t lower = getTimeInMinutes(chosen[i]->meetings[i]->getStartTime());
            size_t upper = getTimeInMinutes(chosen[i]->meetings[chosen[i]->size - 1]->getEndTime());

            size_t diff1 = 0, diff2 = 0;
            if (lower > startMinutes || endMinutes > upper) {
                if (lower > startMinutes) diff1 = lower - startMinutes;
                if (endMinutes > upper) diff2 = endMinutes - upper;

                if (diff1 >= duration || diff2 >= duration) {
                    if (diff1 >= duration) {
                        cout << endl << chosen[i]->meetings[i]->getDate() << ": " << "between " 
                            << startTime << " and " << chosen[i]->meetings[i]->getStartTime() << endl;
                    }
                    if (diff2 >= duration) {
                        cout << endl << chosen[i]->meetings[i]->getDate() << ": " << "between " 
                            << chosen[i]->meetings[i]->getEndTime() << " and " << endTime << endl;
                    }

                    found = true;
                }
            }
        }
    }
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < chosen[i]->size; ++j) {
            size_t end = getTimeInMinutes(chosen[i]->meetings[j]->getEndTime());
            size_t start = getTimeInMinutes(chosen[i]->meetings[j + 1]->getStartTime());
            
            if (start - end >= duration) {
                cout  << endl << chosen[i]->meetings[i]->getDate() << ": " << "between " << chosen[i]->meetings[j]->getEndTime() << " and "
                                << chosen[i]->meetings[j + 1]->getStartTime() << endl;
                
                found = true;
            }
        }
    }

    cout << endl;

    return found;
}
