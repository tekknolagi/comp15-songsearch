//
// read_lyrics.cpp
//
//   Code to read in song data from a specified file
//   You may use this code in your project.
//   You will have to add code to process the information as it is read in
//
#include <iostream>
#include <sstream>
#include <fstream>

#include "hashtable.h"
#include "song.h"

using namespace std;

//
// read_lyics 
//   purpose: read in song data from a disk file
//   arguments: the name of the file, bool to ask for progress status
//   returns: nothing
//   does: calls a function each time a word is found
//
void read_lyrics (HashTable *h, const char * filename, bool show_progress) {
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

                Song *s = new Song(artist, title);

		if (show_progress) {
			if (song_count++ % 10000 == 0) {
				cout << "At "       << song_count << 
					" Artist: " << artist     << 
					" Title: "   << title << endl;
			}
		}
		// -- Then read all words until we hit the 
		// -- special <BREAK> token
		while (in >> word && word != "<BREAK>") {
			//
			// -- Found a word
                        s->addWord(word);
                        h->addWord(word, s);
		}

		// -- Important: skip the newline left behind
		in.ignore();
	}

        h->getWord("cry")->print();
}
