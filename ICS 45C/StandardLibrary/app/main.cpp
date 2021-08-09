// main.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// This code example takes you through a few uses of the "std::vector"
// container, including how it interfaces with iterators and generic
// algorithms.  The example is organized as a set of separate, unrelated
// functions, each demonstrating some aspect of this portion of the standard
// library.  The main() function is set up to call each of these functions,
// though I've commented all of the calls out; if you'd like to see the
// output of one of the functions in particular, uncomment the call to that
// function, then recompile and run the program.
//
// Be sure to read through the page on the course web site that discusses
// the background information for this code example before reading through
// this; it discusses the underlying concepts at work here, which I'll assume
// you're already familiar with in the comments here.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>


void accessingAndManipulatingVectorElements()
{
    // "std::vector" is a class template in C++, which means that it's necessary
    // to give it "type parameters".  There is no such thing, technically, as
    // a vector; there is only a std::vector<int>, a std::vector<string>, and
    // so on.
    std::vector<int> v;

    for (int i = 0; i < 10; i++)
    {
        // The push_back() function adds an element to the end of a vector.
        // push_back seems like a peculiar name, but it makes more sense when
        // you consider that you can remove the last element with a function
        // called pop_back (and that there are other containers with push_front
        // and pop_front functions, though vector lacks them, because they
        // would be inefficient).  You may recognize the terms "push" and "pop"
        // if you've previously learned about a classic data structure called
        // a stack.
        v.push_back(i);
    }


    // Another way to create the same vector -- since we've got a statically-
    // determined set of values to add to it (i.e., we know at compile time
    // exactly how many values to add and exactly what they are) -- is to use
    // the "initializer" syntax to initialize the vector instead.
    //
    // std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //
    // The "initializer" syntax uses curly braces instead of parentheses as a
    // means of listing what otherwise appear to be constructor parameters.
    // Some types, like std::vector<int>, support this syntax as a way of
    // passing an arbitrary number of values into the constructor and using
    // them to initialize what's stored inside of the object.
    //
    // (There's more to say about this initialization syntax, but we'll leave
    // the rest of it for another time.)


    // One way to access elements in a vector is to use the [] notation, which
    // is similar to how you access array elements in C++.  The feature of C++
    // that makes this possible is operator overloading, which we'll see in a
    // couple of weeks.  In this case, the [] operator has been overloaded to
    // work on vectors by returning a reference to the element at a particular
    // index.
    //
    // One thing to note about the [] operator on a vector is that it does not
    // perform range checking, which means you can use it to access non-existent
    // cells, which will provide you with direct access to memory that quite
    // likely does not belong to the vector at all.  A separate function called
    // at() can be called on the vector instead, if you want range-checked
    // access to a cell.  at() can be used on either side of an assignment
    // statement, as demonstrated below, because it returns a reference to the
    // appropriate cell.  When at() accesses a cell out of bounds, it responds
    // by "throwing an exception", a mechanism we'll see in some detail toward
    // the end of the quarter.
    //
    // Like the elements of arrays, vector elements are indexed consecutively,
    // beginning at zero.  If there are n elements stored in the vecotr, their
    // indices will range from 0 through n - 1.  The size() function is a way
    // to ask a vector how many elements it stores.  The function returns an 
    // unsigned integer value.  So we'll want to use unsigned int in our
    // loop, to avoid the potential of "i < v.size()" generating a
    // "signed/unsigned mismatch" warning.

    for (unsigned int i = 0; i < v.size(); i++)
    {
        v[i] = v[i] * 2;
        v.at(i) = v.at(i) + 1;

        std::cout << v[i] << std::endl;
        std::cout << v.at(i) << std::endl;
    }
}



void declaringVectorsWithElementsAlreadyInThem()
{
    // Normally, when you declare a vector like this, it holds no elements.
    std::vector<int> vectorThatIsEmpty;

    // You can also pass a parameter to the construtor, which immediately
    // sets the size of the vector to something other than zero.  The
    // elements are initialized using the appropriate default constructor
    // (which, in the case of ints, initializes them to zero).  So this
    // creates a vector of 10 ints, all with the value 0.
    std::vector<int> v1(10);

    // Don't believe me? :)
    std::cout << "Contents of v1: ";

    for (unsigned int i = 0; i < v1.size(); i++)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << std::endl;

    // You can pass a second parameter to the vector constructor, as well,
    // which sets an initial value for each element.  So, for example, suppose
    // you want a vector of 15 ints, each of which has a value -1.
    std::vector<int> v2(15, -1);

    std::cout << "Contents of v2: ";

    for (unsigned int i = 0; i < v2.size(); i++)
    {
        std::cout << v2[i] << " ";
    }
    std::cout << std::endl;
}



