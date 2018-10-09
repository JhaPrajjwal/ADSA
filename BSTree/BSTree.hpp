#ifndef BSTREE_HPP
#define BSTREE_HPP 1
#include "BinaryTree.hpp"

template<typename Key,typename Value>
class BSTree : public BinaryTree<Key,Value>{
  private:
    int count=0;
 public:
   BSTree() { this->root=NULL; }

   virtual void put(const Key& key, const Value& value);

   Value get(const Key& key);

   virtual bool has(const Key& key) ;

   virtual Key minimum() { return minimum(this->root); }

   virtual Key minimum(BinaryNode<Key,Value> *node);//helper function

   virtual Key maximum() { return maximum(this->root); }

   virtual Key maximum(BinaryNode<Key,Value> *node); //helper function

   virtual Key successor(const Key& key);

   virtual Key predecessor(const Key& key);

   void remove(const Key& key);

   virtual void print();//print in sorted order

   virtual int size() { return this->count; }

   virtual int getHeight() { return getHeight(this->get_root()); }

   virtual int getHeight(BinaryNode<Key,Value> *root);//helper
};

#endif /* ifndef BSTREE_HPP */
#include "BSTree.cpp"
