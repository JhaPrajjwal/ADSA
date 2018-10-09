#ifndef BSTree_CPP
#define BSTree_CPP
#include "BSTree.hpp"
#include<iostream>
using namespace std;

template<typename Key,typename Value>
void BSTree<Key,Value>::put(const Key& key, const Value& value)
{
  BinaryNode<Key,Value> *temp=new BinaryNode<Key,Value>;
  temp->key=key;
  temp->val=value;
  temp->left=NULL;
  temp->right=NULL;
  temp->parent=NULL;

  if((this->root)==NULL)
  {
    (this->root)=temp;
    count++;
    return;
  }

  BinaryNode<Key,Value> *t=(this->root);
  while(1)
  {
    if(t->key>=key)
    {
      if(t->left==NULL)
      {
        t->left=temp;
        temp->parent=t;
        count++;
        break;
      }
      else t=t->left;
    }
    else
    {
      if(t->right==NULL)
      {
        t->right=temp;
        temp->parent=t;
        count++;
        break;
      }
      else t=t->right;
    }
  }
}

template<typename Key,typename Value>
void BSTree<Key,Value>::print()
{
  this->print_pre_order((this->root));
  cout<<endl;
}


template<typename Key,typename Value>
Value BSTree<Key,Value>::get(const Key& key)
{
  BinaryNode<Key,Value> *t=(this->root);
  while(t!=NULL)
  {
    if(t->key==key) return t->val;
    else if(t->key>key) t=t->left;
    else t=t->right;
  }
  return Value();
}

template<typename Key,typename Value>
bool BSTree<Key,Value>::has(const Key& key)
{
  BinaryNode<Key,Value> *t=(this->root);
  while(t!=NULL)
  {
    if(t->key==key) return true;
    else if(t->key>key) t=t->left;
    else t=t->right;
  }
  return false;
}


template<typename Key,typename Value>
Key BSTree<Key,Value>::minimum(BinaryNode<Key,Value> * node)
{
  BinaryNode<Key,Value> *t=node;
  while(t->left!=NULL) t=t->left;
  return t->key;
}

template<typename Key,typename Value>
Key BSTree<Key,Value>::maximum(BinaryNode<Key,Value> * node)
{
  BinaryNode<Key,Value> *t=node;
  while(t->right!=NULL) t=t->right;
  return t->key;
}

template<typename Key,typename Value>
Key BSTree<Key,Value>::successor(const Key& key)
{
  BinaryNode<Key,Value> *t=(this->root),*node;
  while(t!=NULL)
  {
    if(t->key==key) { node=t; break; }
    else if(t->key>key) t=t->left;
    else t=t->right;
  }
  if(t==NULL) return Key();
  else if(key==this->maximum((this->root))) return Key();
  else if(node->right!=NULL) return this->minimum(node->right);
  else
  {
    BinaryNode<Key,Value> *temp=node->parent;
    while(temp!=NULL&&node==temp->right)
    {
      node=temp;
      temp=temp->parent;
    }
    if(temp->key==key) return Key();
    return temp->key;
  }
}

template<typename Key,typename Value>
Key BSTree<Key,Value>::predecessor(const Key& key)
{
  BinaryNode<Key,Value> *t=(this->root),*node;
  while(t!=NULL)
  {
    if(t->key==key) { node=t; break; }
    else if(t->key>key) t=t->left;
    else t=t->right;
  }
  if(t==NULL) return Key();
  else if(key==this->minimum((this->root))) return Key();
  else if(node->left!=NULL) return this->maximum(node->left);
  else
  {
    BinaryNode<Key,Value> *temp=node->parent;
    while(temp!=NULL&&node==temp->left)
    {
      node=temp;
      temp=temp->parent;
    }
    return temp->key;
  }
}

template<typename Key,typename Value>
void BSTree<Key,Value>::remove(const Key& key)
{
  BinaryNode<Key,Value> *temp=(this->root);
  if((this->root)==NULL) return;

  while(temp!=NULL)
  {
    if(key<temp->key) temp=temp->left;
    else if(key>temp->key) temp=temp->right;
    else
    {
      //cout<<temp->key<<endl;
      count--;
      if(temp->left==NULL)
      {
        BinaryNode<Key,Value> *par=temp->parent;
        if(par==NULL)// only 1 node remains
        {
          if(temp->right==NULL) (this)->root=NULL;
          else
          {
            (this)->root=temp->right;
            temp->right->parent=NULL;
          }
          delete temp;
          return;
        }
        else if(temp->right==NULL)
        {
          if(par->right==temp) par->right=NULL;
          else par->left=NULL;
          delete temp;
          return ;
        }
        else
        {
          if(par->right==temp) par->right=temp->right;
          else par->right=temp->right;
          temp->right->parent=temp->parent;
          delete temp;
          return;
        }
      }
      else if(temp->right==NULL)
      {
        BinaryNode<Key,Value> *par=temp->parent;
        if(par==NULL)// only 1 node remains
        {
          if(temp->left==NULL) this->root=NULL;
          else
          {
            (this)->root=temp->left;
            temp->left->parent=NULL;
          }
          delete temp;
          return;
        }
        else if(temp->left==NULL)
        {
          if(par->right==temp) par->right=NULL;
          else par->left=NULL;
          delete temp;
          return ;
        }
        else
        {
          if(par->right==temp) par->right=temp->left;
          else par->left=temp->left;
          temp->left->parent=temp->parent;
          delete temp;
          return;
        }
      }
      else
      {
        BinaryNode<Key,Value> *succ=temp->right;
        while(succ->left!=NULL) succ=succ->left;
        temp->key=succ->key;
        temp->val=succ->val;
        if(succ->parent->right==succ) succ->parent->right=NULL;
        else succ->parent->left=NULL;
        delete succ;
        return;
      }
    }
  }
}

template<typename Key,typename Value>
int BSTree<Key,Value>::getHeight(BinaryNode<Key,Value> *root)
{
  if(root==NULL) return 0;
  return max(getHeight(root->left),getHeight(root->right))+1;
}

#endif
