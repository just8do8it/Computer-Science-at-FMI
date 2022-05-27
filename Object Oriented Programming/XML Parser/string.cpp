#include <cstring>
#include "string.h"
#define DEFAULT_CAPACITY 8

String::String() {
    this->data = new char[DEFAULT_CAPACITY];
}

void String::copyFrom(const String& other) {
    this->data = new char[strlen(other.getData()) + 1];
    strcpy(this->data, other.getData());
}

void String::free() {
    delete[] this->data;
}

String::String(const char* data) {
    this->data = new char[strlen(data) + 1];
    strcpy(this->data, data);
}

String::String(const String& other) {
    copyFrom(other);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

String::~String() {
    free();
}

const char* String::getData() const {
    return this->data;
}

String& String::operator+=(const String& other) {
    strcat(this->data, other.data);
    return *this;
}

String& String::operator+=(const char* data) {
    strcat(this->data, data);
    return *this;
}


char String::operator[](size_t index) const {
    return this->data[index];
}

char& String::operator[](size_t index) {
    return this->data[index];
}

bool String::operator!=(const String& other) const {
    return strcmp(this->data, other.data);
}

bool String::operator==(const String& other) const {
    return !(*this != other);
}

bool String::operator>(const String& other) const {
    return strcmp(this->data, other.data) > 0;
}

bool String::operator<(const String& other) const {
    return strcmp(this->data, other.data) < 0;
}

std::istream& operator>>(std::istream& in, String& str) {
    char buff[1024];
    in >> buff;
    delete[] str.data;
    str.data = new char[strlen(buff) + 1];
    strcpy(str.data, buff);

    return in;
}


std::ostream& operator<<(std::ostream& out, const String& str) {
    out << str.getData();
    return out;
}
