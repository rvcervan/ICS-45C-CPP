// Rectangle.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// Declares a Rectangle class that inherits from Shape.  Everything interesting
// here is explained in the comments in Circle.hpp.

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"



class Rectangle : public Shape
{
public:
    Rectangle(double width, double height)
        : width{width}, height{height}
    {
    }


    virtual double area() const override
    {
        return width * height;
    }


private:
    double width;
    double height;
};



#endif // RECTANGLE_HPP

