all:
	g++ -Isrc/Include -Lsrc/lib -o build/game src/source/*.cpp -lmingw32 -lSDL2main -lSDL2 