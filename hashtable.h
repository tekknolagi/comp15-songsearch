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
  word_freq_s () {}
  word_freq_s (Song *song, int freq) {
    this->song = song;
    this->freq = freq;
  }
  // overrode so i could use std::find
  bool operator == (Song *other) {
    if (!other) return false;
    return song == other;
  }
  bool operator != (Song *other) {
    if (!other) return false;
    return song != other;
    // might be very slow according to perf
    // return !(*this == other);
  }
} word_freq_t;

typedef struct word_vec_pair_s {
  vector<word_freq_t> songs;
  string word;

  word_vec_pair_s (string word, Song *song) {
    //songs.resize(10);
    songs.push_back(word_freq_t(song, 1));
    this->word = word;
  }
  void addWord (string word, Song *song) {
    (void)word; // make clang happy // TODO: fix
    vector<word_freq_t>::iterator i = find(songs.begin(), songs.end(), song);
    // found
    if (i != songs.end()) {
      i->freq++;
      // not at beginning; moveable
      while (i != songs.begin() && (i-1)->freq < i->freq) {
	iter_swap(i, i-1);
	i--;
      }

      if (songs.size() > 10)
	songs.resize(10);
    }
    // not found
    else
      songs.push_back(word_freq_t(song, 1));
  }
  void print () {
    for (vector<word_freq_t>::iterator i = songs.begin(); i != songs.end(); i++)
      cout << i->song->getContext(word);
  }
} word_vec_pair_t;

class HashTable {
 public:
  HashTable () {
    size = 0;
    contents = NULL;
  }
  HashTable (size_t size) {
    this->size = size;
    contents = new word_vec_pair_t*[size];
    for (size_t i = 0; i < size; i++)
      contents[i] = NULL;
  }
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
  double getLoad () {
    return load/(double) size;
  }

  size_t size, load;
  word_vec_pair_t **contents;
};

#endif
