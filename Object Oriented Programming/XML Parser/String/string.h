#ifndef STRING_HH
#define STRING_HH
#include <iostream>

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

    friend std::istream& operator>>(std::istream&, String&);
};

std::ostream& operator<<(std::ostream&, const String&);

#endif