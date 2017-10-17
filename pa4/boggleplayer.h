

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"
#include <string>

using namespace std;

class BogglePlayer : public BaseBogglePlayer {
  public:
  void buildLexicon(const set<string>& word_list);
  
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  void helper(string validWord, int index, unsigned int minimum_word_length, set<string>* words, int length, int visitedArr[]);


  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

bool helperisOnBoard(const string& wordLower, int wordPos, int currPos, vector<int>& result, int visitedArr[]);


  void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

  int getRow (int arrayPos);

int getColumn (int arrayPos);

void getNeighbor(int arrayPos, signed int neighborArr []);

  BogglePlayer() {
    boardArr=0;
  }
  
  ~BogglePlayer() {
     if(boardArr){

      delete[] (boardArr);

      boardArr=0;
     }
     deleteNodes(lexTree.root);
     lexTree.root=0;

  }
  void deleteBogglePlayer();
  void deleteNodes(boggleNode* node);

  string* boardArr; 
  private:
  boggleTrie lexTree;
};

#endif