void usingIteratorsOnAVector()
{
    std::vector<std::string> v;
    v.push_back("alex");
    v.push_back("is");
    v.push_back("happy");
    v.push_back("today");

    // Another way to iterate across a vector -- or any of the other containers
    // in the standard library -- is to use an iterator.  Iterators abstract
    // away the details of how elements are organized in a data structure,
    // providing instead of a uniform interface that allows you to iterate
    // different data structures with the same code.  This is the key to
    // implementing generic algorithms, like the ones that are written in the
    // standard library.
    //
    // An iterator has a "position", which indciates where in the data structure
    // the iterator refers to.  If there are n elements in a container, there
    // are n + 1 possible iterator positions: one for each element, and an
    // extra one called "end" that indicates a position just beyond the last
    // element.  The position called "begin" indicates the first element.  To
    // get an iterator into a container, we can call functions begin() and
    // end() on it, which return iterators in the "begin" and "end" positions,
    // respectively.
    //
    // Iterators behave somewhat like pointers.  We can use the * (dereference)
    // operator to access or modify the element referred to by an iterator.  We
    // can use ++ to move it forward, -- to move it backward, += or -= to move
    // it forward or backward in more than just single steps, and so on, though
    // not all containers provide iterators that support all of these
    // operations.
    //
    // Here is an example of a loop that iterates through the vector v and does
    // two things:
    //   (1) Update the element so that it has "!!!" concatenated to it
    //   (2) Print the newly-updated element, followed by its length


    // std::vector<string>::iterator is an iterator that knows how to iterate
    // through a vector of strings.
    for (std::vector<std::string>::iterator i = v.begin(); i != v.end(); i++)
    {
        // Note that, since our iterator is called i, *i is the syntax for
        // accessing/changing the value referred to by the iterator.  Note,
        // also, the use of the -> operator to call the length() function on
        // each element, the same way you would use -> with a pointer.

        *i += "!!!";
        std::cout << "'" << *i << "' (length = " << i->length() << ")" << std::endl;
    }


    // Types like "vector<string>::iterator" are quite a mouthful, and the
    // problem becomes more acute when you have more complex types, such as
    // "map<string, vector<unsigned int>>::const_iterator".  In C++11, the
    // "auto" keyword has been adapted to do what's called "type inference",
    // which asks the compiler to deduce (if possible) what the appropriate
    // type is without you having to write it.  Variables of "auto" types
    // still have a statically-determined type, just like variables whose
    // types you explicitly specify; the only difference is that you're asking
    // the compiler to use its knowledge of the program's declarations to
    // figure out the type for you, rather than you having to say it.  Given
    // that the compiler has still chosen a type for the variable, all the
    // same restrictions are in place once you have it -- you'll still have
    // to treat the variable like a variable of the chosen type.
    //
    // I don't find myself using "auto" very often, but for some patterns --
    // especially for something like the loop below, where there is enough
    // context for someone to be able to read and understand the code, including
    // knowing what its types are, without having to go searching through header
    // files to see how functions are declared.  So many containers have begin()
    // and end() functions that return iterators, there's no mystery here.
    //
    // Note, though, that whether you prefer "auto" or not, you should also
    // realize that you can't use it everywhere.  You can only use it in a
    // circumstance in which the compiler can deduce the correct type (e.g.,
    // when you're declaring a variable and immediately assigning it a value)
    // based on context.

    for (auto i = v.begin(); i != v.end(); i++)
    {
        *i = "!!!";
        std::cout << "'" << *i << "' (length = " << i->length() << ")" << std::endl;
    }
}



// The keyword "const" has an effect on iterators.  Suppose we have a "const"
// vector, as in the parameter to printAll() below.  That means we've agreed
// not to do anything that might possibly change that vector.  This affects
// our ability to ask the vector for an iterator, since iterators possess the
// ability to not only access elements, but also to change them.
//
// The solution is to understand that when you ask a const container for an
// iterator, you get a special kind of iterator called a "const_iterator",
// which allows access to the individual elements in the container, but does
// not permit their modification.

void printAll(const std::vector<int>& v)
{
    // This would be an error if we tried to do it:
    //
    // for (std::vector<int>::iterator i = v.begin(); i != v.end(); i++)
    //
    // because begin(), when called on a const vector, returns a const_iterator
    // instead.

    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); i++)
    {
        std::cout << *i << std::endl;

        // This would be an error, since i is a const_iterator:
        //
        // *i = 3;
    }

    // Note, too, that "auto" will do the right thing here; it'll deduce that
    // the correct type of the iterator is std::vector<int>::const_iterator,
    // since the vector itself is marked "const".  In other words, if we've
    // promised not to change the vector, asking the vector for an iterator
    // will give us an iterator that provides that same promise.
}


void howConstAffectsIterators()
{
    std::vector<int> v;
    
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    printAll(v);
}



