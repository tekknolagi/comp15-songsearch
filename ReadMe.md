# ReadMe for COMP 15 HW6
## Song Search 

### Purpose

The purpose of the assignment is to implement a search on a large song database.
In this search, we use a hash table and vectors of Song classes.

### Files

1. `hashfunc.cpp` and `hashfunc.h`
  * Implement the Jenkins hash function used in building the hashtable.
2. `hashtable.cpp` and `hashtable.h`
  * Implement the hashtable used to store the words, songs, and frequencies.
3. `song.cpp` and `song.h`
  * Implement the Song class, which stores artist, title, and lyrics.
4. `read_lyrics.cpp` and `read_lyrics.h`
  * Read the lyrics from a file and add to hashtable.
5. `wordlist.cpp` and `wordlist.h`
  * Some glue to pull all the aforementioned components together.
5. `main.cpp`
  * Run the search on a (large) file.

### Building

`make`

or

`make extras`

### Structures

#### `HashTable`

Holds a table of `word_vec_pair_t`s. Uses the Jenkins hash function.

Hashtables have O(1) insert, delete, and search, not counting probing for
collisions. Jenkins, however, has a pretty good distribution of buckets,
so we can safely say there is not much probing.

#### `word_vec_pair_t`

Holds a vector of `word_freq_t`s and the word that this bucket represents.
The vector is kept in sorted order.

#### `word_freq_t`

Holds a `Song` pointer and frequency that the word in the bucket appears in that
song.

This struct has a few overridden operators so that I could use `std::find` and
`std::sort` without much hassle.

#### `Song`

Holds the artist and title as strings, and space-separated lyrics in a vector.
One can also look up contexts for a given word in a song.

### Algorithms

#### Jenkins lookup3

The lookup3 hash function takes a char array and hashes it into a `uint32_t`.
This particular hash function has a good distribution for fairly random words.

#### `getWord`

Then, try and insert a word. Probe until you hit a NULL spot or the word you are
looking for. Return either.

#### `addWord`

If the load factor of the table is greater than 0.5, resize the table. Then,
check to see if the value at the location exists. If it does exist, check to see
if it's the right word. If it's the right word, increment the frequency and
re-order the results list. If it's not the right word, probe until you hit
either NULL or the right word. If you hit NULL, allocate a new pair.

### Extras! :D

If you run `make extras`, the program will build more tables so that the user
can search on both artist and song title. The program will naturally NOT return
context.

If you wish to speed up build time by only allowing search on artist or only allowing
search on title, compile with `-DARTIST` or `-DTITLE` respectively.

To search by artist:

`a:Rick Astley`

To search by title:

`a:Never Gonna Give You Up`

### Collaborators

* Logan Garbarini
* Prof. Christopher Gregg
