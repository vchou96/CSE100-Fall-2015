

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
#include <iostream>
//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.
//
class boggleNode {
public:  
  char symbol;
  int end;
  boggleNode* a0 [26];
  
  
  boggleNode(char symbol, int end) : symbol(symbol), end(end) {
    for(int i = 0; i<26; i++) {
      a0[i] = 0;
    }
  }

  
};

class boggleTrie {
public:  
  boggleNode* root;
  boggleTrie() : root(0) {}
  /*void printTree (boggleNode* node) {
    for(int i = 0; i < 26; i++) { 
    if(node->a0[i]) {
      std::cout << node->a0[i]->symbol << std::endl;
      printTree(node->a0[i]);
    }
    }*/
      
 //   }
  

};

#endif
