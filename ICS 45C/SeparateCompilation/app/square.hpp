// square.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// Based on the principles discussed on this example's web lesson (in short,
// header files contain declarations but not definitions), this header file
// contains the declaration of the one and only function "exported" (made
// available) by the square.cpp source file: the "square" function.


// This technique is used to ensure that the same header file is not included
// more than once in the same source file.  Words that begin with the "#"
// character are meant for the preprocessor, which reads each source file
// before the compiler does.  The preprocessor does some simple things --
// makes macro replacements, eliminates code under certain conditions (so,
// say, you can have a file that contains certain code that is compiled only
// when the target is Windows and other code that is compiled only when the
// target is Linux).  Its commands are called "preprocessor directives"; those
// are the things that start with a "#" character.
//
// In this case, we have some cryptic-looking syntax, but here's how it
// reads in English:
//
//   "If you haven't seen SQUARE_HPP before, make a note of the fact that
//    you've seen SQUARE_HPP, so that if you see it again, you'll notice.
//    Then, go ahead and include all of the stuff in this file, up to
//    the end."
//
// Note the #endif at the end of the file; it is the end of the block that
// begins with #ifndef.
//
// The effect of this is that the contents of this file will only ever be
// included once within a source file; a subsequent attempt to include it
// will cause everything to be ignored, since SQUARE_HPP will have been seen
// once already.
//
// The name SQUARE_HPP is chosen somewhat arbitrarily, but the goal is to make
// sure that it's globally unique.  One way to make this likely is to match
// the name of the macro to the name of the header file, the way we've done
// here.

#ifndef SQUARE_HPP
#define SQUARE_HPP



// square() takes an int parameter and returns the square of its argument.
int square(int n);



#endif // SQUARE_HPP

