// math.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// This header file contains declarations for a set of functions called
// the "math functions."  In our case, there are only two functions in
// the set: square and cube.  Note that we're reusing the declaration
// of the square function from square.h here, so that if its signature
// changes, this "math.hpp" header will also be affected.  Note, also,
// the use of the #ifndef/#define/#endif idiom.  (See the comments in
// "square.hpp" for more details about how it works.)

#ifndef MATH_HPP
#define MATH_HPP

#include "square.hpp"


int cube(int n);


#endif // MATH_HPP

