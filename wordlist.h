#ifndef WORDLIST_H
#define WORDLIST_H

#include "heap.h"

class WordList {
 public:
  WordList();
  ~WordList();

  read_lyrics(char *, bool);
  search();

 private:
  // ensure about 70% load (no collisions)
  // consider http://en.wikipedia.org/wiki/Jenkins_hash_function ?
  const size_t HASHTABLE_SIZE = 285700;
  (MaxHeap *) hash_table[HASHTABLE_SIZE] = { 0 };
};

#endif
