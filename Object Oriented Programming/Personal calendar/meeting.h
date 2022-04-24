#ifndef MEETING_H
#define MEETING_H
#include <iostream>
using namespace std;

class Meeting {
    char *name;
    char *comment;
    char date[11]; 		// dd-mm-yyyy
    char startTime[6]; 	// hh:mm
    char endTime[6];   	// hh:mm

    void copyFrom(const Meeting&);
    void free();

public:
    static bool dateIsValid(const char*);
    static bool timeIsValid(const char*, const char*);
    Meeting(const char*, const char*, const char*, const char*, const char*);
    Meeting(const Meeting&);
    Meeting& operator=(const Meeting&);
    ~Meeting();

    const char* getName() const;
    const char* getComment() const;
    const char* getDate() const;
    const char* getEndTime() const;
    const char* getStartTime() const;

    void setName(const char*);
    void setComment(const char*);
    void setDate(const char*);
    void setStartTime(const char*);
    void setEndTime(const char*);
};

size_t getTimeInMinutes(const char*);

ostream& operator<<(ostream&, const Meeting&);

bool operator==(const Meeting&, const Meeting&);
bool operator!=(const Meeting&, const Meeting&);

bool operator<(const Meeting&, const Meeting&);

#endif