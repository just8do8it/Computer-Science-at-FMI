#include <iostream>
#include <cstring>
#include <fstream>
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
    if (this->size - 1 == this->capacity / 3) {
        resize(this->capacity / 2);
    }

    bool found = false;

    for (int i = 0; i < this->size; ++i) {
        if (*this->meetings[i] == meeting) {
            found = true;
            delete this->meetings[i];
        }
        if (found) {
            this->meetings[i] = this->meetings[i + 1];
            if (i == this->size - 2) {
                break;
            }
        }
    }

    if (found) {
        delete this->meetings[this->size];
        this->size--;
        return true;
    }
    
    return false;
}

