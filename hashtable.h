#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "hashfunc.h"
#include "song.h"

#define NUM_RESULTS 10
#define ARR_SIZE (NUM_RESULTS+1)

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
  bool operator == (Song *other) {
    return song == other;
  }
  bool operator != (Song *other) {
    return !(*this == other);
  }
} word_freq_t;

typedef struct word_vec_pair_s {
  vector<word_freq_t> songs;
  //word_freq_t songs[ARR_SIZE];
  string word;

  word_vec_pair_s (string word, Song *song) {
    //songs.resize(10);
    songs.push_back(word_freq_t(song, 1));
    this->word = word;
  }
  void addWord (string word, Song *song) {
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
    for (int i = 0; i < size; i++)
      contents[i] = NULL;
  }
  ~HashTable () {
    for (int i = 0; i < size; i++)
      if (contents[i])
	delete contents[i];
    delete [] contents;
  }
  void addWord (string word, Song *song);
  word_vec_pair_t *getWord (string word);

 private:
  void resize ();
  double getLoad () {
    return load/(double) size;
  }

  size_t size, load;
  word_vec_pair_t **contents;
};

#endif
