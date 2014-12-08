#include <iostream>
#include "hashtable.h"

using namespace std;

string alpha_only (string s);

void HashTable::addWord (string word, Song *song) {
        if (getLoad() > 0.5) resize();
        insert(word, song);
}

word_vec_pair_t *HashTable::getWord (string word) {
        word = alpha_only(word);
        uint32_t hash = hash_string(word);
        size_t probe = 0;
        word_vec_pair_t *res = NULL;
	while ((res = contents[(hash + probe) % size])) {
	  if (res->word == word)
	    return res;
	  probe++;
	}
        return NULL;
}

void HashTable::insert (string word, Song *song) {
        word = alpha_only(word);
        uint32_t hash = hash_string(word);

        if (contents[hash % size]) {
                size_t probe = 0;
                word_vec_pair_t *res = NULL;
                while ((res = contents[(hash + probe) % size]) != NULL) {
                        if (res->word == word) {
                                res->addWord(song);
                                return;
                        }
                        probe++;
                }
                contents[(hash + probe) % size] = new word_vec_pair_t(word, song);
		load++;
        }
        else {
                contents[hash % size] = new word_vec_pair_t(word, song);
                load++;
        }
}

void HashTable::resize () {
        uint32_t hash = 0;
        size_t newsize = size * 2 + 1;
        word_vec_pair_t *res = NULL;

        word_vec_pair_t **newcontents = new word_vec_pair_t*[newsize];
        for (size_t i = 0; i < newsize; i++) newcontents[i] = NULL;

        for (size_t i = 0; i < size; i++) {
                if (contents[i]) {
                        size_t probe = 0;
                        hash = hash_string(contents[i]->word);
                        while ((res = newcontents[(hash + probe) % newsize]) && probe++);
                        newcontents[(hash + probe) % newsize] = contents[i];
                }
        }

	delete [] contents;
        contents = newcontents;
        size = newsize;
}

string alpha_only (string s) {
        // ostringstream ss;
        // for (size_t i = 0; i < s.length(); i++)
        //         if (isalnum(s[i]))
        //                 ss << (char) (tolower(s[i]));
        // return ss.str();

        /* String should be faster than stringstream. */
        string ns = "";
        for (size_t i = 0; i < s.length(); i++)
                if (isalnum(s[i]))
		  //ns.append(1, (char) tolower(s[i]));
		  ns += (char) tolower(s[i]);
        return ns;
}
