#ifndef STRING_H
#define STRING_H
#include <iostream>
using namespace std;

class String {
    char *data;

    void copyFrom(const String&);
    void free();

public:
    String();
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    ~String();

    const char* getData() const;
    String& operator+=(const String&);
    String& operator+=(const char*);
    char operator[](size_t) const;
    char& operator[](size_t);
    bool operator==(const String&) const;
    bool operator!=(const String&) const;
    bool operator>(const String&) const;
    bool operator<(const String&) const;

};

ostream& operator<<(ostream&, const String&);

#endif