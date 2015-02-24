#
# Makefile for SongSearch, Assignment 6
#
CXX ?= clang++
# FLAGS = -g3 
FLAGS = -Wall -O3  -W -Wextra -pedantic #-Werror

songsearch: 
	${CXX} ${FLAGS} -o songsearch main.cpp song.cpp word_freq.cpp \
	hash_table.cpp hash_func.cpp read_lyrics.cpp word_list.cpp

extras: FLAGS += -DARTISTS -DTITLES
extras: songsearch

clean:
	rm -f songsearch

