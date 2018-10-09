#ifndef AVL_CPP
#define AVL_CPP
#include "BSTree.hpp"
#include "AVL.hpp"
#include<iostream>
#define inf 10000000

template<typename Key,typename Value>
int AVL<Key,Value>::size(BinaryNode<Key,Value> *root)
{
  if(root==NULL) return 0;
  return root->size;
}

template<typename Key,typename Value>
int AVL<Key,Value>::height(BinaryNode<Key,Value>* node)
{
  if(node==NULL) return 0;
  else return node->height;
}

template<typename Key,typename Value>
void AVL<Key,Value>::update_height(BinaryNode<Key,Value>* node)
{
  while(node!=NULL)
  {
    node->height=1+max(height(node->right),height(node->left));
    node=node->parent;
  }
}

template<typename Key,typename Value>
BinaryNode<Key,Value>* AVL<Key,Value>::rightRotate(BinaryNode<Key,Value>* node)
{
  BinaryNode<Key,Value> *temp=node->left;
  BinaryNode<Key,Value> *temp2=temp->right;
  BinaryNode<Key,Value> *par=node->parent;
  int l=0;
  if(par!=NULL&&par->left==node) l++;

  temp->right=node;
  node->parent=temp;
  node->left=temp2;
  if(temp2!=NULL) temp2->parent=node;
  node->height=max(height(node->right),height(node->left))+1;
  temp->height=max(height(temp->right),height(temp->left))+1;
  node->size=size(node->right)+size(node->left)+1;
  temp->size=size(temp->right)+size(temp->left)+1;
  //temp->parent->size=size(temp->parent->right)+size(temp->parent->left)+1;
  //cout<<"RR "<<node->key<<":"<<node->size<<" "<<temp->key<<":"<<temp->size<<endl;
  if(par==NULL)
  {
    this->root=temp;
    temp->parent=NULL;
  }
  else if(l)
  {
    par->left=temp;
    temp->parent=par;
  }
  else
  {
    par->right=temp;
    temp->parent=par;
  }

  return temp;
}

template<typename Key,typename Value>
BinaryNode<Key,Value>* AVL<Key,Value>::leftRotate(BinaryNode<Key,Value>* node)
{
  BinaryNode<Key,Value> *temp=node->right;
  BinaryNode<Key,Value> *temp2=temp->left;
  BinaryNode<Key,Value> *par=node->parent;
  int l=0;
  if(par!=NULL&&par->left==node) l++;

  node->parent=temp;
  temp->left=node;
  node->right=temp2;
  if(temp2!=NULL) temp2->parent=node;
  node->height=max(height(node->right),height(node->left))+1;
  temp->height=max(height(temp->right),height(temp->left))+1;
  node->size=size(node->right)+size(node->left)+1;
  temp->size=size(temp->right)+size(temp->left)+1;
  //temp->parent->size=size(temp->parent->right)+size(temp->parent->left)+1;
  //cout<<"LR "<<node->key<<":"<<node->size<<" "<<temp->key<<":"<<temp->size<<endl;
  if(par==NULL)
  {
    this->root=temp;
    temp->parent=NULL;
  }
  else if(l)
  {
    par->left=temp;
    temp->parent=par;
  }
  else
  {
    par->right=temp;
    temp->parent=par;
  }

  return temp;
}

template<typename Key,typename Value>
int AVL<Key,Value>::getBalance(BinaryNode<Key,Value>* node)
{
    if(node==NULL) return 0;
    return height(node->left)-height(node->right);
}

template<typename Key,typename Value>
BinaryNode<Key,Value>* AVL<Key,Value>::doBalance(BinaryNode<Key,Value>* node,const Key& key)
{
  while(node!=NULL)
  {
    int fac=getBalance(node);
    if(fac>1 && key<(node->left)->key) rightRotate(node);//left left
    else if(fac>1 && key>(node->left)->key)// left right
    {
      leftRotate(node->left);
      rightRotate(node);
    }
    else if(fac<-1 && key>(node->right)->key) leftRotate(node);// right right
    else if(fac<-1 && key<(node->right)->key)// right left
    {
      rightRotate(node->right);
      leftRotate(node);
    }
    node=node->parent;
    update_height(node);
  }
}

template<typename Key,typename Value>
int AVL<Key,Value>::pututil(const Key& key, const Value& value)
{
  int ans=0;
  BinaryNode<Key,Value> *temp=new BinaryNode<Key,Value>;
  temp->key=key;
  temp->val=value;
  temp->height=1;
  temp->size=1;
  temp->left=NULL;
  temp->right=NULL;
  temp->parent=NULL;

  if((this->root)==NULL)
  {
    (this->root)=temp;
    return ans;
  }

  BinaryNode<Key,Value> *t=(this->root);
  while(1)
  {
    if(t->key>=key)
    {
      t->size++;
      if(t->left==NULL)
      {
        t->left=temp;
        temp->parent=t;
        break;
      }
      else t=t->left;
    }
    else
    {
      ans+=1+size(t->left);
      t->size++;
      if(t->right==NULL)
      {
        t->right=temp;
        temp->parent=t;
        break;
      }
      else t=t->right;
    }
  }
  update_height(t);
  doBalance(t,key);
  return ans;
}


template<typename Key,typename Value>
void AVL<Key,Value>::remove(const Key& key)
{
  BinaryNode<Key,Value> *temp=(this->root),*t;// t will hold the parent corresponding to the deleted key
  if((this->root)==NULL) return;

  while(temp!=NULL)
  {
    temp->size--;
    if(key<temp->key) temp=temp->left;
    else if(key>temp->key) temp=temp->right;
    else
    {
      if(temp->left==NULL)
      {
        if(temp->right==NULL)
        {
          BinaryNode<Key,Value> *par=temp->parent;
          if(par==NULL)// only 1 node remains
          {
            (this)->root=NULL;
            delete temp;
            return;
          }
          if(par->right==NULL) par->left=NULL;
          else if((par->right)->key==key) par->right=NULL;
          else par->left=NULL;
          t=temp->parent;
          delete temp;
          break;
        }
        else
        {
          temp->key=(temp->right)->key;
          temp->val=(temp->right)->val;
          t=temp;
          delete temp->right;
          temp->right=NULL;
          break;
          //cout<<temp->key<<":"<<temp->size<<"hello1"<<endl;
        }
      }
      else if(temp->right==NULL)
      {
        if(temp->left==NULL)
        {
          BinaryNode<Key,Value> *par=temp->parent;
          if(par->right==NULL) par->left=NULL;
          else if((par->right)->key==key) par->right=NULL;
          else par->left=NULL;
          t=temp->parent;
          delete temp;
          break;
        }
        else
        {
          temp->key=(temp->left)->key;
          temp->val=(temp->left)->val;
          temp->size=1;
          delete temp->left;
          t=temp;
          temp->left=NULL;
          break;
        }
      }
      else// 2 children
      {
        int f=0;
        BinaryNode<Key,Value> *succ=temp->right;
        succ->size--;
        if(succ->left==NULL) f++;//if it is a leaf node
        while(succ->left!=NULL)
        {
          succ=succ->left;
          succ->size--;
        }
        temp->key=succ->key;
        temp->val=succ->val;
        t=succ->parent;
        if(!f) succ->parent->left=NULL;
        else succ->parent->right=NULL;
        delete succ;
        break;
      }
    }
  }
  update_height(t);
  doBalance(t,key);
}

#endif
