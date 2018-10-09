#ifndef AVL_HPP
#define AVL_HPP 1
#include "BSTree.hpp"
template <typename Key,typename Value>
class AVL : public BSTree<Key, Value>{

 private:
  /*
   * Inherit as much functionality as possible from the BSTree class.
   * Then provide custom AVL Tree functionality on top of that.
   * The AVL Tree should make use of as many BST functions as possible.
   * Override only those methods which are extremely necessary.
   */
  /*
   * Apart from that, your code should have the following four functions:
   * getBalance(node) -> To get the balance at any given node;
   * doBalance(node) -> To fix the balance at the given node;
   * rightRotate(node) -> Perform a right rotation about the given node.
   * leftRotate(node) -> Perform a left rotation about the given node.
   *
   * The signature of these functions are not provided in order to provide you
   * some flexibility in how you implement the internals of your AVL Tree. But
   * make sure these functions are there.
   */
 public:
   AVL() { this->root=NULL; }

   virtual int height(BinaryNode<Key,Value>* node);// height of any subtree

   BinaryNode<Key,Value>* rightRotate(BinaryNode<Key,Value>* node);

   BinaryNode<Key,Value>* leftRotate(BinaryNode<Key,Value>* node);

   int getBalance(BinaryNode<Key,Value>* node);

   BinaryNode<Key,Value>* doBalance(BinaryNode<Key,Value>* node,const Key& key);

   void update_height(BinaryNode<Key,Value>* node);

   virtual void put(const Key& key, const Value& value) { int ans=pututil(key,value); }

   int pututil(const Key& key, const Value& value);

   void remove(const Key& key);

   int size() { return size(this->root); }

   int size(BinaryNode<Key,Value>* node);
};

#endif /* ifndef AVL_HPP */
#include "AVL.cpp"
