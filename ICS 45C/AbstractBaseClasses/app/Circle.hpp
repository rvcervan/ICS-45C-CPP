// Circle.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// Declares a Circle class that inherits from Shape.

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"


// The member functions here are short and simple, so I'll define them right
// in the class declaration, to provide the compiler with the ammunition
// to optimize more easily.  It's technically legal to define member functions
// in class declarations without having to worry about the typical problem
// of functions that are defined in multiple source files.  We'll continue
// defining member functions in source files when they aren't short and
// simple (i.e., when they'll take a lot longer than the mechanics of
// calling them will take).

class Circle : public Shape
{
public:
    // Since I think this statement (along with many others like it) doesn't
    // make sense and, hence, shouldn't be legal:
    //
    //     Circle c = 3.0;
    //
    // ...I'm making the Circle constructor "explicit".  This is necessary
    // because constructors that take one parameter (or those that can be
    // called with one parameter, because of default arguments) are
    // automatically used for implicit type conversions.  That automatic
    // behavior can be turned off by marking the constructor "explicit".
    // So, in effect, we're saying "This constructor can only be called
    // explicitly."  In the absence of the explicit keyword, doubles will
    // be automatically converted to Circles whenever the compiler feels
    // that it's appropriate, such as in the initialization above, parameter
    // passing (where you could pass a double to a function expecting a
    // Circle!), and so on.
    //
    // It's good for us to start thinking about this issue now.  Forgetting
    // "explicit" when it's sensible allows the compiler to make some very
    // liberal type conversions, without warning you about them.  This can
    // lead to some very subtle bugs, shield you from compile-time errors
    // that should result from a variety of code mistakes, and give behavior
    // that differs radically from what you would expect by looking at the
    // code.
    //
    // You only need to worry about "explicitness" of constructors when they
    // can be called with one parameter.  If they can't, then "explicit" is
    // meaningless.  (Note that constructors that take multiple parameters,
    // but have default arguments such that it's possible to call them with
    // only one parameter; you'd want to consider whether "explicit" is
    // sensible for these, too.)
    explicit Circle(double radius)
        : radius{radius}
    {
    }


    virtual double area() const override
    {
        return radius * radius * 3.1415927;
    }

private:
    double radius;
};



#endif // CIRCLE_HPP

