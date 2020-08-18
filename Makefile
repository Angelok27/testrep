OBJECTS = obj/interface.o obj/word.o obj/hangman.o obj/game.o
CC = gcc -std=c99 -Wall
LIBS = `pkg-config --cflags --libs gtk+-3.0` -rdynamic

.PHONY: clean prepare

#############

gam/hangman: prepare ${OBJECTS}
	$(CC) -o gam/hangman ${OBJECTS} $(LIBS)

obj/interface.o: src/interface.c
	$(CC) -c src/interface.c -o obj/interface.o $(LIBS)

obj/word.o: src/word.c
	$(CC) -c src/word.c -o obj/word.o $(LIBS)

obj/hangman.o: src/hangman.c
	$(CC) -c src/hangman.c -o obj/hangman.o $(LIBS)

obj/game.o: src/game.c
	$(CC) -c src/game.c -o obj/game.o $(LIBS)

app: gam/hangman
	gam/hangman

test: gam/test
	gam/test

prepare: gam obj

gam:
	mkdir gam

obj:
	mkdir obj

clean:
	rm -f gam/* obj/*.o
