
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// Define a Letter type
typedef char Letter;

// Define a Value type
typedef int Value;

#include <iostream>

class Tile {
public:
   Tile(char letter, int value);
   ~Tile();
   Tile(Tile& other);

   std::string getTileAsString();  
   Letter letter;
   Value  value;

private:
   Value getValue();
   Letter getLetter();
   
};

#endif // ASSIGN2_TILE_H
