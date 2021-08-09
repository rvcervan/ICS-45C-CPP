// Song.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// Implementation of our Song class, including the new feature that requires
// that artists and titles cannot be longer than a specified maximum.
// Whenever any attempt is made to set a song's artist or title to be longer
// than the maximum, we truncate it to the maximum length.

#include "Song.hpp"


// As we've seen before, the "unnamed namespace" is how we write functions
// in source files that are "private" to a source file (i.e., their names
// are not exposed to the linker and, thus, the functions cannot be called
// from other source files).  This is a great way to write helper functions
// without making our classes more complicated -- we don't add member
// functions to the header file, we don't declare new functions globally,
// and so on.

namespace
{
    // truncate() takes a string and a length and returns either the
    // original string (if it's not already longer than the given
    // length) or the first n characters of the string (if the
    // given length is n).
    std::string truncate(const std::string& s, unsigned int length)
    {
        if (s.size() > length)
        {
            return s.substr(0, length);
        }
        else
        {
            return s;
        }
    }


    // truncateArtist() truncates a string so that it's no longer
    // than the maximum length of an artist.
    std::string truncateArtist(const std::string& artist)
    {
        return truncate(artist, Song::MAX_ARTIST_LENGTH);
    }


    // truncateTitle() truncates a string so that it's no longer
    // than the maximum length of a title.
    std::string truncateTitle(const std::string& title)
    {
        return truncate(title, Song::MAX_TITLE_LENGTH);
    }
}


// In the constructor, we now use truncateArtist() and truncateTitle()
// to ensure that our artist and title aren't too long.
Song::Song(const std::string& artist, const std::string& title)
    : artist{truncateArtist(artist)}, title{truncateTitle(title)}
{
}


const std::string& Song::getArtist() const
{
    return artist;
}


const std::string& Song::getTitle() const
{
    return title;
}


// We also use truncateArtist() and truncateTitle() here for the same reason.
void Song::setArtist(const std::string& artist)
{
    this->artist = truncateArtist(artist);
}


void Song::setTitle(const std::string& title)
{
    this->title = truncateTitle(title);
}

