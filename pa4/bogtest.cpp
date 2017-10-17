/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;
//  string wordA("abcde");
 string wordA("apple");
  string wordX("x");
  lex.insert(wordA);
  lex.insert("z");
string row0[] = {"a","p","l"};
string row1[] = {"p","q","e"};
//  string row0[] = {"De","C"};
 // string row1[] = {"b","A"};
  string* board[] = {row0,row1};
  set<string> words;
  vector<int> locations;

  p->buildLexicon(lex);

  p->setBoard(2,3,board);

/*  if(p->isInLexicon(wordX)) {
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
    return -1;
  }*/
  if(!p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }

 /* if(p->isOnBoard(wordX).size() > 0) {
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }*/

  locations.clear();
  locations = p->isOnBoard(wordA);
  if(locations.size() != 5 || locations[0] != 0) {
    std::cerr << locations.size() << std::endl;
    std::cerr << locations[0] << std::endl;
    std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
    return -1;
  }

  locations.clear();  
  locations = p->isOnBoard("x");
  if(locations.size() != 0) {
    std::cerr << "problem" << std::endl;
  }

  locations.clear();  
  locations = p->isOnBoard("aba");
  if(locations.size() != 0) {
    std::cerr << "problem" << std::endl;
  }

  

  if(!p->getAllValidWords(0,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    return -1;
  };

  if(words.size() != 1 || words.count(wordA) != 1) {
    std::cerr << "words thing: " << words.size() << " & " << words.count(wordA) <<std::endl;
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    return -1;
  }

  delete p;
  return 0;

}
