CC = gcc

CFLAGS = -g -std=c++11 -lstdc++
 
all: frontEnd

frontEnd: main.cpp token.hpp scanner.hpp scanner.cpp parser.hpp parser.cpp semantics.hpp semantics.cpp
	$(CC) -o $@ $^ $(CFLAGS) 
 
clean:
	rm frontEnd 
	rm -r *.dSYM