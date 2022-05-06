.default: all

all: scrabble

clean:
	rm -rf scrabble *.o *.dSYM

scrabble: scrabble.o Node.o Tile.o Game.o Player.o LinkedList.o Board.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
