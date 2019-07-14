chess: build/chess.o build/TerminalWriter.o build/TileRenderer.o
	g++ -o bin/chess build/chess.o build/TerminalWriter.o build/TileRenderer.o

build/TerminalWriter.o: src/TerminalWriter.cpp
	g++ -std=c++11 -c -I include/ -o build/TerminalWriter.o src/TerminalWriter.cpp 

build/TileRenderer.o: src/TileRenderer.cpp
	g++ -std=c++11 -c -I include/ -o build/TileRenderer.o src/TileRenderer.cpp 

build/chess.o: apps/chess.cpp
	g++ -std=c++11 -c -I include/ -o build/chess.o apps/chess.cpp 

.PHONY: clean

clean: 
	rm -f build/* bin/*
