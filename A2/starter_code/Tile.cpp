#include "Tile.h"

Tile::Tile():
    letter('_'),
    value(0)
{}
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

std::string Tile::getTileAsString() {
    std::string tileString;
    tileString.push_back(this->getLetter());
    tileString.push_back('-');
    tileString.push_back(this->getValue());
    return tileString;
}

Value Tile::getValue() {
    return value;
}

Letter Tile::getLetter() {
    return letter;
}