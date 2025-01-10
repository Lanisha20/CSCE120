// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <stdexcept>
using std::ostream;
using std::istream;


class MyString {
    private:
        char* myStr;
        size_t cap;
        size_t len;

    public: 
        MyString();
        MyString(const char* s); // construcotr
        MyString(const MyString& other); // constructor copy
        ~MyString(); //deconstructor
        MyString& operator=(const MyString& other); 
        MyString& operator+= (const MyString& str); // assignment ooerator
        friend ostream& operator<< (ostream& os, const MyString& str);
        friend bool operator== (const MyString& lhs, const MyString& rhs);
        friend MyString operator+ (const MyString& lhs, const MyString& rhs);
        // void print() const; //  prints string
        void resize (size_t x);
        size_t capacity() const; // const is needed here tho?
        size_t size() const;
        size_t length() const; // gets length
        const char* data() const;
        bool empty();
        const char& front() const;
        const char& at(size_t position) const;
        void clear();
        size_t find (const MyString& str, size_t position = 0) const noexcept;
};

#endif