// TODO: Implement this source file
#include "MyString.h"
#include "Rover.h"
#include <iostream>

using namespace std;


// MyString()
MyString::MyString() : len(0), cap(1), myStr(new char[1]) { // initializing a new string
    myStr[0] = '\0';  // empty string
}

// MyString(const char* s)
// MyString(const MyString& other)
MyString::MyString(const MyString& str) {
    len = str.len;
    cap = str.cap;
    myStr = new char[cap];
    size_t i = 0;
    while (i < len) { // might change to for loop if this doesn't work properly
        myStr[i] = str.myStr[i];
        i++;
    }
    myStr[len] = '\0';
}

MyString::MyString(const char* s): len(0), cap(1), myStr(nullptr) {
    if (s == nullptr) {
        myStr = new char[cap];
        myStr[0] = '\0';
    }
    else {
        while (s[len] != '\0') { // might switch these to for loops later
            len++;
        }
        cap = len + 1;
        myStr = new char[cap]; // allocate and copy characters over
        size_t i = 0;
        while (i < len) {
            myStr[i] = s[i];
            i++;
        }
        myStr[len] = '\0';
    }
}

MyString::~MyString() {
    delete[] myStr;
}

// MyString& operator=(const MyString& other)
MyString& MyString::operator= (const MyString& str){
    if (this != &str) {
        delete[] myStr;
        myStr = new char[str.cap]; // copy over content
        for (int i = 0; i < str.cap; i++) {
            myStr[i] = str.myStr[i];
        }
        cap = str.cap; // copy capacity and lenght
        len = str.len;
    }
    return *this; // return current object reference
}

// MyString& operator+= (const MyString& str); // assignment ooerator
MyString& MyString::operator+=(const MyString& str) {
    int cap2 = len + str.len; // new cap and allocate new memory
    char* myStr2 = new char[cap2 + 1];
    int append = 0;
    for (int i = 0; i < len; i++) {
        myStr2[i] = myStr[i]; // copy over current content
    }
    for (int i = 0; i < str.len; i++) {
        append = len + i;
        myStr2[append] = str.myStr[i]; // append contents
    }
    myStr2[cap2] = '\0';
    delete[] myStr; // delete old memory
    myStr = myStr2;
    len = cap2; // assign new capacity and length
    cap = cap2 + 1;
    return *this; // return currenr object
}

ostream& operator<< (ostream& os, const MyString& str) {
    os << str.data(); // inserting string content into stream
    return os;
}

// friend bool operator== (const MyString& lhs, const MyString& rhs)
bool operator==(const MyString& lhs, const MyString& rhs) {
    if (lhs.len == rhs.len) {
        for (size_t i = 0; i < lhs.len; ++i) {
            if (lhs.myStr[i] != rhs.myStr[i]) {
                return false; // return if mismatch found
            }
        }
        return true; // if all char match return true  
    }
    return false; // if lengths arent same return false
    /*if(lhs.len != rhs.len) {
        return false;
    }
    for(size_t i=0;i < rhs.len; ++i){
        if(rhs.myStr[i] != lhs.myStr[i]){
            return false;
        }
    }
    return true; */
}
// friend MyString operator+ (const MyString& lhs, const MyString& rhs)
MyString operator+(const MyString& lhs, const MyString& rhs){
    MyString string(lhs);
    string += rhs;
    return string;
}

void MyString::resize (size_t x) {
    len = x; 
    cap = x + 1;
}

size_t MyString::capacity() const {
    return cap;
}

size_t MyString::size() const {
    return len;
}

size_t MyString::length() const {
    return len;
}

const char* MyString::data() const {
    return myStr;
}


bool MyString::empty() {
    /*if(len == 0) {
        return true;
    }
    else {
        return false;
    } */
    return (len == 0); // will directly return true or false depending on truth valeu of that equality statemnt
}

const char& MyString::front() const {
    return myStr[0];
}

const char& MyString::at(size_t position) const {
    if (position >= len) {
            throw std::out_of_range("Character is out of range.");
        }
    return myStr[position];
}

// void clear();
void MyString::clear() {
    len = 0;
    if (cap > 1) {
        cap = 1;
    }
    myStr[0] = '\0';
}
// size_t find (const MyString& str, size_t position = 0) const noexcept;
size_t MyString::find (const MyString& val, size_t pos) const noexcept {
    size_t start = -1; // -1 means not found
    size_t n = 0;      // = index substring 'val'

    for (size_t i = pos; i < cap; i++) {
        if (myStr[i] == val.data()[n]) { // chekc if characters match
            if (start == -1) {
                start = i;
            }
            n++;
            if (val.data()[n] == '\0') {
                return start; // found substring
            }
        } 
        else {
            if (start != -1) {
                i = start;
                start = -1;
            }
            n = 0; //reset index in substring
        }
    }
    return start; // if not found
}

// the joys of locally compliling... now when i submit i actually get points :) AND I DONT HAVE 85 SUBMISSIONS