// The true power afforded by iterators is not to simplify a typical iteration
// loop like the ones we've been writing.  The power is that they help you to
// avoid many of the typical loops you'd have to write, so you never have to
// write them in the first place.
//
// As an example, there are many times where you wrtie a loop that boils down
// to "Do something to every element in a container."  This functionality is
// encapsulated in a generic algorithm called "for_each".  You tell the
// algorithm where to start (inclusive), where to end (exclusive), and what
// function to call on each element in that range of elements.  It does the
// rest.  The starting and ending positions are communicated as iterators.

void printInt(int i)
{
    std::cout << i << std::endl;
}

void doubleInt(int& i)
{
    i *= 2;
}


void usingTheGenericForEachAlgorithm()
{
    std::vector<int> v;

    for (int i = 0; i < 20; i++)
    {
        v.push_back(i);
    }

    // Here, we use for_each to print all of the elements.  Since we have
    // a vector<int>, we can pass printInt(), which is a function that
    // takes a parameter of type int.
    std::for_each(v.begin(), v.end(), printInt);

    // Here, we use for_each to change the value of all the elements, by
    // passing a different function, one that takes an int by reference
    // and doubles it.  Again, the function's parameter is compatible
    // with the kinds of elements in the container, so it works.
    std::for_each(v.begin(), v.end(), doubleInt);

    // Now we'll print the updated elements.
    std::for_each(v.begin(), v.end(), printInt);

    // The third parameter to for_each doesn't have to be the name of a
    // function.  It just has to be something that can be treated as a
    // function.  One shorthand available in C++11 is the use of what are
    // called "lambda expressions", which let you build an "anonymous"
    // (i.e., unnamed) function on the fly.
    //
    // Syntactically, lambda expressions are a little confusing.  They
    // begin with brackets -- and it's possible to put things in those
    // brackets, but let's assume for now that they're always meant to
    // be empty -- and are followed by a parameter list and a body.
    //
    // Example:
    //
    //     [](int x) { return x * x; }
    //
    // That defines an anonymous function that takes an int and returns
    // the square of that int.
    //
    // Since lambda expressions evaluate to functions, you can use a
    // lambda expression to specify the function to be passed to for_each.
    std::for_each(v.begin(), v.end(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;
}



// There are a variety of other generic algorithms that can provide
// functionality that you might otherwise have to write yourself.  They
// tend to use iterators as a way of knowing what range of elements to
// use/change; most take "ranges," which are defined by two iterators (a
// start position and an end position, with start begin inclusive and end
// begin exclusive, so you can use begin() and end()).

void usingOtherGenericAlgorithms()
{
    // First, let's generate a vector containing a bunch of random integers
    // from 100..999.  (The details of random-number generation are beyond
    // the scope of this example, but we'll return to them another time.)

    std::random_device randomDevice;
    std::mt19937 randomEngine(randomDevice());
    std::uniform_int_distribution<int> randomDistribution(100, 999);

    std::vector<int> v;

    for (int i = 0; i < 20; i++)
    {
        v.push_back(randomDistribution(randomEngine));
    }

    // Sorting the elements is as easy as calling the sort algorithm and
    // telling it to sort the vector from beginning to end.
    std::vector<int> vEntirelySorted = v;
    std::sort(vEntirelySorted.begin(), vEntirelySorted.end());
    std::cout << "vEntirelySorted contents:" << std::endl;
    std::for_each(vEntirelySorted.begin(), vEntirelySorted.end(), printInt);

    // Alternatively, we can sort just part of the vector by passing
    // different iterators.  For example, this will sort the first 10
    // elements.  Note the use of "v.begin() + 10," which gives us an
    // iterator 10 positions to the right of the begin position.
    std::vector<int> vPartiallySorted = v;
    std::sort(vPartiallySorted.begin(), vPartiallySorted.begin() + 10);
    std::cout << "vPartiallySorted contents:" << std::endl;
    std::for_each(vPartiallySorted.begin(), vPartiallySorted.end(), printInt);

    // The max_element algorithm can find us the largest element in a
    // range of elements, returning an iterator to that largest element.
    std::vector<int>::iterator max = std::max_element(v.begin(), v.end());
    std::cout << "The max element in v is: " << *max << std::endl;

    // We can scramble the sorted numbers back up randomly by using
    // the shuffle algorithm (and passing it a random number
    // generator).
    std::vector<int> vScrambledBackUp = vEntirelySorted;
    std::shuffle(vScrambledBackUp.begin(), vScrambledBackUp.end(), randomEngine);
    std::cout << "vScrambledBackUp contents:" << std::endl;
    std::for_each(vScrambledBackUp.begin(), vScrambledBackUp.end(), printInt);
}



int main()
{
    // Uncomment calls to individual example functions if you'd like to see
    // their output.

//    accessingAndManipulatingVectorElements();
//    declaringVectorsWithElementsAlreadyInThem();
//    usingIteratorsOnAVector();
//    howConstAffectsIterators();
//    usingTheGenericForEachAlgorithm();
//    usingOtherGenericAlgorithms();

    return 0;
}

