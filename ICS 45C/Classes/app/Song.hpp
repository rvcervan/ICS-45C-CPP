// Song.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// This is the declaration of the Song class, the purpose of which is to
// establish (at least) enough information so that source files can make
// use of objects of the class.  So there are a couple of things that we
// must include in our class declaration:
//
// (1) The member variables, which will specify how much memory is required
//     by a Song object.  In this case, there are two member variables, so
//     the amount of memory required is twice the amount of memory required
//     by each std::string object (which is, in turn, determined by the
//     declaration of the std::string class), plus padding (if any)
//     that the compiler adds between them.
//
// (2) The member functions, which will specify what functions can be called
//     on Song objects.

#ifndef SONG_HPP
#define SONG_HPP

#include <string>



// A couple of things to notice:
//
// (1) Groups of members are made public or private by preceding them with
//     either "public:" or "private:".  Saying "public:" in a class declaration
//     means "Henceforth and until I say otherwise, every member declared below
//     this is public."  Though, technicaly, the default is private, I like to
//     include this regardless, to make as clear as possible the meaning of
//     what I wrote.  (And I generally tend to like to lead off with what's
//     public, anyway, since that's most relevant to a human reader of the
//     code.)
// (2) Class declarations, like struct declarations, are required to end with a
//     semicolon following their closing curly brace.

class Song
{
public:
    // The constructor takes two parameters.  It'll simply assign these two
    // parameters into the member variables artist and title, respectively.
    // Declaring this constructor has a couple of consequences:
    //
    // (1) If you want to create a Song object, you'll have to specify an
    //     artist and a title for it by passing parameters to this constructor.
    // (2) There will be no default constructor (i.e., one that takes no
    //     parameters and default-constructs the member variables).  You get
    //     one of those if you don't declare any constructors; as soon as you
    //     declare a constructor, you don't get the default one anymore.  In
    //     our case, that's fine: We don't want to have Songs that don't have
    //     artists and titles.
    //
    // Notice, too, that this constructor, along with a couple of the member
    // functions, take strings by const reference; this is because it saves
    // having to make a copy of the string on the way into the function, but
    // still allows the function to guarantee the caller that the string will
    // not be modified within the function.
    Song(const std::string& initialArtist, const std::string& initialTitle);

    // getArtist() returns this song's artist.  The "const" on the end of its
    // signature is how we specify that it's safe to call getArtist() on a
    // const Song:
    //
    //     const Song s{"U2", "Please"};
    //     cout << s.getArtist() << endl;   // This will be okay
    //     s.setArtist("R.E.M.");           // This will not
    std::string getArtist() const;

    // getTitle() returns this song's title.
    std::string getTitle() const;

    // setArtist() changes this song's artist.  The function is not marked
    // "const" because it changes the state of the Song, so it should not
    // be legal to call it on a const Song.
    void setArtist(const std::string& newArtist);

    // setTitle() changes this song's title.
    void setTitle(const std::string& newTitle);

private:
    std::string artist;
    std::string title;
};



// It may seem a little strange that we included both the public and private
// parts in the header, even though it is intended to be the interface and
// not the implementation -- as we don't tend to think of private details as
// part of the "interface" of a class -- but it's important to remember that
// there are two audiences for header files:
//
// (1) The people who will be reading it, so they can understand how to make
//     use of whatever is declared within it
// (2) The compiler that will be compiling a source file that includes this
//     header
//
// In the latter case, allocating a Song object requires the compiler to know
// the size of a Song object, which requires it to know how many and what
// kinds of member variables Songs have.  Any source file that allocates a
// Song object (statically or dynamically) will need to know these deetails.
// So the private member variables turn out to be very important to include
// in a class declaration, even though they seem out of place from a human
// perspective.



#endif // SONG_HPP

