/*
 * main.cpp
 *
 */
//#include "WordList.h"
#include <iostream>
#include "hashtable.h"

using namespace std;

extern void read_lyrics (HashTable *, const char *, bool);

int main (int argc, char *argv[]) {
        HashTable h = HashTable(100);
	string filename;
	//WordList wordlist;

	if (argc == 2) { // if there is a filename on the command line
                read_lyrics(&h, argv[1],true);
	}
	else { // use a pre-defined filename
		filename = "rick_db.txt";
                //filename = "small.txt";
		//filename = "lyrics_fulldb.txt";
                read_lyrics(&h, filename.c_str(),false);
                cout << "LOADED!" << endl;
                string word = "";
                while (word != "<BREAK>") {
                        cin >> word;
                        h.getWord(word)->print();
                }
	}
        //wordlist.search();

        return 0;
}
