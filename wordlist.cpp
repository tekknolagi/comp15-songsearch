#include <iostream>
#include <fstream>
#include <unistd.h>

#include "wordlist.h"

using namespace std;

WordList::WordList () {
  words = new HashTable(1);
  #ifdef ARTISTS
  artistPrefix = "a:";
  artists = new HashTable(1);
  #endif
  #ifdef TITLES
  titlePrefix = "t:";
  titles = new HashTable(1);
  #endif
}

WordList::~WordList () {
  delete words;
  #ifdef ARTISTS
  delete artists;
  #endif
  #ifdef TITLES
  delete titles;
  #endif
  
  // free all the songs from the vector
  Song *cur = NULL;
  while (!songs.empty()) {
    cur = songs.back();
    delete cur;
    cur = NULL;
    songs.pop_back();
  }
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
      words->addWord(word, s);
      #ifdef ARTISTS
      artists->addWord(artist, s);
      #endif
      #ifdef TITLES
      titles->addWord(title, s);
      #endif
    }

    // -- Important: skip the newline left behind
    in.ignore();
  }
}

void WordList::search (string term) {
  word_vec_pair_t *res = words->getWord(term);
  #ifdef ARTISTS
  // searching by artist: "does it start with 'a:'?"
  if (!term.compare(0, artistPrefix.size(), artistPrefix)) {
    string name = term.substr(artistPrefix.size());
    res = artists->getWord(name);
    // no word context
    if (res) res->print(false);
  }
  // searching by title
  #endif
  #ifdef TITLES
  if (!term.compare(0, titlePrefix.size(), titlePrefix)) {
    string name = term.substr(titlePrefix.size());
    res = titles->getWord(name);
    // no word context
    if (res) res->print(false);
  }
  #endif
  res = words->getWord(term);
  // yes word context
  if (res) res->print(true);
}

void WordList::repl () {
  string term = "";
  while (true) {
    if (isatty(0))
      cout << "> "; 
    // asked to break by user, and did not hit EOF
    if (getline(cin, term) && term == "<BREAK>") break;
    // search table for term... and print
    search(term);
    cout << "<END OF REPORT>" << endl;
  }
}
