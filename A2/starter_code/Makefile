.default: all

all: scrabble

clean:
	rm -rf scrabble *.o *.dSYM

<<<<<<< HEAD
scrabble: Tile.o Node.o LinkedList.o scrabble.o Game.o Board.o Player.o
=======
scrabble: scrabble.o Node.o Tile.o Game.o Player.o LinkedList.o Board.o
>>>>>>> main
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
