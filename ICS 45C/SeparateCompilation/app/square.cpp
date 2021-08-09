// square.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// Again, based on the technique discussed on the web page accompanying
// this code example, this is the definition of the square function.
// It's simple; it just multiplies its argument by itself and returns
// the result.
//
// The compiler will compile this source file in the absence of the others,
// generating an object file "square.cpp.o" as a result.  "square.cpp.o" will
// contain the compiled version of the square function, and nothing else.


// It's generally good practice to include the header file that corresponds
// to each source file, though, technically, it's not necessary in this
// case.  It will be very important when we start implementing classes in a
// week or so, though.

#include "square.hpp"



int square(int n)
{
    return n * n;
}

