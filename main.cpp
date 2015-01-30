#include "word_list.h"

int main (int argc, char *argv[]) {
  WordList db = WordList();

  // if there is a filename on the command line
  if (argc == 2) {
    db.read_lyrics(argv[1], false);
  }
  // use a pre-defined filename
  else {
    db.read_lyrics("rick_db.txt", false);
  }

  db.repl();

  return 0;
}
