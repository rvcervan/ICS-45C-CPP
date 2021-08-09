// Student.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// Declares a Student class that inherits from the Person class.

#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <vector>

// We'll need to include the declaration of the Person class here,
// because the compiler will not be able to compile the Student class
// declaration (e.g., determine a layout for Student objects) without
// knowing the details of Person's class declaration.
#include "Person.hpp"



// To declare the Student class to inherit from the Person class, we use
// the colon (:) operator.  "public" indicates the type of inheritance.
// For now, go ahead and always say "public" and things will work as you
// expect.  There are other kinds of inheritance that are subtly different,
// but public will suffice for us (for now).

class Student : public Person
{
public:
    // Since the Person constructor will need to take a name and an age
    // as parameters, and the Student constructor will need to call the
    // Person constructor, it's sensible to have the Student constructor
    // take these parameters, too.
    Student(const std::string& name, unsigned int age, unsigned int id);


    // Just for fun, we'll say that student IDs are immutable, so I'll
    // write a "getter" but no "setter" for it
    unsigned int getId() const;


    // You can return a const reference from a function, in which case you'll
    // be able to return an actual value of a member variable (as opposed to
    // a copy of it) without being worried about the caller changing it.
    // This can be a useful performance optimization.
    const std::vector<unsigned int>& getCourses() const;
    void addCourse(unsigned int courseId);
    void dropCourse(unsigned int courseId);


    // Here, we're overriding the toString() function, so that it'll do
    // something different for Students than it does for other kinds
    // of Persons.  It's not necessary to mark toString() virtual here,
    // since it's already marked virtual in the Person class, but it's
    // a good practice (for readability), so I'll do it.
    virtual std::string toString() const override;

private:
    unsigned int id;
    std::vector<unsigned int> courses;
};



#endif // STUDENT_HPP
