#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>

#include "hashtable.h"
#include "song.h"

#define initSong(a, t) {this->artist = (a); this->title = (t);}

extern string alpha_only (string);

Song::Song () {
        initSong("uninitialized", "uninitialized");
}

Song::Song (string artist, string title) {
        initSong(artist, title);
}

Song::Song (string artist, string title, string lyrics) {
        initSong(artist, title);
        setLyrics(lyrics);
}

void Song::setLyrics (string lyrics) {
        string buf;
        stringstream ss(lyrics);
        while (ss >> buf)
                this->lyrics.push_back(buf);
}

void Song::addWord (string word) {
        lyrics.push_back(word);
}

// TODO: fix
string Song::getContext (string word) {
        stringstream ss;

        for (vector<string>::iterator i = lyrics.begin();
             i != lyrics.end();
             i++) {
                if (alpha_only(*i) == word) {
                        vector<string>::iterator
                                first = i - 5,
                                last = i + 6;
                        first = (first < lyrics.begin()) ? lyrics.begin() : first;
                        last  = (last > lyrics.end()) ? lyrics.end() : last;

                        ss << "Title: " << title << endl;
                        ss << "Artist: " << artist << endl;
                        ss << "Context: ";
                        copy(first, last, ostream_iterator<string>(ss, " "));
                        ss << endl << endl;
                }
        }

        return ss.str();
}
