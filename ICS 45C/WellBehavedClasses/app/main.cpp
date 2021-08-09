// main.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// This source file exercises our ArrayList class in a variety of ways, so you
// can see the various effects of having the class be well-behaved.  Don't
// be bashful about writing your own main() function to replace mine with
// your own experiments; it'll take some experimentation to really understand
// what causes copy constructors, assignment operators, and destructors to be
// called, which is an important part of understanding this example.

#include <iostream>
#include "ArrayList.hpp"


// This is a utility function that prints the contents of an ArrayList
// to the console, which I use throughout this source file.
void printAll(const ArrayList& a)
{
    std::cout << "ArrayList: size = " << a.size();
    std::cout << ", capacity = " << a.capacity() << std::endl;

    for (unsigned int i = 0; i < a.size(); i++)
    {
        std::cout << "    " << i << ": " << a.at(i) << std::endl;
    }
}


// This function accepts an ArrayList by value.  Note that while we're allowed
// to make changes to it, those changes will not be reflected in the original.
void passingArrayListByValue(ArrayList a)
{
    a.add("indeed");
    a.add("because");
    a.add("things");
    a.add("are");
    a.add("going");
    a.add("very");
    a.add("well");
    printAll(a);
}


// This function accepts an ArrayList by reference, allowing us to make changes
// to it that will be reflected in the original.  Here, we introduce two
// changes: adding a new element to the end and changing an element using
// at() as an lvalue.
void passingArrayListByReference(ArrayList& a)
{
    a.add("indeed");
    a.at(2) = "ecstatic";
    printAll(a);
}
// It may seem very strange that "a.at(2)" is allowed to be placed on the
// left-hand side of an assignment, but remember what this function returns:
// a reference to a string.  Given a reference to a string, you can assign a
// value into that string.  Since the ArrayList is returning a reference to one
// of the strings actually stored in its own array, assigning to a.at(2)
// actually changes the string in that array.


// This function demonstrates the effect of constness.  I've commented a
// few lines out that show things that are illegal to do to a const
// ArrayList, because they introduce changes to the ArrayList.
void theEffectOfConst(const ArrayList& a)
{
    std::cout << "theEffectOfConst" << std::endl;

    // We can't add to a const ArrayList, so this statement is illegal.
//    a.add("hello");

    // Because a is a const reference, calling a.at(3) is a call to the
    // const version of the function, which returns a const reference to a
    // string.  You can't assign to a const reference to a string (because
    // it represents a promise not to change that string), so this statement
    // is illegal.
//    a.at(3) = "Boo";

    // Reading a value using a.at(2) is fine, though.
    std::cout << a.at(2) << std::endl;

    // Copying a into a separate ArrayList, as well as modifying that copy, is
    // fine, because it doesn't change the original.
    ArrayList a2 = a;
    a2.add("hello");

    // Trying to acquire a non-const reference to a is problematic, though,
    // because that would introduce a way to change a, which we've promised
    // not to change.  So this statement is illegal.
//    ArrayList& a3 = a;

    printAll(a);
    printAll(a2);
}


int main()
{
    ArrayList a1;
    a1.add("Alex");
    a1.add("is");
    a1.add("happy");
    a1.add("today");
    printAll(a1);

    passingArrayListByValue(a1);
    printAll(a1);

    passingArrayListByReference(a1);
    printAll(a1);

    ArrayList a2{a1};
    a2.add("happily");

    ArrayList a3 = a1;
    a3.add("here");

    a1 = a3;

    printAll(a1);
    printAll(a2);
    printAll(a3);

    theEffectOfConst(a1);

    return 0;
}

