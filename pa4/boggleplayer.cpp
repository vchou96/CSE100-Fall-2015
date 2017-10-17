#include "boggleplayer.h"
#include <iostream>
#include <string>
#include <set>
#include <stdio.h>
#include <string.h>
//#include "boggleutil.h"
#include <stack>
#include <locale>        

bool boardSet = false;
bool lexiconBuilt = false;
std::locale loc;
string boardLower;
int totalRows;
int totalCols;
int currRow;
int currCol;



void BogglePlayer::buildLexicon(const set<string>& word_list){
  if(lexTree.root){
    deleteNodes(lexTree.root);
    lexTree.root=0;
  }
  lexTree.root = new boggleNode(0, 0);  
  boggleNode* temp = lexTree.root;
  set<string>::iterator vit = word_list.begin();
  set<string>::iterator ven = word_list.end();
  
  //for each word
  for(vit = word_list.begin(); vit != ven; ++vit){
    char lexWord[strlen((*vit).c_str())];
    strcpy(lexWord, (*vit).c_str());
    
    //for each letter of the word
    for(int i = 0; i < (int)strlen((*vit).c_str()); i++) {
      int nodeArr = lexWord[i] - 97; 
      if(!temp->a0[nodeArr]) {
        boggleNode* temp2 = new boggleNode(lexWord[i], 0);
        temp->a0[nodeArr] = temp2;
      }

      temp = temp->a0[nodeArr];
    }
    temp->end = 1;
    temp = lexTree.root;
  }
  lexiconBuilt = true;
  //lexTree.printTree(lexTree.root);
}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
  deleteBogglePlayer();
  totalRows = rows;
  totalCols = cols;  

  int pos=0;
  boardArr = new string [rows*cols];
  for(int i =0; i<(int)rows; i++){
    for(int j=0; j< (int)cols; j++) {
      string boardStr = diceArray[i][j];
      for(unsigned int i = 0; i < boardStr.size(); i++){
        boardLower= boardLower + tolower(boardStr[i], loc);
      }
      boardArr[pos] = boardLower;
      boardLower = "";
      pos++;
    } 
  }
  boardSet = true;

}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
  if(!boardSet && !lexiconBuilt) {
    return false;
  }

  for(int i=0; i<totalRows*totalCols; i++){
    int length = 0;    
int visitedArr[totalRows*totalCols];
  for(int k = 0; k<totalRows*totalCols;k++){
    visitedArr[k] = 0;
  }
    string validWord = boardArr[i];
    length++;
    if(length >= (int)minimum_word_length) {
      if(isInLexicon(validWord) && !(isOnBoard(validWord)).empty()) {
        words->insert(validWord);
      }
    }
    visitedArr[i]=1;
    helper(validWord, i, minimum_word_length, words, length, visitedArr);
  }
  return true;
}

void BogglePlayer::helper(string validWord, int index, unsigned int minimum_word_length, set<string>* words, int length, int visitedArr[]){
  int neighborArr[8];
  for(int k = 0; k<8;k++){
    neighborArr[k] = (totalRows*totalCols)+2;
  }
  
  int length2 = length;
  if(length > totalRows*totalCols){
    return;
  }
  getNeighbor(index, neighborArr);
  string validW = validWord;

  for(int j=0; j<8; j++){
    validWord = validW;
    length=length2;
    if(neighborArr[j] >= 0 && neighborArr[j] < totalRows*totalCols && visitedArr[neighborArr[j]]==0){
      validWord = validWord + boardArr[neighborArr[j]];
      length++;
      visitedArr[neighborArr[j]] = 1;
      if(length >= (int)minimum_word_length) {
        if(isInLexicon(validWord)) {
          words->insert(validWord);
        }
      }
        helper(validWord, neighborArr[j], minimum_word_length, words, length, visitedArr);
    visitedArr[neighborArr[j]]=0;
    
    }
  }
}



