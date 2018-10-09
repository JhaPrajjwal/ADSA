#ifndef BinaryTree_CPP
#define BinaryTree_CPP
#include "BinaryTree.hpp"
#include "queue.hpp"
#include<iostream>
using namespace std;

template<typename Key,typename Value>
void BinaryTree<Key,Value>::put(const Key& key, const Value& value)
{
  BinaryNode<Key,Value> *temp=new BinaryNode<Key,Value>;
  temp->key=key;
  temp->val=value;
  temp->left=NULL;
  temp->right=NULL;

  if((this)->root==NULL)
  {
    (this)->root=temp;
    temp->parent=NULL;
    return;
  }

  queue< BinaryNode<Key,Value> *> q;
  BinaryNode<Key,Value> *t=(this)->root;
  q.push(t);
  while(!q.isempty())
  {
    t=q.top();
    q.pop();
    if(t->left==NULL)
    {
      t->left=temp;
      temp->parent=t;
      break;
    }
    else q.push(t->left);

    if(t->right==NULL)
    {
      t->right=temp;
      temp->parent=t;
      break;
    }
    else q.push(t->right);
  }
}

template<typename Key,typename Value>
void BinaryTree<Key,Value>::print_in_order(const BinaryNode<Key,Value> *root)
{
  if(root!=NULL)
  {
    if(root->left!=NULL) print_in_order(root->left);
    cout<<root->key<<":"<<root->val<<" ";
    if(root->right!=NULL) print_in_order(root->right);
  }
}

template<typename Key,typename Value>
void BinaryTree<Key,Value>::print_pre_order(const BinaryNode<Key,Value> *root)
{
  if(root!=NULL)
  {
    cout<<root->key<<":"<<root->val<<" ";
    if(root->left!=NULL) print_pre_order(root->left);
    if(root->right!=NULL) print_pre_order(root->right);
  }
}

template<typename Key,typename Value>
void BinaryTree<Key,Value>::print_post_order(const BinaryNode<Key,Value> *root)
{
  if(root!=NULL)
  {
    if(root->left!=NULL) print_post_order(root->left);
    if(root->right!=NULL) print_post_order(root->right);
    cout<<root->key<<":"<<root->val<<" ";
  }
}

template<typename Key,typename Value>
Value BinaryTree<Key,Value>::get(const Key& key)
{
  BinaryNode<Key,Value> *temp=(this)->root;
  queue< BinaryNode<Key,Value>* > q;
  q.push(temp);
  int f=0;
  Value ans=Value();

  while(!q.isempty())
  {
    temp=q.top();
    q.pop();
    if(temp->key==key)
    {
      ans = temp->val;
      f++;
      break;
    }
    if(temp->left!=NULL) q.push(temp->left);
    if(temp->right!=NULL) q.push(temp->right);
  }

  if(!f) cout<<"Key Not Found"<<endl;
  return ans;
}

template<typename Key,typename Value>
bool BinaryTree<Key,Value>::has(const Key& key)
{
  BinaryNode<Key,Value> *temp=(this)->root;
  queue< BinaryNode<Key,Value> *> q;
  q.push(temp);

  while(!q.isempty())
  {
    temp=q.top();
    q.pop();
    if(temp->key==key) return true;
    if(temp->left!=NULL) q.push(temp->left);
    if(temp->right!=NULL) q.push(temp->right);
  }

  return false;
}

template<typename Key,typename Value>
Key BinaryTree<Key,Value>::minimum()
{
  BinaryNode<Key,Value> *temp=(this)->root;
  queue< BinaryNode<Key,Value>* > q;
  q.push(temp);
  Key ans=temp->key;
  Value min=temp->val;
  while(!q.isempty())
  {
    temp=q.top();
    q.pop();
    if(temp->val<min){ min=temp->val; ans=temp->key; }
    if(temp->left!=NULL) q.push(temp->left);
    if(temp->right!=NULL) q.push(temp->right);
  }
  return ans;
}

template<typename Key,typename Value>
Key BinaryTree<Key,Value>::maximum()
{
  BinaryNode<Key,Value> *temp=(this)->root;
  queue< BinaryNode<Key,Value> *> q;
  q.push(temp);
  Key ans=temp->key;
  Value max=temp->val;
  while(!q.isempty())
  {
    temp=q.top();
    q.pop();
    if(temp->val>max) { max=temp->val; ans=temp->key; }
    if(temp->left!=NULL) q.push(temp->left);
    if(temp->right!=NULL) q.push(temp->right);
  }
  return ans;
}

template<typename Key,typename Value>
void BinaryTree<Key,Value>::remove(const Key& key)
{
  BinaryNode<Key,Value> *ROOT=(this)->root;
  BinaryNode<Key,Value> *temp=ROOT;
  queue< BinaryNode<Key,Value> *> q;
  q.push(temp);
  BinaryNode<Key,Value> *hold;
  int f=0;
  while(!q.isempty())
  {
    temp=q.top();
    q.pop();
    if(temp->key==key)
    {
      hold=temp;
      f++;
    }
    if(temp->left!=NULL) q.push(temp->left);
    if(temp->right!=NULL) q.push(temp->right);
  }
  if(!f) cout<<"Key Not Found\n";
  else if(hold==ROOT&&temp==ROOT)
  {
    delete hold;
    (this)->root=NULL;
  }
  else
  {
    hold->val=temp->val;   //temp now is the lowest rightmost BinaryNode
    hold->key=temp->key;
    if((temp->parent)->right==temp) (temp->parent)->right=NULL;
    else (temp->parent)->left=NULL;
    delete temp;
  }
}

template<typename Key,typename Value>
Key BinaryTree<Key,Value>::successor(const Key& key)
{
  BinaryNode<Key,Value> *temp=(this)->root;
  queue< BinaryNode<Key,Value>* > q;
  q.push(temp);
  Key ans=Key();
  while(!q.isempty())
  {
    temp=q.top();
    q.pop();
    if(temp->key>key&&ans==Key()) ans=temp->key;
    else if(temp->key>key&&ans>temp->key) ans=temp->key;
    if(temp->left!=NULL) q.push(temp->left);
    if(temp->right!=NULL) q.push(temp->right);
  }
  return ans;
}

template<typename Key,typename Value>
Key BinaryTree<Key,Value>::predecessor(const Key& key)
{
  BinaryNode<Key,Value> *temp=(this)->root;
  queue< BinaryNode<Key,Value>* > q;
  q.push(temp);
  Key ans=Key();
  while(!q.isempty())
  {
    temp=q.top();
    q.pop();
    if(temp->key<key&&ans==Key()) ans=temp->key;
    else if(temp->key<key&&ans<temp->key) ans=temp->key;
    if(temp->left!=NULL) q.push(temp->left);
    if(temp->right!=NULL) q.push(temp->right);
  }
  return ans;
}

#endif
