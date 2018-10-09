#ifndef SEQLINEARLIST_CPP
#define SEQLINEARLIST_CPP
#include "seqLinearList.hpp"
#include<iostream>


template<class Item>
LinearList<Item>::LinearList()
{
	MaxSize=100;
	element = new Item[MaxSize]();
	//new Item[MaxListSize](); initalizes the Array to zero.
}

template<class Item>
LinearList<Item>::LinearList(const int& MaxListSize)
{
	len=MaxListSize;
	MaxSize=100;
	element = new Item[MaxSize]();
	//for(int i=0;i<len;i++) element[i]=0;
}

template<class Item>
LinearList<Item>::~LinearList()
{
	delete[] element;
	len=0;
	//free() can be used but delete is an operator and therefore faster.
}

template<class Item>
Item& LinearList<Item>::operator[](const int& i)
{
	return *(element+i);
}

template<class Item>
bool LinearList<Item>::isEmpty()
{
	return !len;
}

template<class Item>
int LinearList<Item>::length()
{
	return len;
}

template<class Item>
int LinearList<Item>::maxSize()
{
	return MaxSize;
}

template<class Item>
Item LinearList<Item>::returnListElement(const int k)
{
	return element[k-1];
}

template<class Item>
bool LinearList<Item>::find(const int k, Item& x)
{
	if(k>len) return false;

	element[k-1]=x;
	return true;
}

template<class Item>
int LinearList<Item>::search(Item x)
{
	for(int i=0;i<len;i++)
	{
		if(element[i]==x) return i+1;
	}
	return 0;
}

template<class Item>
void LinearList<Item>::deleteElement(const int k, Item& x)
{
	if(!len||k>=len) return;

	x=element[k];
	for(int i=k;i<len-1;i++)
	{
		element[i]=element[i+1];
	}
	element[len-1]=0;
	len--;
}

template<class Item>
void LinearList<Item>::insert(const int k, Item& x)
{
	if(len==MaxSize)
	{
		cout<<"Cannot add, Max Size of List reached\n";
		return;
	}

	if(len==0)
	{
		element[0]=x;
		len++;
		return;
	}

	for(int i=len-1;i>k;i--) element[i+1]=element[i];
	element[k+1]=x;

	len++;
}
template<class Item>
void LinearList<Item>::push_back(Item &val)
{
	element[len]=val;
	len++;
}
#endif
