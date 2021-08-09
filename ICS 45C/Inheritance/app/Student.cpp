// Student.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// Definition of the Student class' member functions.

#include <algorithm>
#include <sstream>
#include "Student.hpp"



// Creating a Student object is going to set off a chain of events, and it's
// important to understand what those events are and in what order they occur.
//
// (1) Memory is allocated, large enough to store a Student object
// (2) Student's constructor is called
// (3) As its first act, Student's constructor will call Person's constructor,
//     because Person is a base class of Student.  (In other words, an object
//     needs to be initialized as a Person before it can be specialized into a
//     Student.)  Because Person's constructor requires parameters, we have to
//     pass them somewhere; the right place to do it, since it has to happen
//     first, is as this constructor's first initializer.
// (4) Person's constructor initializes all of the mebers of Person using its
//     initializers (or defaults, for any that don't have initializers).
//     Members are initialized in the order that they're listed in Person's
//     class declaration.
// (5) The body of the Person constructor is executed.
// (6) The rest of Student's initializers are executed, initializing all of
//     the member variables introduces in Student's class declaration.  Again,
//     these members are initialized in the order that they're listed in the
//     class declaration.
// (7) The body of the Student constructor is executed.

Student::Student(const std::string& name, unsigned int age, unsigned int id)
    : Person{name, age}, id{id}
{
}


// Note, too, that destroying a Student sets off the inverse chain of events:
//
// (1) The body of Student's destructor is executed.
// (2) All of Student's member variables (those not declared in Person) are
//     destroyed in the reverse of the order they're declared in the Student
//     class declaration.
// (3) The body of Person's destructor is executed.
// (4) All of Person's member variables are destroyed, again in the reverse of
//     the order they're declared in the Person class declaration.



unsigned int Student::getId() const
{
    return id;
}


const std::vector<unsigned int>& Student::getCourses() const
{
    return courses;
}


void Student::addCourse(unsigned int courseId)
{
    // This is an example of using the generic algorithm "find" from the
    // standard library.  It takes two iterators (a range of values to
    // search) and a value to search for; it returns an iterator referring
    // to where the value was found (or the "end" iterator if it wasn't
    // found at all).

    if (std::find(courses.begin(), courses.end(), courseId) == courses.end())
    {
        courses.push_back(courseId);
    }
}


void Student::dropCourse(unsigned int courseId)
{
    // I intend to use the iterator returned from find() a couple of times,
    // but I don't see a good reason why I should want to write the entire
    // type declaration on i.

    auto i = std::find(courses.begin(), courses.end(), courseId);

    if (i != courses.end())
    {
        courses.erase(i);
    }
}



// Remember that you only use the word "virtual" in the class declaration, not
// in the function's definition
std::string Student::toString() const
{
    std::ostringstream oss;

    // You can call the base class version of a member function by specifying
    // its full name (including the class)
    oss << Person::toString() << " (ID#" << id << ")";
    oss << " - " << courses.size() << " courses";
    
    return oss.str();
}

