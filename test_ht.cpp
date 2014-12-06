#include <iostream>

#include "song.h"
#include "hashtable.h"

using namespace std;

int main () {
        Song a = Song("artist", "title", "hello world");
        Song b = Song("artist2", "title2", "hallo2tha world");
        HashTable h = HashTable(10);

        h.addWord("hello", &b);

        h.addWord("Hello", &a);
        h.addWord("heLl!o", &a);
        h.addWord("hello", &a);
        h.addWord("hello", &a);

        h.addWord("world", &a);
        h.addWord("world", &a);

        h.addWord("world", &b);
        h.addWord("world", &b);
        h.addWord("world", &b);

        h.getWord("hello")->print();
        h.getWord("world")->print();
}
