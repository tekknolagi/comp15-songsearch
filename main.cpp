/*
 * main.cpp
 *
 */
#include <iostream>
#include <unistd.h>
#include <vector>
#include "hashtable.h"

using namespace std;

extern void read_lyrics (HashTable *, vector<Song *> *, const char *, bool);

int main (int argc, char *argv[]) {
  HashTable h = HashTable(1);
  string filename;
  vector<Song *> songs;

  if (argc == 2) // if there is a filename on the command line
    read_lyrics(&h, &songs, argv[1],true);
  else { // use a pre-defined filename
    filename = "rick_db.txt";
    read_lyrics(&h, &songs, filename.c_str(), false);
  }

  string word = "";
  word_vec_pair_t *res = NULL;
  while (true) {
    if (isatty(0))
      cout << "> "; 
    // asked to break by user, and did not hit EOF
    if ((cin >> word) && word == "<BREAK>") break;
    // search table for word...
    res = h.getWord(word);
    // ... and print results
    if (res) res->print();
    cout << "<END OF REPORT>" << endl;
  }

  // free all the songs from the vector
  Song *cur = NULL;
  while (!songs.empty()) {
    cur = songs.back();
    delete cur;
    cur = NULL;
    songs.pop_back();
  }

  return 0;
}
