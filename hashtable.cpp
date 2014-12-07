#include "hashtable.h"

static string alpha_only (string s);

void HashTable::addWord (string word, Song *song) {
        cout << "Load: " << getLoad() << ", size: " << size << endl;
        if (getLoad() > 0.5) resize();
        insert(word, song);
}

word_vec_pair_t *HashTable::getWord (string word) {
        word = alpha_only(word);
        uint32_t hash = hash_string(word);
        size_t probe = 0;
        word_vec_pair_t *res = contents[hash % size];
        if (res)
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
                cout << "if... ";
                size_t probe = 0;
                word_vec_pair_t *res = NULL;
                while ((res = contents[(hash + probe) % size]) != NULL) {
                        if (res->word == word) {
                                res->addWord(word, song);
                                cout << "if done - hit word" << endl;
                                return;
                        }
                        probe++;
                }
                cout << "if done - hit NULL" << endl;
                contents[(hash + probe) % size] = new word_vec_pair_t(word, song);
        }
        else {
                cout << "else... ";
                contents[hash % size] = new word_vec_pair_t(word, song);
                load++;
                cout << "else done" << endl;
        }
}

void HashTable::resize () {
        uint32_t hash = 0;
        size_t newsize = size * 10 + 1;
        word_vec_pair_t *res = NULL;

        cout << "Allocating... ";

        word_vec_pair_t **newcontents = new word_vec_pair_t*[newsize];
        for (size_t i = 0; i < newsize; i++) newcontents[i] = NULL;

        cout << "Finished allocating." << endl;
        cout << "Resizing... ";

        for (size_t i = 0; i < size; i++) {
                if (contents[i]) {
                        size_t probe = 0;
                        hash = hash_string(contents[i]->word);
                        while ((res = newcontents[(hash + probe) % newsize])) {
                                probe++;
                        }
                        newcontents[(hash + probe) % newsize] = contents[i];
                        cout << "Deleting... ";
                        delete contents[i];
                        cout << "Finished deleting." << endl;
                }
        }

        cout << "Finished resizing." << endl;

        delete [] contents;
        contents = newcontents;
        size = newsize;
}

static string alpha_only (string s) {
        // ostringstream ss;
        // for (size_t i = 0; i < s.length(); i++)
        //         if (isalnum(s[i]))
        //                 ss << (char) (tolower(s[i]));
        // return ss.str();

        /* String should be faster than stringstream. */
        string ns = "";
        for (size_t i = 0; i < s.length(); i++)
                if (isalnum(s[i]))
                        ns += (char) tolower(s[i]);
        return ns;
}