bool BogglePlayer::isInLexicon(const string& word_to_check) {
  if(!lexiconBuilt) {
    return false;
  }
  char wordArr[word_to_check.size()];
  strcpy(wordArr, word_to_check.c_str());
  
  boggleNode* temp = lexTree.root;
  if(!temp->a0[wordArr[0]-97]) {
    return false;
  }
  temp = temp->a0[wordArr[0]-97];
  for(unsigned int i = 1; i < word_to_check.size(); i++) {
    if(temp->a0[wordArr[i]-97]) {
      temp = temp->a0[wordArr[i]-97];
    }
    else {
      return false;
    }
  }
  if(!temp->end) {
    return false;
  }
  return true;
}

vector<int> BogglePlayer::isOnBoard(const string& word) {
  vector<int> result;
  vector<int> zeroResult;
  int firstLetter = 0;
  int currPos = 0;
//  int indexBoard = 0;
//  int visitedArr[totalRows*totalCols] = {0};
int visitedArr[totalRows*totalCols];
  for(int k = 0; k<totalRows*totalCols;k++){
    visitedArr[k] = 0;
  }
  int wordPos = 0;
 
 // int neighborArr[8] = {totalRows*totalCols + 2};
//int neighborArr[8];
 // for(int k = 0; k<8;k++){
  //  neighborArr[k] = (totalRows*totalCols)+2;
 // }
 // bool returnEmpty;
  if(!boardSet){
    return zeroResult;
  }
  
  string wordLower;
  //convert to lower case
  for(unsigned int i = 0; i<word.size(); i++){
    wordLower= wordLower + std::tolower(word[i], loc); 
  }

  //find first letter/string
  string boardSize;
  while(currPos<totalRows*totalCols) {
    string boardStr = boardArr[currPos];
    if((wordLower.substr(0, boardStr.size())).compare(boardStr) == 0) {
      firstLetter = 1;
      visitedArr[currPos]=1;
      result.push_back(currPos);
      boardSize = boardStr;
      wordPos = wordPos+boardSize.size();
      if(helperisOnBoard(wordLower, wordPos,currPos, result, visitedArr)){
        return result;
      }
      else{
        firstLetter=0;
        wordPos = wordPos-boardSize.size();
      }
    }
    //indexBoard++;
    currPos++;
  }

  if(!firstLetter) {
    return zeroResult;
  }
/*  wordPos = wordPos+boardSize.size();
  
  if(!helperisOnBoard(wordLower, wordPos,currPos, result, visitedArr)){
    return zeroResult;
  }*/
  return result;
}
    

bool BogglePlayer::helperisOnBoard(const string& wordLower, int wordPos, int currPos, vector<int>& result, int visitedArr[]){
  //int visitedArr[totalRows*totalCols] = {0};
  //int wordPos = 0;
  int temp=currPos;
  int temp2 = wordPos;
  int neighPos = 0;
  int neighFound=0;
  bool returnVal = false;
 // int neighborArr[8] = {totalRows*totalCols + 2};
 int neighborArr[8];
  for(int k = 0; k<8;k++){
    neighborArr[k] = (totalRows*totalCols)+2;
  }
  getNeighbor(currPos, neighborArr);
  string neighStr = "";
  if(wordPos == (int)wordLower.size()){
    return true;
  }
  while(neighPos<8){
    if(neighborArr[neighPos] >= 0 && neighborArr[neighPos] < totalRows*totalCols){
      neighStr = boardArr[neighborArr[neighPos]];
      if(wordLower.substr(wordPos, neighStr.size()).compare(neighStr)==0){
        if(!visitedArr[neighborArr[neighPos]]) {
          currPos = neighborArr[neighPos];
          visitedArr[currPos]=1;
          neighFound=1;
          result.push_back(currPos);
          wordPos = wordPos+neighStr.size();
          returnVal=helperisOnBoard(wordLower,wordPos,currPos, result, visitedArr);
          if (returnVal){
            return true;
          }
          currPos=temp;
    if(neighPos!=7)
      wordPos = temp2;

        }
      }
    }
    neighPos++;

  }

  if(neighPos==8 && wordPos+1 !=  (int)wordLower.size()){
    neighFound=0;
  }
  if(!neighFound ){
    //backtracked =true;
    //visitedArr={0};
    visitedArr[currPos] = 0;
    result.pop_back();
    wordPos = wordPos-neighStr.size();
    if(result.empty()){
      return returnVal;
    }
  }
  return returnVal;
//neighFound=0;
}

