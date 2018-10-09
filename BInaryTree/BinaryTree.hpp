#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP 1
#include "queue.hpp"
template<typename Key,typename Value>
class BinaryNode
{
  public:
		Key key;
		Value val;
    int height;
    int size;
		BinaryNode<Key,Value> *left,*right,*parent;
    /*Default constructor. Should assign the default value to key and value
    */
		BinaryNode()
		{
      height=0;
			left=NULL;
			right=NULL;
			parent=NULL;
		}
	  /*This contructor should assign the key and val from the passed parameters
    */
		BinaryNode(Key key, Value value)
		{
      height=0;
			(this)->key = key;
			(this)->val = value;
			left=NULL;
			right=NULL;
			parent=NULL;
		}
};

template<typename Key,typename Value>
class BinaryTree
{

  protected:
		BinaryNode<Key,Value> *root;

  public:

  BinaryTree() { root=NULL; }

  virtual void remove(const Key& key);

  virtual bool has(const Key& key) ;

  BinaryNode<Key,Value> *get_root() { return (this)->root; }

  Value get(const Key& key);//return default value of data type if not found

  virtual void put(const Key& key, const Value& value);

  virtual void print_in_order() { return print_in_order(root); }

  virtual void print_in_order(const BinaryNode<Key,Value> *root);//helper

  virtual void print_pre_order() { return print_pre_order(root); }

  virtual void print_pre_order(const BinaryNode<Key,Value> *root);//helper

  virtual void print_post_order() { return print_post_order(root); }

  virtual void print_post_order(const BinaryNode<Key,Value> *root);//helper

  virtual Key minimum();

  virtual Key maximum();

  virtual Key successor(const Key& key);

  virtual Key predecessor(const Key& key);

};

#endif /* ifndef BINARYTREE_HPP */
#include "BinaryTree.cpp"
