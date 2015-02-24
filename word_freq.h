#ifndef WORD_FREQ_H
#define WORD_FREQ_H

#include "song.h"

typedef struct word_freq {
  Song *song;
  int freq;

  // important - resize() will complain if this does not exist
  // needs constructor when adding "empty" elements
  word_freq ();
  word_freq (Song *song, int freq);
  
  // overrode so i could use std::sort
  // sorts BACKWARDS (ie descending order)
  bool operator < (const word_freq &other) const;
  
  // overrode so i could use std::find
  bool operator == (Song *other) const;
  
  // this too
  bool operator != (Song *other) const;
} word_freq;

typedef struct word_vec_pair {
  std::vector<word_freq> songs;
  std::string word;

  // initialize a new pair and add the first frequency
  word_vec_pair (std::string word, Song *song);
  
  // find the song in the std::vector
  // if not found, push to the back
  // if found, increment frequency and
  // swap until the song is in the "right" place
  void addWord (Song *song);
  
  // print all the contexts of this word in every song
  void print (bool context);
} word_vec_pair;

#endif
