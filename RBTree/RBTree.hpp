#ifndef RBTree_HPP_
#define RBTree_HPP_ 1
#include "BSTree.hpp"
/* The color enumeration.
 * Please use this and not integers or characters to store the color of the node
 * in your red black tree.
 * Also create a class RBTNode which should inherit from BinaryNode and has the attribute color in it.
 */
enum Color { RED, BLACK };

template<typename Key,typename Value>
class RBTNode: public BinaryNode<Key,Value>{
	public:
		Color col;
		int black_height;
		RBTNode<Key,Value> *left,*right,*parent;
		RBTNode()
		{
			col=BLACK;
      black_height=0;
			left=NULL;
			right=NULL;
			parent=NULL;
		}
};

template <class Key, class Value>
class RBTree : public BSTree<Key, Value> {

	void insertRBFixup(RBTNode<Key,Value> *root,const Key& key);

	void deleteRBFixup(RBTNode<Key,Value> *root);

	protected:
		RBTNode<Key,Value> *root;

	public:
		RBTree() { this->root=NULL; }

		RBTNode<Key,Value>* get_root() { return this->root; }

		RBTNode<Key,Value>* new_node(const Key &key,const Value &value);

		Color getcolor(RBTNode<Key,Value>* node);

		RBTNode<Key,Value>* getparent(RBTNode<Key,Value>* node);

		RBTNode<Key,Value>* getgrandparent(RBTNode<Key,Value>* node);

		RBTNode<Key,Value>* get_sibling(RBTNode<Key,Value>* node);

		RBTNode<Key,Value>* get_parents_sibling(RBTNode<Key,Value>* node);

		RBTNode<Key,Value>* rightRotate(RBTNode<Key,Value>* node);

    RBTNode<Key,Value>* leftRotate(RBTNode<Key,Value>* node);

		void put(RBTNode<Key,Value>* root,const Key &key,const Value &val);

		void transplant(RBTNode<Key,Value>* u,RBTNode<Key,Value>* v);

		void remove(RBTNode<Key,Value>* root,const Key &key);

		void print_in_order(RBTNode<Key,Value> *root);

	  void print_pre_order(RBTNode<Key,Value> *root);

		void print_post_order(RBTNode<Key,Value> *root);

		bool has(const Key& key);

	  Value get(const Key& key);

    Key minimum(RBTNode<Key,Value> *node);

    Key maximum(RBTNode<Key,Value> *node);

    Key successor(const Key& key);

    Key predecessor(const Key& key);

		int blackHeight(RBTNode<Key,Value> *node);// not done

		void update_height(RBTNode<Key,Value>* node);

		int height(RBTNode<Key,Value> *node) { return node==NULL?0:node->height; }

};
#endif
#include "RBTree.cpp"
