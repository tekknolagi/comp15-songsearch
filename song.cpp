#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>

#include "hash_table.h"
#include "song.h"

// i did not feel like writing this->blah lots of times
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

// go through the space-separated lyrics, adding words to
// the lyrics vector
void Song::setLyrics (string lyrics) {
  string buf;
  stringstream ss(lyrics);

  while (ss >> buf) {
    addWord(buf);
  }
}

void Song::addWord (string word) {
  lyrics.push_back(word);
}

// TODO: fix
// ^ is it even broken?
string Song::getContext (string word) {
  stringstream ss;

  // go through all the words in the song
  for (vector<string>::iterator i = lyrics.begin();
       i != lyrics.end();
       i++) {
    // if the current word is the word we're looking for
    if (alpha_only(*i) == word) {
      // go 5 (or to the beginning) back
      // and go 5 (or to the end) forward
      vector<string>::iterator
      first = i - 5,
      last = i + 6; // .end() is past the back of the array
      first = (first < lyrics.begin()) ? lyrics.begin() : first;
      last  = (last > lyrics.end()) ? lyrics.end() : last;

      // <joke> and do the harlem print </joke>
      // as much as i despise XML, i got docked points
      // last time for humorous commentary
      ss << "Title: " << title << endl;
      ss << "Artist: " << artist << endl;
      ss << "Context: ";

      // go through each of the words in the range of first->last
      // and append to the stringstream
      copy(first, last, ostream_iterator<string>(ss, " "));

      // and add a newline to it
      ss << endl << endl;
    }
  }

  return ss.str();
}
