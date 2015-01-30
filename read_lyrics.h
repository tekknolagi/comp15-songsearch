//
//  read_lyrics.h
//  Reads in lyrics from a database, given the filename
//

#ifndef __read_lyrics__
#define __read_lyrics__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>

using namespace std;

#include "hash_table.h"

// read the lyrics from a file
void read_lyrics (HashTable *h, vector<Song *> *songs, char *filename,
                  bool show_progress);

#endif
