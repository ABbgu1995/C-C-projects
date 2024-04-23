#ifndef UNTITLED7_GENERALEXCEPTION_H
#define UNTITLED7_GENERALEXCEPTION_H
#include <iostream>
#include <exception>
using namespace std;
class Error: public exception{
public:
    Error()= default;;
    virtual void handle () const=0;

};
// class to handle errors in general details
class invalidDetailsException: public Error{
public:
    invalidDetailsException(){};
    virtual void handle () const { cout << "Please enter valid details\n";}
};

// class to handle errors in party name
class invalidNameException: public Error{
public:
    invalidNameException(){};
    virtual void handle () const { cout << "Please enter valid name\n";}
};

// class to handle errors in id of politician
class invalidIDException: public Error{
public:
    invalidIDException(){};
    virtual void handle () const { cout << "Please enter valid id\n";}
};

// class to handle errors in memory allocation
class MemoryErrors: public Error{
public:
    MemoryErrors(){};
    virtual void handle () const { cout << "Memory error, finish program\n";}

};
#endif //UNTITLED7_GENERALEXCEPTION_H
