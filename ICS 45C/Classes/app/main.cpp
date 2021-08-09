// main.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// Be sure you read through Song.hpp and Song.cpp before you read through
// this.  This part of the example demonstrates how to use a class, but
// it makes a lot more sense if you know about the class already.

#include <iostream>
#include "Song.hpp"



void allocatingSongsStatically()
{
    std::cout << "allocatingSongsStatically" << std::endl;

    // This is how you declare a Song object statically.  Because its only
    // constructor requires two string parameters, it is *necessary* to
    // pass two strings to that constructor.
    //
    // Note that the word "new" is not being used here; that's because my 
    // goal is to allocate the object statically; "new" allocates objects
    // dynamically on the heap.  The advantage of static allocation is the
    // same here as it's been in other places: When you statically allocate
    // an object in a function, it will be destroyed automatically when the
    // function ends, removing the possibility of forgetting to destroy it
    // (which is a lot easier than you might think).
    //
    // Note, also, the use of the "initializer list" syntax that we saw
    // when we learned about structs; that same notation is the typical way
    // to initialize objects of classes, too, with the arguments you list
    // being passed to the class' constructor.  (There are some wrinkles
    // in this use of syntax, which we'll see later.)
    Song mySong{"U2", "Moment of Surrender"};

    // Given a Song object, the '.' operator is used to call member functions,
    // the same way we used '.' to access the members of a struct.  When you
    // say "x.y", you're saying that "x" is an object with a member "y" and
    // that you want to access that "y" member.  If it's a member function, you
    // can call it; if it's a member variable (and you have access to it, i.e.,
    // it's not private), you can read from it or write to it.
    std::cout << mySong.getArtist() << " - " << mySong.getTitle() << std::endl;
}



void allocatingSongsDynamically()
{
    std::cout << "allocatingSongsDynamically" << std::endl;

    // This is how you allocate a Song object dynamically.  It's the same as
    // allocating anything else dynamically, except that we need to include
    // constructor parameters.
    Song* mySong = new Song{"Muse", "Big Freeze"};

    // As with a struct, when you have a pointer to an object of a class type,
    // you can use the '->' operator can be used to follow that pointer *and*
    // access one of its members.  The ugly alternative, (*mySong).getArtist(),
    // is not something you'll typically see written.
    std::cout << mySong->getArtist() << " - " << mySong->getTitle() << std::endl;

    // Don't forget to delete the object when you're done with it!  It won't
    // always be the case that we delete objects in the same function in which
    // we create them dynamically -- in fact, it's much more often done
    // differently, because an object like this (whose lifetime matches the
    // lifetime of the function it's created in) would better be placed on
    // the stack, unless it's very large.
    delete mySong;
}


void usingConstSongs()
{
    std::cout << "usingConstSongs" << std::endl;
    
    // Like any other kind of object, Songs can be const, which means we
    // promise not to change them.  The class declaration includes an
    // indication of which things can and can't be done to const Songs.
    const Song mySong{"R.E.M.", "Electrolite"};

    // This is legal, because getArtist() and getTitle() are const.
    std::cout << mySong.getArtist() << " - " << mySong.getTitle() << std::endl;

    // This would be illegal, since setArtist() is not const.  I've left
    // this line commented out, so the program will compile, but try
    // uncommenting this line and compiling the program again.
    // mySong.setArtist("Alex Thornton");
}


// This function prints out the artist and title of a song.  It takes a
// reference to a constant Song, because it doesn't need to change it
// (and so it won't have to be copied, which would require its two member
// variables to be copied).
void printSongDetails(const Song& song)
{
    std::cout << song.getArtist() << " - " << song.getTitle() << std::endl;
}


void pointersAndReferencesAndParameters()
{
    std::cout << "pointersAndReferencesAndParameters" << std::endl;

    // We can statically or dynamically allocate a Song, yet still pass it
    // to printSongDetails().  In either case, we have to pass a Song object
    // (to which the parameter, a reference, will need to refer).  In the
    // case of song1, we simply pass song1.  On the other hand, song2 is a
    // pointer, so we'd need to pass the object it points to.
    Song song1{"Green Day", "21 Guns"};
    Song* song2 = new Song{"Paul Simon", "Diamonds on the Soles of Her Shoes"};

    printSongDetails(song1);
    printSongDetails(*song2);

    delete song2;
}


int main()
{
    allocatingSongsStatically();
    allocatingSongsDynamically();
    usingConstSongs();
    pointersAndReferencesAndParameters();

    return 0;
}

