// main.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// A few examples of creating and manipulating Person and Student objects

#include <iostream>
#include "Person.hpp"
#include "Student.hpp"


void oneYearOlderAndPrint(Person& p)
{
    p.setAge(p.getAge() + 1);
    std::cout << p.toString() << std::endl;
}


int main()
{
    Person p1{"Alex Thornton", 41};
    Student s2{"Joe Student", 21, 12345678};
    s2.addCourse(10001);
    s2.addCourse(10002);


    // Since Person references can point to any kind of object that is some
    // kind of Person (and Students are Persons, because of the inheritance
    // relationship), it's legal to pass either a Person or a Student object
    // to the oneYearOlderAndPrint() function.  And since toString() is
    // virtual, polymorphism kicks in, so the Student is printed differently
    // than the Person is.
    oneYearOlderAndPrint(p1);
    oneYearOlderAndPrint(s2);


    // This is called "slicing".  Only the name and age member variables are
    // copied from s2 into p3, because p3 is a Person object (not a pointer or
    // reference) and doesn't have a place to copy the ID or the vector of
    // courses.
    Person p3 = s2;
    oneYearOlderAndPrint(p3);


    // Pointers aren't much different than they've been so far, except that
    // they're able to point to objects of related types (i.e., since Students
    // are Persons, Person pointers can point to Student objects).
    Person* p = new Student{"Jane Student", 25, 23456789};
    std::cout << p->toString() << std::endl;
    delete p;


    return 0;
}

