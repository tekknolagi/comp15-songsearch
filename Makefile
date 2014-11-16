#
# Makefile for SongSearch, Assignment 6
#
CXX = clang++
FLAGS = -Wall -g3

songsearch: <your .cpp and .h files go here>
	${CXX} ${FLAGS} -o songsearch <your .cpp files go here>
	
clean:
	rm -f songsearch

provide_design:
	provide comp15 hw5_design songsearch_design.txt

provide:
	provide comp15 hw5 <all your files go here>

