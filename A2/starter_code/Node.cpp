
#include "Node.h"

Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Node& other)
{
   // shallow copy
   next = other.next;
   tile = other.tile;
}
