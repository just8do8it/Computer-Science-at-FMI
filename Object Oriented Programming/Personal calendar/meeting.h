#ifndef MEETING_H
#define MEETING_H

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
    const char* getStartTime() const;
    const char* getEndTime() const;
};

bool operator==(const Meeting&, const Meeting&);
bool operator!=(const Meeting&, const Meeting&);

bool operator<(const Meeting&, const Meeting&);

#endif