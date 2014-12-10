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
  void search (string term);
  void repl ();

 private:
  HashTable *words;
  #ifdef ARTISTS
  string artistPrefix;
  HashTable *artists;
  #endif
  #ifdef TITLES
  string titlePrefix;
  HashTable *titles;
  #endif
  vector<Song *> songs;
};

#endif
