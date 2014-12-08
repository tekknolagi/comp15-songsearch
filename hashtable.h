#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "hashfunc.h"
#include "song.h"

using namespace std;

typedef struct word_freq_s {
  Song *song;
  int freq;

  // important - resize() will complain if this does not exist
  // needs constructor when adding "empty" elements
  word_freq_s () {}
  word_freq_s (Song *song, int freq) {
    this->song = song;
    this->freq = freq;
  }
  // overrode so i could use std::sort
  bool operator < (const word_freq_s& other) const {
    return this->freq > other.freq;
  }
  // overrode so i could use std::find
  bool operator == (Song *other) {
    if (!other) return false;
    return song == other;
  }
  // this too
  bool operator != (Song *other) {
    if (!other) return false;
    return song != other;
    // dereference might be very slow according to perf:
    // return !(*this == other);
  }
} word_freq_t;

typedef struct word_vec_pair_s {
  vector<word_freq_t> songs;
  string word;

  // initialize a new pair and add the first frequency
  word_vec_pair_s (string word, Song *song) {
    songs.push_back(word_freq_t(song, 1));
    this->word = word;
  }

  // find the song in the vector
  // if not found, push to the back
  // if found, increment frequency and
  // swap until the song is in the "right" place
  void addWord (Song *song) {
    // this uses the overloaded operator(s)
    vector<word_freq_t>::iterator i = find(songs.begin(), songs.end(), song);
    // found
    if (i != songs.end()) {
      i->freq++;
      // sort(songs.rbegin(), songs.rend()); // sort backwards (i.e. descending)
      sort(songs.begin(), songs.end());

      // shrink back to avoid memory bloat
      // is wrong if compared to 11 or 10 instead
      // TODO: debug
      if (songs.size() > 12)
	songs.resize(10);
    }
    // not found - add to back
    else
      songs.push_back(word_freq_t(song, 1));
  }
  // print all the contexts of this word in every song
  void print () {
    for (vector<word_freq_t>::iterator i = songs.begin(); i != songs.end(); i++)
      cout << i->song->getContext(word);
  }
} word_vec_pair_t;

class HashTable {
 public:
  HashTable () {
    load = 0;
    size = 0;
    contents = NULL;
  }
  // allocate a table size long, but not the elements inside
  HashTable (size_t size) {
    load = 0;
    this->size = size;
    contents = new word_vec_pair_t*[size];
    for (size_t i = 0; i < size; i++)
      contents[i] = NULL;
  }
  // destroy the entire table...
  // TODO: may leak
  ~HashTable () {
    for (size_t i = 0; i < size; i++)
      if (contents[i])
    	delete contents[i];
    delete [] contents;
  }
  void addWord (string word, Song *song);
  word_vec_pair_t *getWord (string word);

 private:
  void insert (string word, Song *song);
  void resize ();
  // get the load factor for the table
  // generally a good idea to keep load < 0.6
  double getLoad () {
    return load/(double) size;
  }

  size_t size, load;
  word_vec_pair_t **contents;
};

#endif
