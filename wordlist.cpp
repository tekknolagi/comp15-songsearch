#include <iostream>
#include <fstream>
#include <unistd.h>

#include "wordlist.h"

using namespace std;

WordList::WordList () {
  words = HashTable(1);
  artists = HashTable(1);
  titles = HashTable(1);
}

WordList::~WordList () {
  // free all the songs from the vector
  // Song *cur = NULL;
  // while (!songs.empty()) {
  //   cur = songs.back();
  //   delete cur;
  //   cur = NULL;
  //   songs.pop_back();
  // }
}

//
// read_lyics 
//   purpose: read in song data from a disk file
//   arguments: the name of the file, bool to ask for progress status
//   returns: nothing
//   does: calls a function each time a word is found
//
void WordList::read_lyrics (const char * filename, bool show_progress) {
  ifstream in(filename);			// creates an input stream
  int song_count = 0;			// for progress indicator
  string artist, title, word;

  // -- While more data to read...
  while (!in.eof()) {
    // -- First line is the artist
    getline(in, artist);
    if (in.fail()) break;

    // -- Second line is the title
    getline(in, title);
    if (in.fail()) break;

    // add the song to the vector to delete later
    Song *s = new Song(artist, title);
    songs.push_back(s);

    // print song every 10000 processed
    if (show_progress && !(++song_count % 10000)) {
      cout << "At "       << song_count << 
	" Artist: " << artist     << 
	" Title: `"   << title << "`" << endl;
    }

    // -- Then read all words until we hit the 
    // -- special <BREAK> token
    while (in >> word && word != "<BREAK>") {
      // -- Found a word
      // add word to song
      s->addWord(word);
      // add word to table
      words.addWord(word, s);
    }

    // -- Important: skip the newline left behind
    in.ignore();
  }
}

word_vec_pair_t *WordList::search (string term) {
  return words.getWord(term);
}

void WordList::repl () {
  string term = "";
  word_vec_pair_t *res = NULL;
  while (true) {
    if (isatty(0))
      cout << "> "; 
    // asked to break by user, and did not hit EOF
    if ((cin >> term) && term == "<BREAK>") break;
    // search table for term...
    res = search(term);
    // ... and print results
    if (res) res->print();
    cout << "<END OF REPORT>" << endl;
  }
}
