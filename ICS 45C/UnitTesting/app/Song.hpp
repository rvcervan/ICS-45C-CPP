// Song.hpp
//
// ICS 45C Winter 2019
// Code Example
//
// This is a declaration of a Song class much like one from a previous
// code example, with one additional feature: artists and titles have a
// length limit (with the artist limited to 30 characters and the title
// limited to 40 characters).
//
// Note that our goal, when writing a header file, is to declare only
// what is absolutely necessary, so we err on the side of leaving things
// out of the header file (and "hidden" in Song.cpp) whenever possible.
// But we do want to include details that are relevant.  So the only thing
// we've added here are constants that specify the maximum length of an
// artist and a title.  The functions that do the work of truncating
// strings are all written only in Song.cpp.  (Note that we could also
// have made these into private member functions -- and sometimes you
// need to, because they need access to the private member variables of
// your class -- but, in this case, it wasn't necessary.)

#ifndef SONG_HPP
#define SONG_HPP

#include <string>



class Song
{
public:
    // There are two new keywords here:
    //
    // * "static", which, when used in a class, specifies something that
    //   is a member of the class as a whole, as opposed to being a member
    //   of each object of the class.  Every Song has the same limit on
    //   artist and title, so it makes sense for these constants to belong
    //   to the class as a whole, as opposed to individual Song objects.
    //   So we make them static.
    //
    // * "constexpr", which is similar to "const", but specifies that you
    //   can write arbitrary expressions (and even functions that calculate
    //   them!) that are evaluated at compile time.  Naturally, there are a
    //   lot of things you can't do in a "constexpr" (e.g., you can't read
    //   user input), because it's the compiler that will be calculating the
    //   answer.  The resulting value can then be used by the compiler
    //   anywhere that the constexpr's name appears.
    static constexpr unsigned int MAX_ARTIST_LENGTH = 30;
    static constexpr unsigned int MAX_TITLE_LENGTH = 40;

public:
    Song(const std::string& artist, const std::string& title);

    // Unlike in the previous code example, we have these two functions
    // return (by const reference) the actual artist and title, as opposed
    // to making copies of them.  Callers who want, for example, to just
    // print them out can then do so without them having to be copied
    // first; callers who need to store them or do other manipulations
    // can choose to copy them first.  This way, callers only pay for the
    // copy if they need it.
    const std::string& getArtist() const;
    const std::string& getTitle() const;

    void setArtist(const std::string& artist);
    void setTitle(const std::string& title);

private:
    std::string artist;
    std::string title;
};



#endif // SONG_HPP

