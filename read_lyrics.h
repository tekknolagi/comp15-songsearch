//
//  read_lyrics.h
//  Reads in lyrics from a database, given the filename
//

#ifndef __read_lyrics__
#define __read_lyrics__

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "hashtable.h"

// read the lyrics from a file
void read_lyrics(HashTable *h, char * filename, bool show_progress );

#endif
