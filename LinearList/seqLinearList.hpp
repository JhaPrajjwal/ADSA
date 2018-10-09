#ifndef SEQLINEARLIST_HPP
#define SEQLINEARLIST_HPP
#include<iostream>
#include<string.h>
using namespace std;

template<class Item>
class LinearList
{
	  private:
		int MaxSize;
		Item *element;    // 1D dynamic array
    int len=0;
	  public:
		/* Default constructor.
		 * Should create an empty list that does not contain any elements*/
		LinearList();

		/* This constructor should create a list containing MaxSize elements. You can intialize the elements with any values.*/
		LinearList(const int& MaxListSize);

		/* Destructor.
		 * Must free all the memory contained by the list */
		~LinearList();

		//indexing operator.
		Item& operator[](const int& i); //return i'th element of list


		/* Returns true if the list is empty, false otherwise.
     		 * */
		bool isEmpty();

		/* Returns the actual length (number of elements) in the list.
     		 * */
		int  length();

		/* Returns the maximum size of the list.
     		 * */
		int  maxSize();

		/* Returns the k-th element of the list.
		 * */
		Item  returnListElement(const int k);

		/* Set x to the k-th element and
		 * return true if k-th element is present otherwise return false.
		 * */
		bool find(const int k, Item& x);

		/* Search for x and
		 * return the position if found, else return 0.
		 * */
		int search(Item x);

		/* Set x to the k-th element and delete that k-th element.
		 * */
		void deleteElement(const int  k, Item& x);

		/* Insert x after k-th element.
		 * */
		void insert(const int  k, Item& x);
		void push_back(Item& val);
};
#endif
#include "seqLinearList.cpp"
