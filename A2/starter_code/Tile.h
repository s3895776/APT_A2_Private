
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// Define a Letter type
typedef char Letter;

// Define a Value type
typedef int Value;

#include <iostream>

class Tile {
public:
   Tile();
   Tile(char letter, int value);
   ~Tile();
   Tile(Tile& other);
   Tile(const Tile& other);
   Value getValue();
   Letter getLetter();
   std::string getTileAsString();  
   

private:
   Letter letter;
   Value  value;
};

#endif // ASSIGN2_TILE_H
