#ifndef WORDLIST_H
#define WORDLIST_H

#include <vector>

#include "song.h"
#include "hashtable.h"

class WordList {
 public:
  WordList ();
  ~WordList ();

  void read_lyrics (const char *, bool);
  word_vec_pair_t *search (string term);
  void repl ();

 private:
  HashTable words;
  HashTable artists;
  HashTable titles;
  vector<Song *> songs;
};

#endif