//all the rest
 // int backtrackIndex=0;
 /* bool backtracked =0;
  while(wordPos < word.size()) {
    getNeighbor(currPos,neighborArr);
    neighPos=0;
    string neighStr = "";
    while(neighPos < 8) {
      if(neighborArr[neighPos] >= 0 && neighborArr[neighPos] < totalRows*totalCols){
      neighStr = boardArr[neighborArr[neighPos]];
       //std::cerr<<"word: "<<wordLower.substr(wordPos, neighStr.size())<<std::endl;
      //std::cerr<<"neighStr: "<<neighStr<<std::endl;
      //std::cerr<<"neighpos: "<<neighPos<<std::endl;

     
        if(wordLower.substr(wordPos, neighStr.size()).compare(neighStr)==0){
      //std::cerr<<"HERE "<<neighStr<<std::endl;

          if(!visitedArr[neighborArr[neighPos]]) {
            currPos = neighborArr[neighPos];
            visitedArr[currPos]=1;
            neighFound=1;
            result.push_back(currPos);
            wordPos = wordPos+neighStr.size();
            break;
          }
          if(backtracked && visitedArr[neighborArr[neighPos]]){
            visitedArr[neighborArr[neighPos]]=0;
          }

        }
      }
      neighPos++;
    }
    //backtrack
    if(!neighFound && neighPos==8){
      backtracked =true;
      //visitedArr={0};
      //visitedArr[currPos] = 1;
      result.pop_back();
      wordPos = wordPos-neighStr.size();
      //return zeroResult;
      if(result.empty()){
        return zeroResult;
      }
      currPos = result.back();
    }
    
    neighFound=0;
    //wordPos = wordPos+neighStr.size();
  }
  return result;
}*/


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

int BogglePlayer::getRow (int arrayPos) {
  currRow = arrayPos/totalCols;
  return currRow;
}

int BogglePlayer::getColumn (int arrayPos) {
  currCol = arrayPos%totalCols;
return currCol;
}


void BogglePlayer::getNeighbor(int arrayPos, int neighborArr []){
 // int neighborArr [8] = {0};
  getRow(arrayPos);
  getColumn(arrayPos);
  //neighbor 0
  if(currRow && currCol){
    neighborArr[0] = arrayPos - totalCols - 1;
  }
  //neighbor 1
  if(currRow) {
    neighborArr[1] = arrayPos - totalCols;    
  }
  //neighbor 2
  if(currRow && currCol != (totalCols-1)) {
    neighborArr[2] = arrayPos - totalCols + 1;    
  }
  //neighbor 3
  if(currCol) {
    neighborArr[3] = arrayPos - 1;    
  }
  //neighbor 4
  if(currCol != totalCols-1) {
    neighborArr[4] = arrayPos + 1;    
  }
  //neighbor 5
  if(currRow != totalRows-1 && currCol > 0) {
    neighborArr[5] = arrayPos + totalCols - 1;    
  }
  //neighbor 6
  if(currRow != totalRows-1) {
    neighborArr[6] = arrayPos + totalCols;    
  }
  //neighbor 7
  if(currRow != totalRows-1 && currCol != totalCols-1) {
    neighborArr[7] = arrayPos + totalCols + 1;    
  }
}

void BogglePlayer::deleteBogglePlayer(){
  if(boardArr){
    delete[] (boardArr);
    boardArr=0;
  }
}

void BogglePlayer::deleteNodes(boggleNode* node){
  if(node){
    for(int i=0;i<26;i++){
      if(node->a0[i]){
        deleteNodes(node->a0[i]);
        node->a0[i]=0;
      }
    }
    delete(node);
  }
}
