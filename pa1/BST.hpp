#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    clear();    
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  virtual bool insert(const Data& item) {
    BSTNode<Data>* temp= new BSTNode<Data>(item);    
    BSTNode<Data>* temp2= root;
    if(!isize){
      root = temp;
      isize++;
      return true;
    }
    while(temp2->left || temp2->right){
      if(temp2->data < item){
        if(!temp2->right) {
          break;
        }
        temp2= temp2->right;
      }
      else if(item < temp2->data) {
        if(!temp2->left) {
          break;
        }
        temp2=temp2->left;
      }
      else {
        break;
      }
    }
    if(temp2->data < item){
      temp2->right=temp;
      temp->parent = temp2;
      isize++;
      return true;
    }
    if(item < temp2->data) {
      temp2->left=temp;
      temp->parent = temp2;
      isize++;
      return true;
    } 
    return false;
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  iterator find(const Data& item) const {
    BSTNode<Data>* temp2= root;
    if(!isize){
      return end();
    }
    while(temp2->left || temp2->right){
      if(temp2->data < item){
        if(!temp2->right) {
          break;
        }
        temp2= temp2->right;
      }
      else if(item < temp2->data) {
        if(!temp2->left) {
          break;
        }
        temp2=temp2->left;
      }
      else {
        break;
      }
    }

    if(temp2-> data < item || item < temp2->data) {
      return end(); 
    } 
    
    else {
      return iterator(temp2);
    }

  }


  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    if (isize) {
      return false;
    }

    return true;
  }

  /** Empties the Tree
   */ // TODO
  bool clear(){
    if(!root){
      return false;
    }
    deleteAll(root);
    isize=0;
    root=0;
    return true;
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ // TODO
  iterator begin() const {
    BSTNode<Data>* temp= root;
    if(!root){
      return iterator(0);
    }
    while(temp->left){
      temp=temp->left;
    }
    return iterator(temp);
   }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
   */ // TODO
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
    
    if(!n) {
      return;
    }
    if(!(n->left) && !(n->right)){
      if(n->parent->left==n){
        std::cout << *n << std::endl;
      	return;
      }
      if(n->parent->right==n){
        std::cout << *n << std::endl;
        return;
         
      }
    }
    if(n->left){
      inorder(n->left);
    }
    std::cout << *n << std::endl;

    if(n->right){
      inorder(n->right);
    }
    
    
    
  }

  /** Find the first element of the BST
   */
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** do a postorder traversal, deleting nodes
   */ // TODO
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */
    if(!n){
      return;
    }
    if(n->left){
      deleteAll(n->left);      
    }
    if(n->right){
      deleteAll(n->right);
    }
    delete n;
    n=0;
  }
};


#endif //BST_HPP
