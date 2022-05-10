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
      std::cout << "\nERROR: Tried to draw from empty LinkedList!" << std::endl;
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

Tile LinkedList::DrawTile(Tile& tile){ //draw specific tile
   //search if tile exists
   // if (!ContainsTile(tile)) {
   //    std::cout << "\nERROR: Tried to draw tile that is not in LinkedList!" << std::endl;
   //    return Tile();
   // }

   // --size;
   // Tile* outTile = nullptr;

   // //remove and patch list
   // Node* curr = this->head;

   // while (curr != nullptr){
   //    if (curr->tile->getLetter() == tile.getLetter()){
   //       //tile found
   //       if (prev == nullptr){
   //          head = curr->next;
   //       } else {
   //          prev->next = curr->next;
   //       }
   //       if (curr == tail){
   //          tail = prev;
   //          tail->next = nullptr;
   //       }

   //       //extract tile
   //       outTile = curr->tile;
   //       delete curr;
   //       break;
   //    }

   //    prev = curr;
   //    curr = curr->next;
   // }

   // return outTile;


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