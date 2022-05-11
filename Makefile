EXE = bin/main
SRC = src/main.c src/visualization.c src/routeFinding.c
LINKS = -lSDL2 -lui
INCDIR = -I/usr/local/include/SDL2
all:
	gcc -o $(EXE) $(SRC) $(LINKS) $(INCDIR) && pwd && ./$(EXE) "test"

clean:
	rm -f $(EXE)