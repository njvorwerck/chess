chess: build/chess.o build/TerminalWriter.o
	g++ -o bin/chess build/chess.o build/TerminalWriter.o

build/TerminalWriter.o: src/TerminalWriter.cpp
	g++ -std=c++11 -c -I include/ -o build/TerminalWriter.o src/TerminalWriter.cpp 

build/chess.o: apps/chess.cpp
	g++ -std=c++11 -c -I include/ -o build/chess.o apps/chess.cpp 

.PHONY: clean

clean: 
	rm -f build/* bin/*
