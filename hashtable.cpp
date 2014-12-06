#include "hashtable.h"

static string alpha_only (string s);

void HashTable::addWord (string word, Song *song) {
        word = alpha_only(word);
        uint32_t hash = hash_string(word);

        if (contents[hash % size]) {
                size_t probe = 0;
                word_vec_pair_t *res = NULL;
                while (!((hash + probe) % size == hash % size
                         && probe == 0)) {
                        res = contents[(hash + probe) % size];
                        if (res->word == word) {
                                res->addWord(word, song);
                                return;
                        }
                        probe++;
                }
        }
        else {
                contents[hash % size] = new word_vec_pair_t(word, song);
                load++;
        }
}

word_vec_pair_t *HashTable::getWord (string word) {
        word = alpha_only(word);
        uint32_t hash = hash_string(word);
        size_t probe = 0;
        word_vec_pair_t *res = contents[hash % size];
        if (res)
                while (!((hash + probe) % size == hash % size
                         && probe == 0)) {
                        res = contents[(hash + probe) % size];
                        if (res->word == word) {
                                return res;
                        }
                        probe++;
                }
        else
                return NULL;
}

void HashTable::resize () {
        uint32_t hash = 0;
        size_t newsize = size * 2 + 1;
        word_vec_pair_t **newcontents = new word_vec_pair_t*[newsize];

        for (size_t i = 0; i < size; i++) {
                if (contents[i]) {
                        hash = hash_string(contents[i]->word) % newsize;
                        newcontents[hash] = contents[i];
                }
        }
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
