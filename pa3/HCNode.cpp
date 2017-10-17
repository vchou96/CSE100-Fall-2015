#include "HCNode.hpp"
#include <iostream>


bool HCNode::operator<(const HCNode& other) {
  if(this-> count == other.count) {
    return this->symbol > other.symbol;
  }
  else {
    return this->count > other.count;
  }
}

/*bool comp(HCNode* one, HCNode* other) {
  if(one->count < other->count){
    return one->symbol== other->symbol;
  }
  else{
    return false;
  }
}*/

/*bool HCNode::comp(HCNode* one, HCNode* other) {
  return one->count < other.count;
}*/

