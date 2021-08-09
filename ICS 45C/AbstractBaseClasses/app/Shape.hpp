// Shape.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// Declares the Shape class, an abstract base class for kinds of shapes.

#ifndef SHAPE_HPP
#define SHAPE_HPP



class Shape
{
public:
    // Even though there doesn't really need to be a Shape destructor --
    // since Shape only contains a double, which doesn't need any special
    // handling -- I'll declare one here and make it virtual, to establish
    // the fact that Shapes should be destroyed polymorphically.  Once you
    // intend to use inheritance, this is generally a good practice.
    virtual ~Shape() = default;

    // area() returns the area of this shape.  Since it doesn't need to
    // modify the meaning of the shape in any way.
    virtual double area() const = 0;
};


// Interestingly, since everything in this class is either defined (the
// destructor) or doesn't need to be (the area() function, which is pure
// virtual), we won't need a Shape.cpp.



#endif // SHAPE_HPP

