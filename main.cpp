/*
 * main.cpp
 *
 */

#include "word_list.h"

using namespace std;

int main (int argc, char *argv[]) {
  WordList db = WordList();

  if (argc == 2) // if there is a filename on the command line
    db.read_lyrics(argv[1], false);
  else { // use a pre-defined filename
    db.read_lyrics("rick_db.txt", false);
  }

  db.repl();

  return 0;
}
