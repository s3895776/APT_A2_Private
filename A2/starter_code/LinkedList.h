
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   void AddTile(Tile& tile);

   Tile* DrawTile();
   Tile* DrawTile(Tile& tile);

   int Count();

   bool ContainsTile(Tile& tile);

   std::string ToString();

private:
   Node* head;
   Node* tail;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
