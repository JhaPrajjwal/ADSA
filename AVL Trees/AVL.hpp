#ifndef AVL_HPP
#define AVL_HPP 1
#include "BSTree.hpp"
template <typename Key,typename Value>
class AVL : public BSTree<Key, Value>{

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
