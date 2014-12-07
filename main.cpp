/*
 * main.cpp
 *
 */
#include <iostream>
#include <vector>
#include "hashtable.h"

using namespace std;

extern void read_lyrics (HashTable *, vector<Song *> *, const char *, bool);

int main (int argc, char *argv[]) {
        HashTable h = HashTable(1);
	string filename;
	vector<Song *> songs;
	//WordList wordlist;

	if (argc == 2) { // if there is a filename on the command line
	  read_lyrics(&h, &songs, argv[1],true);
	}
	else { // use a pre-defined filename
		filename = "rick_db.txt";
                //filename = "small.txt";
		//filename = "lyrics_fulldb.txt";
                read_lyrics(&h, &songs, filename.c_str(),false);
	}

        string word = "";
        while (cout << "> " && cin >> word && word != "<BREAK>") {
                word_vec_pair_t *res = h.getWord(word);
                if (res) res->print();
		cout << "<END OF REPORT>" << endl;
        }

	Song *cur = NULL;
	while (!songs.empty()) {
	  cur = songs.back();
	  delete cur;
	  cur = NULL;
	  songs.pop_back();
	}

        return 0;
}
