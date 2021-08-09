// main.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// A little program that calls functions, defined elsewhere, called square()
// and cube().  The important thing here is that we're able to include
// "math.hpp" (which itself includes "square.hpp") and also include
// "square.hpp" a second time without any problems.  This is due to the
// #ifndef/#define/#endif idiom used in both header files, which is a way
// to prevent the same header file's text from being included in any given
// source file more than once.


// This is how you include the declarations from the built-in I/O library,
// which we'll use to write console output from our program.  As a general
// rule, when we include header files from the C++ Standard Library, we'll
// surround their names with angle-brackets; when we include our own header
// files, we'll surround their names with double-quotes.
#include <iostream>

// Meanwhile, this is how you include header files from your own project,
// by surrounding their names with double-quotes instead.
#include "math.hpp"
#include "square.hpp"



int main()
{
    // These calls are allowed, even though the code for square and cube
    // does not appear in this source file (even after including "math.hpp"
    // and "square.hpp").  The linker will resolve these calls to the
    // functions defined in the other source files, thereby allowing the
    // program to run.

    int i = square(3);
    int j = cube(4);
    int k = i * j;

    std::cout << "The square of 3 is " << i << std::endl;
    std::cout << "The cube of 4 is " << j << std::endl;
    std::cout << "The square of 3 times the cube of 4 is " << k << std::endl;

    return 0;
}



// Note that, technically, it wouldn't be an error to include the text of
// "square.hpp", as we've written it here, twice.  Function declarations can
// appear more than once in the same source file.  However, if other kinds of
// things, such as classes, were declared in "square.hpp" instead, it would be a
// big no-no, since there are some kinds of things that cannot be declared
// twice in the same source file.  Best to use caution and always use the
// #ifndef/#define/#endif idiom in your header files, because it's never a
// bad thing -- and often a good thing -- to ensure that the text of the
// same header file is not included in the same source file twice.
//
// Of course, a reasonable question to ask at this point is "Why are you
// including square.hpp right after including math.hpp, even though you know
// that math.hpp includes square.hpp?"  The answer is to prove a point, which
// is that this kind of thing can happen.  When the dependencies between
// header files are few, they're easy to remember.  But no one has all of
// those dependencies memorized, new dependencies are added over time, and
// it is basically impossible, as a practical matter, to avoid possibly
// including the same header file twice.  So the wise move is to prevent
// the text of the header file from being included twice, by using the
// #ifndef/define/endif idiom in every header file.

