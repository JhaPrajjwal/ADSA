#ifndef RBTree_CPP_
#define RBTree_CPP_
#include "RBTree.hpp"
#include<iostream>
using namespace std;


template<typename Key,typename Value>
RBTNode<Key,Value> * RBTree<Key,Value>::new_node(const Key& key, const Value& value)
{
  RBTNode<Key,Value> *temp= new RBTNode<Key,Value>;
  temp->key=key;
  temp->val=value;
  temp->col=RED;
  temp->size=1;
  temp->height=1;
  temp->black_height=1;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

template<typename Key,typename Value>
Color RBTree<Key,Value>::getcolor(RBTNode<Key,Value>* node) { return node->col; }

template<typename Key,typename Value>
RBTNode<Key,Value>* RBTree<Key,Value>::getparent(RBTNode<Key,Value>* node) { return node->parent; }

template<typename Key,typename Value>
RBTNode<Key,Value>* RBTree<Key,Value>::getgrandparent(RBTNode<Key,Value>* node) { return node->parent->parent; }

template<typename Key,typename Value>
RBTNode<Key,Value>* RBTree<Key,Value>::get_sibling(RBTNode<Key,Value>* node)
{
  RBTNode<Key,Value>* temp=getparent(node);
  if(temp->left==node) return temp->right;
  else return temp->left;
}

template<typename Key,typename Value>
RBTNode<Key,Value>* RBTree<Key,Value>::get_parents_sibling(RBTNode<Key,Value>* node)
{
  RBTNode<Key,Value>* temp1=getparent(node);
  RBTNode<Key,Value>* temp2=getgrandparent(node);
  if(temp2->left==temp1) return temp2->right;
  else return temp2->left;
}

template<typename Key,typename Value>
RBTNode<Key,Value>* RBTree<Key,Value>::leftRotate(RBTNode<Key,Value>* node)
{
  RBTNode<Key,Value> *temp=node->right;
  RBTNode<Key,Value> *temp2=temp->left;
  RBTNode<Key,Value> *par=node->parent;
  int l=0;
  if(par!=NULL&&par->left==node) l++;

  node->parent=temp;
  temp->left=node;
  node->right=temp2;
  if(temp2!=NULL) temp2->parent=node;
  node->height=max(height(node->right),height(node->left))+1;
  temp->height=max(height(temp->right),height(temp->left))+1;
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
RBTNode<Key,Value>* RBTree<Key,Value>::rightRotate(RBTNode<Key,Value>* node)
{
  RBTNode<Key,Value> *temp=node->left;
  RBTNode<Key,Value> *temp2=temp->right;
  RBTNode<Key,Value> *par=node->parent;
  int l=0;
  if(par!=NULL&&par->left==node) l++;

  temp->right=node;
  node->parent=temp;
  node->left=temp2;
  if(temp2!=NULL) temp2->parent=node;
  node->height=max(height(node->right),height(node->left))+1;
  temp->height=max(height(temp->right),height(temp->left))+1;
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
void RBTree<Key,Value>::insertRBFixup(RBTNode<Key,Value> *node,const Key& key)
{
  while(getparent(node)!=NULL&&getgrandparent(node)!=NULL&&getcolor(getparent(node))==RED)
  {
    RBTNode<Key,Value> *p=getparent(node), *gp=getgrandparent(node), *sib=get_parents_sibling(node);
    if(gp->left==p)
    {
      if(sib!=NULL&&getcolor(sib)==RED)
      {
        p->col=sib->col=BLACK;
        gp->col=RED;
        gp->black_height+=1;
        node=gp;
      }
      else
      {
        if(p->right==node)
        {
          leftRotate(p);
          swap(node,p);
        }
        p->col=BLACK;
        gp->col=RED;
        rightRotate(gp);
        p->black_height+=1;
      }
    }
    else
    {
      if(sib!=NULL&&getcolor(sib)==RED)
      {
        p->col=sib->col=BLACK;
        gp->col=RED;
        gp->black_height+=1;
        node=gp;
      }
      else
      {
        if(p->left==node)
        {
          rightRotate(p);
          swap(node,p);
        }
        p->col=BLACK;
        gp->col=RED;
        leftRotate(gp);
        p->black_height+=1;
      }
    }
  }
  this->root->col=BLACK;
}

template<typename Key,typename Value>
void RBTree<Key,Value>::put(RBTNode<Key,Value> *root,const Key& key, const Value& value)
{
  if(this->root==NULL)
  {
    this->root=new_node(key,value);
    this->root->col=BLACK;
    return ;
  }

  if(root->key>=key)
  {
    if(root->left==NULL)
    {
      RBTNode<Key,Value> *temp=new_node(key,value);
      root->left=temp;
      temp->parent=root;
      insertRBFixup(temp,key);
      update_height(temp);
      return ;
    }
    else return put(root->left,key,value);
  }
  else
  {
    if(root->right==NULL)
    {
      RBTNode<Key,Value> *temp=new_node(key,value);
      root->right=temp;
      temp->parent=root;
      insertRBFixup(temp,key);
      update_height(temp);
      return ;
    }
    else return put(root->right,key,value);
  }
}

template<typename Key,typename Value>
void RBTree<Key,Value>::transplant(RBTNode<Key,Value>* u,RBTNode<Key,Value>* v)
{
  if(u->parent==NULL) this->root=v;
  else if(u==u->parent->left) u->parent->left=v;
  else u->parent->right=v;
  if(v!=NULL) v->parent=u->parent;
}

template<typename Key,typename Value>
void RBTree<Key,Value>::deleteRBFixup(RBTNode<Key,Value> *root)
{
  while(root!=NULL&&root!=this->root&&getcolor(root)==BLACK)
  {
    RBTNode<Key,Value> *w;
    if(root==root->parent->left)
    {
      w=root->parent->right;
      if(w!=NULL&&getcolor(w)==RED)
      {
        w->col=BLACK;
        root->parent->col=RED;
        leftRotate(root->parent);
        w=root->parent->right;
      }
      if(w!=NULL&&w->left!=NULL&&w->right!=NULL&&w->left->col==BLACK&&w->right->col==BLACK)
      {
        w->col=RED;
        root=root->parent;
      }
      else if(w!=NULL&&w->right!=NULL&&w->right->col==BLACK)
      {
        w->left->col=BLACK;
        w->col=RED;
        rightRotate(w);
        w=root->parent->right;
      }
      if(w!=NULL)
      {
        w->col=root->parent->col;
        root->parent->col=BLACK;
        if(w->right!=NULL) w->right->col=BLACK;
        leftRotate(root->parent);
      }
      root=this->root;
    }
    else
    {
      w=root->parent->left;
      if(w!=NULL&&getcolor(w)==RED)
      {
        w->col=BLACK;
        root->parent->col=RED;
        rightRotate(root->parent);
        w=root->parent->left;
      }
      if(w!=NULL&&w->left!=NULL&&w->right!=NULL&&w->right->col==BLACK&&w->left->col==BLACK)
      {
        w->col=RED;
        root=root->parent;
      }
      else if(w!=NULL&&w->left!=NULL&&w->left->col==BLACK)
      {
        w->right->col=BLACK;
        w->col=RED;
        leftRotate(w);
        w=root->parent->left;
      }
      w->col=root->parent->col;
      root->parent->col=BLACK;
      if(w->left!=NULL) w->left->col=BLACK;
      rightRotate(root->parent);
      root=this->root;
    }
  }
  this->root->col=BLACK;
}

template<typename Key,typename Value>
void RBTree<Key,Value>::remove(RBTNode<Key,Value>* root,const Key &key)
{
  int f=0;
  if(root==NULL) return ;
  if(root->key>key) remove(root->left,key);
  else if(root->key<key) remove(root->right,key);
  else
  {
    RBTNode<Key,Value>* temp=root;
    RBTNode<Key,Value>* x;
    Color deleted_node_col=temp->col;
    if(temp->left==NULL&&temp->right==NULL)
    {
      if(deleted_node_col==BLACK&&temp!=this->root)
      {
        RBTNode<Key,Value>* sib=get_sibling(temp);
        if(sib!=NULL&&getcolor(sib)==BLACK&&sib->left==NULL&&sib->right==NULL)
        {
          sib->col=RED;
          goto there;
        }
        deleteRBFixup(temp);
        if(root->parent!=NULL&&root->parent->col==RED) root->parent->col=BLACK;
      }
      there:
      x=NULL;
      transplant(root,x);
      delete temp;
    }
    else if(temp->left==NULL)
    {
      x=temp->right;
      transplant(root,x);
      delete temp;
      if(x!=NULL&&x->parent!=NULL&&getcolor(x)==RED&&getcolor(x->parent)==RED) x->col=BLACK;
      if(deleted_node_col==BLACK) deleteRBFixup(x);
    }
    else if(temp->right==NULL)
    {
      x=temp->left;
      transplant(root,x);
      if(x!=NULL&&x->parent!=NULL&&getcolor(x)==RED&&getcolor(x->parent)==RED) x->col=BLACK;
      if(deleted_node_col==BLACK) deleteRBFixup(x);
    }
    else
    {
      Key succ=successor(temp->key);
      temp=this->root;
      if(succ==Key()) succ=key;
      while(succ!=temp->key)
      {
        if(succ>temp->key) temp=temp->right;
        else temp=temp->left;
      }
      deleted_node_col=temp->col;
      //copy contents
      root->key=temp->key;
      root->val=temp->val;
      //case if equal keys
      if(temp==root)
      {
        x=root->right;
        if(temp->parent!=NULL) temp->parent->left=NULL;
        else
        {
          transplant(temp,x);
          x->left=temp->left;
        }

        if(deleted_node_col==BLACK) deleteRBFixup(x);
        delete temp;
      }
      // case 1 if right node is successor
      else if(temp->parent==root)
      {
        x=root;
        x->right=temp->right;
        if(temp->right!=NULL) temp->right->parent=x;
        if(deleted_node_col==BLACK) deleteRBFixup(x);
        delete temp;
      }
      // case 2
      else
      {
        x=root;
        if(temp->parent!=NULL) temp->parent->left=NULL;
        if(deleted_node_col==BLACK) deleteRBFixup(x);
        delete temp;
      }
      /*
      if(temp->parent==root) x->parent=temp;
      else
      {
        transplant(temp,temp->right);
        temp->right=root->right;
        temp->right->parent=temp;
      }
      transplant(root,temp);
      temp->left=root->left;
      temp->left->parent=temp;
      temp->col=root->col;
      if(deleted_node_col==BLACK) deleteRBFixup(x);
      delete temp;
      */
    }
  }
}

template<typename Key,typename Value>
void RBTree<Key,Value>::print_in_order(RBTNode<Key,Value> *root)
{
  if(root!=NULL)
  {
    if(root->left!=NULL) print_in_order(root->left);
    cout<<root->key<<":"<<root->val<<" ";
    if(root->right!=NULL) print_in_order(root->right);
  }
}

template<typename Key,typename Value>
void RBTree<Key,Value>::print_pre_order(RBTNode<Key,Value> *root)
{
  if(root!=NULL)
  {
    cout<<root->key<<":"<<root->val<<":col="<<root->col<<" ";
    if(root->left!=NULL) print_pre_order(root->left);
    if(root->right!=NULL) print_pre_order(root->right);
  }
}

template<typename Key,typename Value>
void RBTree<Key,Value>::print_post_order(RBTNode<Key,Value> *root)
{
  if(root!=NULL)
  {
    if(root->left!=NULL) print_post_order(root->left);
    if(root->right!=NULL) print_post_order(root->right);
    cout<<root->key<<":"<<root->val<<" ";
  }
}

template<typename Key,typename Value>
bool RBTree<Key,Value>::has(const Key& key)
{
  RBTNode<Key,Value> *t=(this->root);
  while(t!=NULL)
  {
    if(t->key==key) return true;
    else if(t->key>key) t=t->left;
    else t=t->right;
  }
  return false;
}

template<typename Key,typename Value>
Value RBTree<Key,Value>::get(const Key& key)
{
  RBTNode<Key,Value> *t=(this->root);
  while(t!=NULL)
  {
    if(t->key==key) return t->val;
    else if(t->key>key) t=t->left;
    else t=t->right;
  }
  return Value();
}

template<typename Key,typename Value>
Key RBTree<Key,Value>::minimum(RBTNode<Key,Value> * node)
{
  RBTNode<Key,Value> *t=node;
  while(t->left!=NULL) t=t->left;
  return t->key;
}

template<typename Key,typename Value>
Key RBTree<Key,Value>::maximum(RBTNode<Key,Value> * node)
{
  RBTNode<Key,Value> *t=node;
  while(t->right!=NULL) t=t->right;
  return t->key;
}

template<typename Key,typename Value>
Key RBTree<Key,Value>::successor(const Key& key)
{
  RBTNode<Key,Value> *t=(this->root),*node;
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
    RBTNode<Key,Value> *temp=node->parent;
    while(temp!=NULL&&node==temp->right)
    {
      node=temp;
      temp=temp->parent;
    }
    return temp->key;
  }
}

template<typename Key,typename Value>
Key RBTree<Key,Value>::predecessor(const Key& key)
{
  RBTNode<Key,Value> *t=(this->root),*node;
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
    RBTNode<Key,Value> *temp=node->parent;
    while(temp!=NULL&&node==temp->left)
    {
      node=temp;
      temp=temp->parent;
    }
    return temp->key;
  }
}

template<typename Key,typename Value>
void RBTree<Key,Value>::update_height(RBTNode<Key,Value>* node)
{
  while(node!=NULL)
  {
    node->height=1+max(height(node->right),height(node->left));
    node=node->parent;
  }
}


#endif
