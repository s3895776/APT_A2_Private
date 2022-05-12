.default: all

all: scrabble Testing

clean:
	rm -rf scrabble *.o *.dSYM
	rm -rf Testing *.o *.dSYM

scrabble: scrabble.o Node.o Tile.o Game.o Player.o LinkedList.o Board.o 
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

Testing: tests.o Node.o Tile.o Game.o Player.o LinkedList.o Board.o
	g++ -Wall -Werror -std=c++14 -g -O -o Testing $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^


