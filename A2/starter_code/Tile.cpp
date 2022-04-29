#include "Tile.h"

Tile::Tile(char letter, int value):
    letter(letter),
    value(value)
{}
Tile::~Tile() {

}
Tile::Tile(Tile&other):
    letter(other.letter),
    value(other.value)
{}