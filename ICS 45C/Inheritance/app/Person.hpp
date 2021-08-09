// Person.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// Declares the Person class, which will be a base class for a derived class
// called Student.  (If you're looking for some practice, here's an exercise:
// write yourself a derived class called Employee and make it do something
// interesting and different from Student.)
//
// This example adds a few details we didn't cover in lecture, but is otherwise
// a mirror of what we covered.

#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>



class Person
{
public:
    // This constant indicates the maximum length that a person's name
    // might be.
    static constexpr int MAX_NAME_LENGTH = 50;


    // This constructor requires Persons to have a name and an age specified
    // for them at construction time.
    Person(const std::string& name, unsigned int age);


    // Marking destructors virtual -- when you're going to be using inheritance
    // -- actually turns out to be important.  Why?  Consider this situation:
    //
    //     Person* p = new Student{"Alex Thornton", 43};
    //     delete p;
    //
    // Remember that polymorphic behavior (i.e., choosing a function on the
    // basis of what kind of object it was called on) is not the default in
    // C++.  This applies to destructors, too, which are effectively member
    // functions that are being called through pointers.  If you want a
    // destructor to be called polymorphically -- and if you're using
    // inheritance and have member variables that need to be cleaned up,
    // this is something you want! -- you have to declare them to be virtual.
    //
    // The "= default" bit is a shorthand way of saying "While I'm declaring
    // this destructor (because I need to establish that it's virtual), I
    // don't need it to do anything other than what the default destructor
    // -- the one that would be generated for me automaticaly -- does."
    // This prevents me from having to have an empty implementation.
    virtual ~Person() = default;


    // These "getters" and "setters" provide the controlled ability to read
    // and modify the values of a Person's member variables
    std::string getName() const;
    unsigned int getAge() const;

    void setName(const std::string& name);
    void setAge(unsigned int age);


    // As an example of a virtual function for these classes, here is a
    // toString() function that returns a string representation of the data
    // in a Person object.
    virtual std::string toString() const;

private:
    std::string name;
    unsigned int age;
};



#endif // PERSON_HPP
