// main.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// Having some fun with shapes

#include <iostream>
#include <vector>
#include <algorithm>
#include "Shape.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"



// Since printArea() can do its job without making any changes to the Shape
// that it's given, I've declared the function to take a const Shape* as a
// parameter.  This allows me to use the function with for_each on a const
// vector or a non-const vector.
void printArea(const Shape* s)
{
    std::cout << s->area() << std::endl;
}


int main()
{
    // You have to be a bit careful with vectors of pointers, because
    // they raise an interesting issue of ownership.  While the pointers
    // will legally be able to point to objects of any of the classes
    // derived from Shape -- and that's a good thing -- there's a
    // danger of forgetting to delete the objects when you're finished
    // with them, which can result in very large, and very difficult to
    // detect (until it's too late) memory leaks.
    //
    // The reason you have to delete the shapes yourself is because vectors
    // only assume responsibility for specifically what you put into them.
    // Since the vector contains Shape pointers, the vector only considers
    // itself to be responsible for the pointers, not the objects the pointers
    // point to.  (This is actually a sensible design decision, not just
    // laziness on the part of the vector.  If the vector deleted the objects,
    // how could you store more than one pointer to the same object in the
    // same vector -- or copies of a pointer in more than one vector --
    // without causing problems?)

    std::vector<Shape*> v;
    v.push_back(new Rectangle{5.0, 7.0});
    v.push_back(new Circle{5.0});
    v.push_back(new Rectangle{4.0, 4.0});

    // Print the area of all the shapes.
    std::for_each(v.begin(), v.end(), printArea);

    // Delete all the objects.  Note that, since the third parameter to
    // for_each must be a function, we had to pass it a function, but
    // a lambda can be used.
    std::for_each(v.begin(), v.end(), [](Shape* s) { delete s; });

    return 0;
}

