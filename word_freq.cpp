#include "word_freq.h"

using namespace std;

word_freq::word_freq () {}

word_freq::word_freq (Song *song, int freq) {
  this->song = song;
  this->freq = freq;
}

bool word_freq::operator < (const word_freq &other) const {
  return this->freq > other.freq;
}

bool word_freq::operator == (Song *other) const {
  if (!other) {
    return false;
  }

  return song == other;
}

bool word_freq::operator != (Song *other) const {
  if (!other) {
    return false;
  }

  return song != other;
  // dereference might be very slow according to perf:
  // return !(*this == other);
}

word_vec_pair::word_vec_pair (string word, Song *song) {
  songs.push_back(word_freq(song, 1));
  this->word = word;
}

void word_vec_pair::addWord (Song *song) {
  // this uses the overloaded operator(s)
  vector<word_freq>::iterator i = find(songs.begin(), songs.end(), song);

  // found
  if (i != songs.end()) {
    i->freq++;
    // sort(songs.rbegin(), songs.rend()); // sort backwards (i.e. descending)
    sort(songs.begin(), songs.end());

    // shrink back to avoid memory bloat
    // is wrong if compared to 11 or 10 instead
    // ???
    if (songs.size() > 12) {
      songs.resize(12);
    }
  }
  // not found - add to back
  else {
    songs.push_back(word_freq(song, 1));
  }
}

void word_vec_pair::print (bool context) {
  for (vector<word_freq>::iterator i = songs.begin(); i != songs.end(); i++) {
    if (i - songs.begin() == 10) {
      break;
    }

    if (context) {
      cout << i->song->getContext(word);
    }
    else {
      cout << "Title: " << i->song->getTitle() << endl;
      cout << "Artist: " << i->song->getArtist() << endl;
      cout << endl;
    }
  }
}
