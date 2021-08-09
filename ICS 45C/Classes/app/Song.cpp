// Song.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// This source file contains the definitions of all of Song's member functions.


// The fact that we're including "Song.hpp" in "Song.cpp" is not optional.
// The compiler will need the declaration of the Song class in order to
// compile the code that follows.
#include "Song.hpp"


// Notice that each of the functions defined here have funny-looking names
// that begin with "Song::".  This is no accident; it's a requirement.  At
// the point in the code where this comment lies, Song's class declaration
// has already been seen (because we included "Song.hpp" above), but it's also
// been closed (because it ended with a curly brace and semicolon).  So
// everything we're writing here is outside of the scope of Song.  In order
// to define a function that is in a scope other than the current one, we
// use the "::" operator.  We could read "Song::getArtist()" to mean "the
// getArtist() function in the scope of Song".  Since the compiler has seen
// that Song is a class, and that Song has member functions declared with
// the same signatures as the ones I'm defining here, it will realize that
// these are definitions for the member functions declared in "Song.hpp".



// Constructors actually do two jobs, in this order:
//
// (1) Construct the member variables
// (2) Anything else they need to do
//
// The first part, the construction of the member variables, occurs before
// the body of the constructor (the part in the curly braces) runs.  The
// member variables are constructed in the order that they're declared in
// the class declaration -- so, in our case, artist is constructed first,
// followed by title.
//
// Since constructing the member variables may involve calling constructors
// that need arguments passed to them, there is a syntax that you can use
// for calling these constructors, by writing a list of what are called
// "initializers."  After the constructor's signature (but before its body)
// can be a colon, followed by any initializers you want to specify.
// Initializers are calls to the constructors of the member variables; here,
// we're calling a string constructor that takes another string argument and
// says "Make this string be a copy of that string."  Like other kinds of
// initialization, each initializer uses the same "initializer list" syntax
// we've seen before (with constructor parameters placed within curly
// braces).
//
// Once that's done, there's no more work to be done, so the body of the
// constructor is empty.  This certainly won't always be the case; it's
// quite common to need both initializers and a body.  But you'll find that
// a lot of constructors you write, especially simpler ones, will use
// initializers and otherwise have an empty body.
Song::Song(const std::string& initialArtist, const std::string& initialTitle)
    : artist{initialArtist}, title{initialTitle}
{
}


// Note that you could also write the constructor this way:
//
// Song::Song(std::string initialArtist, std::string initialTitle)
// {
//     artist = initialArtist;
//     title = initialTitle;
// }
//
// The reason you wouldn't is performance-related.  In a naive compilation
// of this constructor, the following things would happen:
//
// (1) The arguments initialArtist and initialTitle would be copied on
//     the way into this constructor, even though the constructor is
//     simply going to copy them again and store those copies in the
//     member variables of the Song being constructed.
// (2) The Song object's memory is allocated.
// (3) string's default constructor would be called on artist, giving it
//     the value "" (empty string).
// (4) string's default constructor would be called on title, giving it
//     the value "" (empty string).
// (5) artist would be re-assigned the value from the initialArtist argument.
// (6) title would be re-assigned the value from the initialTitle argument.
//
// There's no reason to have C++ first construct the strings as empty, then
// re-assign them, when you could just have the objects constructed with the
// appropriate values right from the get-go.  So you should prefer to use
// initializers to initialize member variables whenever possible.  And our
// use of const references avoids two more string copies.
//
// It's certainly possible that a "sufficiently smart compiler" would
// eliminate some or even all of this overhead.  But I'd make the argument
// that the version that uses initializers even reads better, because it
// makes clear that the only thing the constructor does is initialization
// of its member variables.



// The "const" specifier at the end of this function's signature must appear
// on both the declaration and the definition, so I've put it in both places.
// The reason is because C++ allows you to overload member functions based
// only on their "constness", so a member function with "const" in its
// signature is considered different from a member function without it, even
// if their signatures are otherwise identical.  (That sounds crazy at first,
// but we'll actually use that kind of overloading in a later example this
// quarter.)
//
// The explicit effect it has on the member function's definition is that
// the two string member variables, artist and title, will be considered to
// be const strings within the function's body.  Any attempt to change them
// will result in a compile-time error.  As usual, when you promise not to
// change something, the compiler won't let you do it; in this case, what
// you're promising not to change is the Song object that the member function
// was called on, a promise that automatically extends to all of its member
// variables.
std::string Song::getArtist() const
{
    return artist;
}


std::string Song::getTitle() const
{
    return title;
}


void Song::setArtist(const std::string& newArtist)
{
    artist = newArtist;
}


void Song::setTitle(const std::string& newTitle)
{
    title = newTitle;
}

