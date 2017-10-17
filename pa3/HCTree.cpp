#include "HCTree.hpp"
#include <algorithm>

using namespace std;

void HCTree::build(const vector<int>& freqs) {
  std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq;
  for(int i=0; i<freqs.size(); i++) {
    if(freqs[i] > 0) {
      HCNode* a = new HCNode(freqs[i], (byte)i, 0, 0, 0);
      pq.push(a);
      leaves[i] = a;
    }
  }
   
  while(pq.size() > 1) {
    HCNode* temp = pq.top();
    pq.pop();  
    HCNode* temp2 = pq.top();
    HCNode* parent = new HCNode(temp->count + temp2->count, temp->symbol, temp, temp2, 0);
    temp->p = parent;
    temp2->p = parent;
    pq.pop();
    pq.push(parent);
  }
  
  int lol = 0;
  for(int i = 0; i < freqs.size(); i++) {
    lol += freqs[i];
  }
  if(lol == 0){
    return;
  }
  root = pq.top();
  pq.pop();
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
  /*if(!symbol){
    return;
  }*/
  HCNode* temp = leaves[symbol];
  //char a[BUFSIZ];
  vector<int> a; 
  //int i=0;
  /*if(!temp){
    return;
  }*/
  while(temp->p){
    if(temp->p->c0==temp){
      a.push_back(0);
    } 
    else {
      a.push_back(1);
    }
    //i++;
    temp = temp->p;
  }

  reverse(a.begin(), a.end());
  for(int i = 0; i < a.size(); i++) {
	out.writeBit(a[i]);
  }
 // std::cout << "encoded char: ";   
 // for(int j=i; j>=0; j--) {
 //   out.writeBit(a[j]); 
  //  std::cout << a[j] << endl;
  //}
  //std::cout << std::endl;
}

/*void HCTree::encode(byte symbol, ofstream& out) const {

}*/

int HCTree::decode(BitInputStream& in) const {
  HCNode * temp= root;
  while(temp->c0 || temp->c1){
    if(in.readBit()){
      temp = temp->c1;
    }
    else {
      temp = temp->c0;
    }
  }
  return temp->symbol;  
}

/*int HCTree::decode(ifstream& in) const {
  return 0;
}*/

void deleteAll(HCNode* n) {
  if (n == 0) {
    return;
  } 
  deleteAll(n->c0);
  deleteAll(n->c1);
  delete n;
}

HCTree::~HCTree(){
  deleteAll(root);
}
