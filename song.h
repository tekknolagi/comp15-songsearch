#ifndef SONG_H
#define SONG_H

#include <vector>

using namespace std;

typedef vector<string>::iterator vec_iter;

class Song {
 public:
  Song ();
  Song (string artist, string title);
  Song (string artist, string title, string lyrics);

  void setTitle (string title) { this->title = title; };
  string getTitle () { return this->title; };
  void setArtist (string artist) { this->artist = artist; };
  string getArtist () { return this->artist; };
  void setLyrics (string lyrics);
  void addWord (string lyrics);
  string getContext (string word);

 private:
  string title;
  string artist;
  vector<string> lyrics;
};

#endif
