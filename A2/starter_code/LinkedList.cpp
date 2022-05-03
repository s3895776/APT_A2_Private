#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   size = 0;
}

LinkedList::~LinkedList() {
   if (head == nullptr) { return; }

   // Walk list, remove nodes
   Node* curr = this->head;
   while (curr != nullptr){
      Node* temp = curr;
      curr = curr->next;
      delete temp;
   }
}

LinkedList::LinkedList(LinkedList& other):
   head(other.head),
   tail(other.tail),
   size(other.size)
{}

// spec: adding a tile alway adds at the end
void LinkedList::AddTile(Tile& tile){
   size++;

   if (head == nullptr){ //empty list
      //create node
      Node* n = new Node(&tile, nullptr);

      //point head and tail to new node
      this->head = n;
      this->tail = n;
   } else {
      //create node
      Node* n = new Node(&tile, nullptr);

      //set tail.next to new node
      this->tail->next = n;

      //set tail to new node
      this->tail = n;
   }
}

Tile* LinkedList::DrawTile(){ //draw from front
   if (this->head == nullptr){
      std::cout << "\nERROR: Tried to draw from empty LinkedList!" << std::endl;
      return nullptr;
   }

   size--;

   // extract tile from node
   Tile* t = this->head->tile;
   Node* temp = this->head;
   this->head = this->head->next;
   delete temp;

   return t;
}

Tile* LinkedList::DrawTile(Tile& tile){ //draw specific tile
   //search if tile exists
   if (!ContainsTile(tile)){
      std::cout << "\nERROR: Tried to draw tile that is not in LinkedList!" << std::endl;
      return nullptr;
   }

   Tile* outTile = nullptr;
   size--;
   
   //remove and patch list
   Node* curr = this->head;
   Node* prev = nullptr;

   while (curr != nullptr){
      if (curr->tile->letter == tile.letter){
         //tile found
         if (prev == nullptr){
            head = curr->next;
         } else {
            prev->next = curr->next;
         }
         if (curr == tail){
            tail = prev;
            tail->next = nullptr;
         }

         //extract tile
         outTile = curr->tile;
         delete curr;
         break;
      }

      prev = curr;
      curr = curr->next;
   }

   return outTile;

   //order of other tiles must remain the same
   return nullptr;
}

bool LinkedList::ContainsTile(Tile& tile){
   if (this->head == nullptr){return false;}

   bool result = false;

   Node* curr = this->head;
   while (curr != nullptr){
      if (curr->tile->letter == tile.letter){
         result = true;
      }
      curr = curr->next;
   }

   return result;
}

int LinkedList::Count(){
   return size;
}

std::string LinkedList::ToString(){
   if (this->head == nullptr){return "EMPTY";}

   std::string s = "";

   Node* curr = this->head;
   while (curr != nullptr){
      s += curr->tile->letter;
      s += "-";
      s += std::to_string(curr->tile->value);
      curr = curr->next;
      if (curr != nullptr){
         s += ", ";
      }
   }
   
   return s;
}