#include <iostream>
#include "hashtable.h"

using namespace std;

string alpha_only (string s);

// resize if necessary, then add the word
void HashTable::addWord (string word, Song *song) {
  if (getLoad() > 0.5) resize();
  insert(word, song);
}

// find the word in the table using linear probing
word_vec_pair_t *HashTable::getWord (string word) {
  word = alpha_only(word);
  uint32_t hash = hash_string(word);
  size_t probe = 0;
  word_vec_pair_t *res = NULL;
  // probe until you hit NULL - then the element cannot exist
  // can do this because we don't delete from the hashtable
  while ((res = contents[(hash + probe) % size])) {
    if (res->word == word)
      return res;
    probe++;
  }
  // not found :(
  return NULL;
}

void HashTable::insert (string word, Song *song) {
  word = alpha_only(word);
  uint32_t hash = hash_string(word);

  // check to see if anything is at the location
  if (contents[hash % size]) {
    size_t probe = 0;
    word_vec_pair_t *res = NULL;
    // guess not... so probe on
    while ((res = contents[(hash + probe) % size])) {
      // found the word
      if (res->word == word) {
	res->addWord(song);
	return;
      }
      probe++;
    }
    // ah, we hit a NULL - so add a new thing there
    contents[(hash + probe) % size] = new word_vec_pair_t(word, song);
    load++;
  }
  else {
    // add a new pair at the location
    contents[hash % size] = new word_vec_pair_t(word, song);
    load++;
  }
}

// resize the table by 2x
void HashTable::resize () {
  uint32_t hash = 0;
  size_t newsize = size * 2 + 1;

  // initialize the new table's contents to NULL
  word_vec_pair_t **newcontents = new word_vec_pair_t*[newsize];
  for (size_t i = 0; i < newsize; i++) newcontents[i] = NULL;

  for (size_t i = 0; i < size; i++) {
    // re-hash the word and move the contents over
    if (contents[i]) {
      //size_t probe = 0;
      hash = hash_string(contents[i]->word) % newsize;
      //while (newcontents[(hash + probe) % newsize] != NULL) {	
      //}
      while (newcontents[hash] != NULL) {
	if (newcontents[hash]->word == contents[i]->word)
	  break;
	hash = ((hash + 1) % (newsize));
      }
      newcontents[hash] = contents[i];
    }
  }

  // delete the old table, but not the contents
  delete [] contents;
  contents = newcontents;
  size = newsize;
}

string alpha_only (string s) {
  // ostringstream ss;
  // for (size_t i = 0; i < s.length(); i++)
  //         if (isalnum(s[i]))
  //                 ss << (char) (tolower(s[i]));
  // return ss.str();

  /* String should be faster than stringstream. */
  string ns = "";
  for (size_t i = 0; i < s.length(); i++)
    if (isalnum(s[i]))
      ns += (char) tolower(s[i]);
  return ns;
}
