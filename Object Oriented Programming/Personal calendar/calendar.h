#ifndef CALENDAR_H
#define CALENDAR_H
#include <iostream>
#include "meeting.h"
using namespace std;

class Calendar {
    char *filename;
    Meeting **meetings;
    size_t size;
    size_t capacity;

    void copyFrom(const Calendar&);
    void free();
public:
    Calendar(const char*);
    Calendar(const char*, Meeting**, size_t, size_t);
    Calendar(const Calendar&);
    Calendar& operator=(const Calendar&);
    ~Calendar();

    const char* getFilename() const;
    Meeting** getMeetings() const;
    size_t getSize() const;
    size_t getCapacity() const;

    void resize(size_t);
    void sort();
    bool addMeeting(const Meeting&);
    bool removeMeeting(const Meeting&);
    bool save();
    bool printFile() const;
    // bool deleteCalendar();
    Meeting** getMeetingsByName(const char*);
    Meeting** getMeetingsByComment(const char*);
    bool saveByWorkHours(const char*, const char*);

    void changeName(const Meeting&, const char*);
    void changeComment(const Meeting&, const char*);
    
    bool changeDate(const Meeting&, const char*);
    bool changeStartTime(const Meeting&, const char*);
    bool changeEndTime(const Meeting&, const char*);

    char** findDate(const char*, size_t, const char*, const char*);
};

#endif