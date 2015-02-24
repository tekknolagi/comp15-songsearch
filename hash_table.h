#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "word_freq.h"
#include "hash_func.h"
#include "song.h"

class HashTable {
public:
  HashTable ();

  // allocate a table size long, but not the elements inside
  HashTable (size_t size);

  // destroy the entire table...
  // TODO: may leak
  ~HashTable ();

  void addWord (std::string word, Song *song);
  word_vec_pair *getWord (std::string word);

private:
  void insert (std::string word, Song *song);
  void resize ();
  // get the load factor for the table
  // generally a good idea to keep load < 0.6
  double getLoad ();

  double load;
  size_t size;
  word_vec_pair **contents;
};

#endif
