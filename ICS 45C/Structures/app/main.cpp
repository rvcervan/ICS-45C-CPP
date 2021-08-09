// main.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// Here, we declare and use a Date struct in various ways.  As I said in
// lecture, there are plenty of reasons why implementing a calendar date
// (solely) this way is problematic, but it serves as a simple example
// for us here.

#include <iostream>


// This is a struct declaration.  It consists of the word "struct", followed
// by a name for the struct, followed by a list of member variables surrounded
// by curly braces.  A struct declaration introduces a new type, which means
// that we can now declare variables of this type, create pointers and
// references to objects of this type, and so on.

struct Date
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

// Note that the semicolon terminating the declaration of this struct is not
// optional; it's got to be there!  (The technical reason is that a struct
// declaration can also include a variable name between the closing curly
// brace and the semicolon, which defines a new variable of the new type,
// though this is a syntax that isn't seen often anymore.)




// Dates can be created statically, in which case they are allocated on the
// run-time stack.  When we have a variable whose type is a struct, we can
// access its members using the '.' operator, which can be either an lvalue
// or an rvalue.

void creatingDatesStatically()
{
    std::cout << "creatingDatesStatically" << std::endl;

    Date date;
    date.year = 2018;
    date.month = 10;
    date.day = 18;

    std::cout << date.year << "-" << date.month << "-" << date.day << std::endl;

    // We can also use initializer lists to initialize structs that have
    // been statically-allocated.
    Date date2{2019, 11, 1};
    
    std::cout << date2.year << "-" << date2.month << "-" << date2.day << std::endl;
    std::cout << std::endl;
}



// Dates can also be created dynamically, using the "new" operator, in which
// case they are allocated on the heap.  Syntactically, there are no surprises
// in the creation; it's just like dynamically allocating an int.  However,
// there is one important caveat: when accessing a struct through a pointer,
// you use the '->' operator instead of the '.' operator to access a member.

void creatingDatesDynamically()
{
    std::cout << "creatingDatesDynamically" << std::endl;

    // This is how you dynamically allocate a Date.  Create it using "new",
    // just like you would an int, which will give you back a pointer to
    // the newly-allocated struct.
    Date* dynamicDate = new Date;

    // Since dynamicDate is a pointer, you'll find that you can't use '.'
    // to access a member.
    //
    // dynamicDate.year = 2018;   // <-- this would be an error
    //
    // The reason is because '.' means "Assuming the thing on the left is
    // something that has members, access the member named on the right."
    // Structs have members.  Pointers don't.
    //
    // You can't do this either:
    //
    // *dynamicDate.year = 2018;
    //
    // but for different reasons.  The '.' operator has a higher precedence
    // than '*' does.  So you can override precedence and do this:
    //
    // (*dynamicDate).year = 2018;
    //
    // but almost nobody does this, because (a) it's ugly as sin, and
    // (b) there's a better syntactic alternative: the '->' operator.
    //
    // '->' means "Assuming the thing on the left is a pointer to something
    // that has members, follow the pointer and *then* access a member
    // of the thing it points to."  So this becomes legal:
    dynamicDate->year = 2018;
    dynamicDate->month = 10;
    dynamicDate->day = 18;

    // Note that we could also have initialized our dynamically-allocated
    // struct using an initializer list.
    //
    // Date* dynamicDate = new Date{2018, 10, 18};

    // Here is a great example of why you should want to be careful about
    // including spaces around your operators.  This is reasonably
    // decent-looking, if not a little confusing with the < and > characters
    // that show up.
    std::cout << dynamicDate->year << "-" << dynamicDate->month << "-" << dynamicDate->day << std::endl;

    // This is legal, but you'd have to be really insane to want to write it
    // (and you'd likely go insane trying to read it).  Let your code breathe!
    std::cout<<dynamicDate->year<<"-"<<dynamicDate->month<<"-"<<dynamicDate->day<<std::endl;

    // But whenever you allocate something dynamically, you'll need to
    // deallocate it somewhere using "delete".  Deleting a dynamically-
    // allocated struct is just like deleting a dynamically-allocated
    // int; use the "delete" operator and give it a pointer to the struct
    // you want to delete.
    delete dynamicDate;

    std::cout << std::endl;
}




// If we're curious, we can use the sizeof() function and pointers to ask
// the compiler to tell us more about the layout of a Date.  I don't find
// myself doing this kind of thing very often in practice, but it's a useful
// way to explore some of the underlying details that are otherwise hard to
// see.
//
// I've written a utility function that compares two pointers and shows
// the difference between them in bytes (i.e., how many bytes away from the
// second pointer, in terms of bytes, is the first pointer?).  Because of
// the way pointer arithemtic works in C++, this is actually no small feat,
// involving some rather strange-looking incantations.

int getOffset(void* basePointer, void* offsetPointer)
{
    return static_cast<int>(
        static_cast<char*>(offsetPointer) - static_cast<char*>(basePointer));
}


void dateLayoutExample()
{
    std::cout << "dateLayoutExample" << std::endl;
    std::cout << "Date Layout" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "Total size: " << sizeof(Date) << std::endl;

    Date d;
    std::cout << "year (offset): " << getOffset(&d, &(d.year)) << std::endl;
    std::cout << "month (offset): " << getOffset(&d, &(d.month)) << std::endl;
    std::cout << "day (offset): " << getOffset(&d, &(d.day)) << std::endl;
    std::cout << std::endl;
}




// Structs can be passed as parameters, by value and by reference.  Passing
// a struct by value entails making a copy of all of its members, which can
// be expensive if it's large; in general, it's no different to pass an
// n-member struct by value than it would be to pass the n members as
// separate parameters, but if n is large (or the members themselves are
// large objects), this can still be prohibitive.
//
// When passing by value, changes to the copy do not affect the original;
// when passing by reference, changes to the copy do (unless it's passed by
// const reference, in which case changes to the copy become impossible).

void fooValue(Date d)
{
    d.year++;
    d.month++;
    d.day++;
}

void fooReference(Date& d)
{
    d.year++;
    d.month++;
    d.day++;
}

void fooConstReference(const Date& d)
{
    // This would be illegal, because d is a reference to a const Date.
    // Const structs are treated as though every member was declared const,
    // so no members can be changed.
    //
    // d.year++;   // <-- illegal!
    //
    // However, accessing the members would be legal, so we could do this:
    std::cout << d.year << "-" << d.month << "-" << d.day << std::endl;
}

void passingStructsAsParameters()
{
    std::cout << "passingStructsAsParameters" << std::endl;

    Date day;
    day.year = 1992;
    day.month = 11;
    day.day = 14;

    fooConstReference(day);
    fooValue(day);
    fooConstReference(day);
    fooReference(day);
    fooConstReference(day);

    std::cout << std::endl;
}




int main()
{
    creatingDatesStatically();
    creatingDatesDynamically();
    passingStructsAsParameters();
    dateLayoutExample();

    return 0;
}

