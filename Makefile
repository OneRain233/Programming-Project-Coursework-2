EXE = bin/main
SRC = src/main.c src/visualization.c src/routeFinding.c src/interface.c
LINKS = -lSDL2 -lui
INCDIR = -I/usr/include/SDL2
all:
	gcc -o $(EXE) $(SRC) $(LINKS) $(INCDIR)
	./$(EXE)

clean:
	rm -f $(EXE)
