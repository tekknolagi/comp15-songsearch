#
# Makefile for SongSearch, Assignment 6
#
CXX = clang++
FLAGS = -Wall -O3

songsearch: #<your .cpp and .h files go here>
	${CXX} ${FLAGS} -o songsearch main.cpp song.cpp hashtable.cpp hashfunc.cpp read_lyrics.cpp

clean:
	rm -f songsearch

provide_design:
	provide comp15 hw6_design songsearch_design.txt

provide:
	provide comp15 hw6 Makefile main.cpp song.cpp hashtable.cpp hashfunc.cpp read_lyrics.cpp song.h hashtable.h hashfunc.h read_lyrics.h

