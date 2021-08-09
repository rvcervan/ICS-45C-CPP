// Person.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// Defines the member functions of the Person class

#include <sstream>
#include "Person.hpp"



// Declaring a namespace with no name is the C++ way to declare a function
// that is local to a source file (i.e., the linker will not see it).  This
// is a good idea when you're writing little utility functions with simple
// names, which aren't likely to have much use outside of their source file.
// Notice, too, that I didn't declare enforceNameLength() in Person.hpp;
// this is because it won't be available to other source files anyway, since
// I've hidden it from the linker.
namespace
{
    // enforceNameLength() takes a string and returns a copy of it that has
    // been truncated to MAX_NAME_LENGTH characters, if necessary.  Since this
    // is not a member function of the Person class, notice that I've
    // referred to the MAX_NAME_LENGTH constant as "Person::MAX_NAME_LENGTH".
    // This is legal, though, since MAX_NAME_LENGTH is public.
    std::string enforceNameLength(const std::string& name)
    {
        if (name.length() > Person::MAX_NAME_LENGTH)
        {
            // The substr() function retruns a substring of a string.
            return name.substr(0, Person::MAX_NAME_LENGTH);
        }
        else
        {
            return name;
        }
    }
}

// You might rightfully wonder why I haven't just made enforceNameLength()
// a private member function of Person.  I tend to like to leave functions
// outside of class declarations when I can; if the function doesn't need
// access to any of the members of a class -- if it's truly just a function
// that doesn't require membership -- it's better to just leave it out, to
// keep the class declaration shorter and simpler, and to allow the function
// to be used in more contexts (e.g., passed as a parameter to generic
// algorithms in the standard library).  C++ gives us the ability to have
// functions that aren't a part of a class for the simple reason that not
// all functions *need* to be a part of a class.



// The Person constructor enforces a length restriction on the name length by
// calling the enforceNameLength() function above before initializing the
// names.
Person::Person(const std::string& name, unsigned int age)
    : name{enforceNameLength(name)}, age{age}
{
}


std::string Person::getName() const
{
    return name;
}


unsigned int Person::getAge() const
{
    return age;
}


void Person::setName(const std::string& name)
{
    this->name = enforceNameLength(name);
}


void Person::setAge(unsigned int age)
{
    this->age = age;
}


std::string Person::toString() const
{
    // Slick, huh?  ostringstream is a "string output stream" class, which
    // allows you to build strings in the same way you write to cout: by
    // by using a chain of calls to the << operator (and all of the other
    // formatting tools provided by cout).  Since ostringstream is derived
    // from the same base class as the other output streams, the same <<
    // operator that can write objects to cout can write them to a string
    // stream, so no special handling needs to be added to other classes
    // to enable this.

    std::ostringstream oss;
    oss << name << ", age " << age;
    
    // When you're finishing building the string, you can extract a copy
    // of it by calling the str() function on the stream.
    return oss.str();
}

