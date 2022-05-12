#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   size = 0;
}

LinkedList::~LinkedList() {
   // if (head == nullptr) { return; }
   // unnecessary since Node* curr will be nullptr if head is nullptr

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

LinkedList::LinkedList(const LinkedList& other):
   head(other.head),
   tail(other.tail),
   size(other.size)
{}

// spec: adding a tile alway adds at the end
void LinkedList::AddTile(Tile& tile){
   size++;

   if (head == nullptr){ //empty list
      //create node
      Node* n = new Node(tile, nullptr);

      //point head and tail to new node
      this->head = n;
      this->tail = n;
   } else {
      //create node
      Node* n = new Node(tile, nullptr);

      //set tail.next to new node
      this->tail->next = n;

      //set tail to new node
      this->tail = n;
   }
}

Tile LinkedList::DrawTile(){ //draw from front
   if (this->head == nullptr){
      //std::cerr << "\nERROR: Tried to draw from empty LinkedList!" << std::endl;
      // Maybe an issue if returning a constructed Tile. 
      return Tile();
   }

   size--;

   // extract tile from node
   Tile t = this->head->tile;
   Node* temp = this->head;
   this->head = this->head->next;
   delete temp;

   return t;
}

Tile LinkedList::DrawTile(Tile& tile){ 

   Node* curr = this->head;
   Node* prev = nullptr;
   Tile outTile = Tile();
   bool result = false;

   while ( (curr != nullptr) & !(result) ) {

      if (curr->tile.getLetter() == tile.getLetter() ) {
         result = true;
         outTile = curr->tile;
      }

      else {
         prev = curr;
         curr = curr->next;
      }

   }
   
   if (result) {
      --size;

      if (prev == nullptr) {
         Node* deletedNode = head;
         head = head->next;
         delete deletedNode;
      } 
      
      else {
         Node* deletedNode = curr;
         prev->next = curr->next;
         delete deletedNode;
      }

      if (curr == tail) {
         Node* deletedNode = tail;
         tail = prev;
         tail->next = nullptr;
         delete deletedNode;
      }

   }

   return outTile;
}

bool LinkedList::ContainsLetter(Letter letter) {
   bool containsLetter = false;

   Node* curr = this->head;
   while (curr != nullptr) {
      if (curr->tile.getLetter() == letter) {
         containsLetter = true;
      }
      curr = curr->next;
   }

   return containsLetter;
}

Tile LinkedList::RemoveTile(Letter letter) {
   Node* node_removedTile;
   
   Node* curr = this->head;

   // head node has the letter
   if (curr->tile.getLetter() == letter) {
      node_removedTile = curr;
      // reassign head to next node
      this->head = curr->next;
   }
   // non-head node has the letter
   else {
      while (curr->next != nullptr) {
         // next node of current has the letter
         if (curr->next->tile.getLetter() == letter) {
            // assign the node to the next node withthe letter
            node_removedTile = curr->next;
            // ignore the next node
            curr->next = curr->next->next;
         } else {
            curr = curr->next;
         }
      }
   }

   return node_removedTile->tile;
}

// bool LinkedList::ContainsTile(Tile& tile){
//    // if (this->head == nullptr){return false;}
//    bool result = false;
//    Node* curr = this->head;
//    while (curr != nullptr) {
//       if (curr->tile.getLetter() == tile.getLetter()){
//          result = true;
//       }
//       curr = curr->next;
//    }
//    return result;
// }
// int LinkedList::Count(){
//    return size;
// }

std::string LinkedList::ToString(){
   std::string s = "";

   if (this->head == nullptr) {
      // this is the reason the test fails. Which string is preferable?
      s = "EMPTY";
   }


   Node* curr = this->head;
   while (curr != nullptr){
      // s += curr->tile->getLetter();
      // s += "-";
      // s += std::to_string(curr->tile->getValue());
      s += curr->tile.getTileAsString();

      curr = curr->next;
      if (curr != nullptr){
         s += ", ";
      }
   }
   
   return s;
}

int LinkedList::Count() {
   return size;
}