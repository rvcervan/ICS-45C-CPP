// SongTests.cpp
//
// ICS 45C Winter 2019
// Code Example
//
// Unit tests for the Song class, including tests of the truncation
// functionality newly added in this version.  This set of unit tests
// is intended to be complete -- it tests everything that the class
// does (which doesn't require that many tests, because the class
// doesn't do that much).  Notice, though, that there's not a single
// unit test for every member function; there's a single unit test
// for every *behavior* (i.e., every sequence of calls to functions
// for which there is a known, meaningful result).  It takes more
// than five tests to test our five member functions.  When you write
// unit tests, you'll want to do likewise.

#include <gtest/gtest.h>
#include "Song.hpp"


// I'm making some decisions purposefully here that seem random.
// For example, when choosing artists and titles to test with in
// these first few tests, I'm intentionally testing with ones that
// are short, so that (a) I don't accidentally choose one that's
// longer than the maximum, and (b) if I ever make the maximum
// smaller, I won't inadvertantly break tests.
//
// (This is illustrative of one of the basic principles of good
// programming: anticipating that things might change and being
// sure you're resilient to that change.  That's good practice
// in any language, not just in C++.  There are many micro-decisions
// that you make while you write code, and it's not as though you'll
// make every one of them correctly, but the more your mind is open
// to the bigger-picture effect of these smaller-picture decisions,
// the better chance you have of getting them right.)

TEST(SongTests, containArtistGivenAtCreation)
{
    Song s{"U2", "Volcano"};
    ASSERT_EQ("U2", s.getArtist());
}


TEST(SongTests, containTitleGivenAtCreation)
{
    Song s{"Arcade Fire", "Afterlife"};
    ASSERT_EQ("Afterlife", s.getTitle());
}


TEST(SongTests, afterChangingArtist_ContainNewArtist)
{
    Song s{"Til Tuesday", "Take On Me"};
    s.setArtist("a-ha");
    ASSERT_EQ("a-ha", s.getArtist());
}


TEST(SongTests, afterChangingTitle_ContainNewTitle)
{
    Song s{"U2", "Breathe"};
    s.setTitle("Gone");
    ASSERT_EQ("Gone", s.getTitle());
}


// Here, I don't want to hard-code test inputs that assume that the
// maximum length of an artist or a title is anything in particular.
// Since these are constants that are declared in my code, those
// constants might change; if they do, I want to be sure that my
// tests don't subsequently break.
//
// So what I'm doing here is intentionally constructing strings that
// are longer than the stated maximum.  The key new technique here is
// the use of a std::string constructor that takes two parameters:
//
// (1) A number of characters
// (2) A character to repeat
//
// which initializes the string to contain the given number of copies
// of the given character.  For example, this constructor call:
//
//    std::string s{5, 'x'};
//
// makes the string s contain the characters "xxxxx".
//
// In my case, though, rather than using a hard-coded default number
// of characters, I calculate a value based on either
// Song::MAX_ARTIST_LENGTH or Song::MAX_TITLE_LENGTH.  Since those
// constants are public, I can use them here.  (And this is one of
// benefits of making those constants public; other code can use
// that knowledge to do the right thing.)
//
// I'm also using a common testing pattern here when testing against
// a limit (in this case, a limit on how many characters an artist
// or a title might be).  I'm testing three situations:
//
// (1) Much larger than the limit
// (2) Barely larger than the limit (i.e., one greater)
// (3) Exactly at the limit
//
// There's a fourth, too, "much smaller than the limit", which I've
// already (implicitly) tested above.

TEST(SongTests, truncateArtistsAtCreationIfTooLong)
{
    std::string longArtist(Song::MAX_ARTIST_LENGTH + 5, 'x');
    std::string truncatedArtist(Song::MAX_ARTIST_LENGTH, 'x');

    Song s{longArtist, "Controller"};
    ASSERT_EQ(truncatedArtist, s.getArtist());
}


