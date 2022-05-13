
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   /*Copy constructor*/
   LinkedList(LinkedList& other);
   LinkedList(const LinkedList& other);
   
   void AddTile(Tile& tile);

   Tile DrawTile();

   /* Draw a specific Tile given a Tile reference.
   If that tile does not exist, return a default constructed tile.
   */
   Tile DrawTile(Tile& tile);

   int Count();

   bool ContainsTile(Tile& tile);
   bool ContainsTile(Letter letter);
   int GetTileValue(Letter letter);

   std::string ToString();

private:
   Node* head;
   Node* tail;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
