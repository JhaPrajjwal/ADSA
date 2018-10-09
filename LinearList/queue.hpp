#ifndef QUEUE
#define QUEUE
#include<iostream>
template<class Item>
class queue
{
  private:
    struct node
    {
      Item val;
      node *next;
    };
    node *head,*tail;
  public:
    queue()
    {
      head=NULL;
      tail=NULL;
    }

    bool isempty()
    {
      if(head==NULL) return true;
      return false;
    }

    void push(const Item &k)
    {
      node *temp=new node;
      temp->val=k;
      temp->next=NULL;

      if(head==NULL)
      {
        head=temp;
        tail=temp;
      }
      else
      {
        tail->next=temp;
        tail=temp;
      }
    }

    Item top()
    {
      return head->val;
    }

    void pop()
    {
      node *temp=head;

      if(head==NULL) return;
      else if(head==tail)
      {
        head=NULL;
        tail=NULL;
        delete temp;
      }
      else
      {
        head=head->next;
        delete temp;
      }
    }
};

#endif