TEST(SongTests, truncateArtistsAtCreationIfBarelyTooLong)
{
    std::string longArtist(Song::MAX_ARTIST_LENGTH + 1, 'b');
    std::string truncatedArtist(Song::MAX_ARTIST_LENGTH, 'b');

    Song s{longArtist, "Half-Life"};
    ASSERT_EQ(truncatedArtist, s.getArtist());
}


TEST(SongTests, doNotTruncateArtistsAtCreationIfExactlyMaximumLength)
{
    std::string maxArtist(Song::MAX_ARTIST_LENGTH, 'h');

    Song s{maxArtist, "Something to Say"};
    ASSERT_EQ(maxArtist, s.getArtist());
}


TEST(SongTests, truncateArtistsWhenChangedAfterCreationIfTooLong)
{
    std::string longArtist(Song::MAX_ARTIST_LENGTH + 7, 'q');
    std::string truncatedArtist(Song::MAX_ARTIST_LENGTH, 'q');

    Song s{"Oingo Boingo", "Try to Believe"};
    s.setArtist(longArtist);
    ASSERT_EQ(truncatedArtist, s.getArtist());
}


TEST(SongTests, truncateArtistsWhenChangedAfterCreationIfBarelyTooLong)
{
    std::string longArtist(Song::MAX_ARTIST_LENGTH + 1, 'g');
    std::string truncatedArtist(Song::MAX_ARTIST_LENGTH, 'g');

    Song s{"Muse", "Starlight"};
    s.setArtist(longArtist);
    ASSERT_EQ(truncatedArtist, s.getArtist());
}


TEST(SongTests, doNotTruncateArtistsWhenChangedAfterCreationIfExactlyMaximumLength)
{
    std::string maxArtist(Song::MAX_ARTIST_LENGTH, 'y');

    Song s{"Sting", "Fragile"};
    s.setArtist(maxArtist);
    ASSERT_EQ(maxArtist, s.getArtist());
}


TEST(SongTests, truncateTitlesAtCreationIfTooLong)
{
    std::string longTitle(Song::MAX_TITLE_LENGTH + 3, 'a');
    std::string truncatedTitle(Song::MAX_TITLE_LENGTH, 'a');

    Song s{"Imogen Heap", longTitle};
    ASSERT_EQ(truncatedTitle, s.getTitle());
}


TEST(SongTests, truncateTitlesAtCreationIfBarelyTooLong)
{
    std::string longTitle(Song::MAX_TITLE_LENGTH + 1, 'p');
    std::string truncatedTitle(Song::MAX_TITLE_LENGTH, 'p');

    Song s{"Van Halen", longTitle};
    ASSERT_EQ(truncatedTitle, s.getTitle());
}


TEST(SongTests, doNotTruncateTitlesAtCreationIfExactlyMaximumLength)
{
    std::string maxTitle(Song::MAX_TITLE_LENGTH, 'u');

    Song s{"XTC", maxTitle};
    ASSERT_EQ(maxTitle, s.getTitle());
}


TEST(SongTests, truncateTitlesWhenChangedAfterCreationIfTooLong)
{
    std::string longTitle(Song::MAX_TITLE_LENGTH + 12, 'f');
    std::string truncatedTitle(Song::MAX_TITLE_LENGTH, 'f');

    Song s{"Jackson Browne", "Before the Deluge"};
    s.setTitle(longTitle);
    ASSERT_EQ(truncatedTitle, s.getTitle());
}


TEST(SongTests, truncateTitlesWhenChangedAfterCreationIfBarelyTooLong)
{
    std::string longTitle(Song::MAX_TITLE_LENGTH + 1, 't');
    std::string truncatedTitle(Song::MAX_TITLE_LENGTH, 't');

    Song s{"Led Zeppelin", "Kashmir"};
    s.setTitle(longTitle);
    ASSERT_EQ(truncatedTitle, s.getTitle());
}


TEST(SongTests, doNotTruncateTitlesWhenChangedAfterCreationIfExactlyMaximumLength)
{
    std::string maxTitle(Song::MAX_TITLE_LENGTH, 'm');

    Song s{"Zwan", "Lyric"};
    s.setTitle(maxTitle);
    ASSERT_EQ(maxTitle, s.getTitle());
}

