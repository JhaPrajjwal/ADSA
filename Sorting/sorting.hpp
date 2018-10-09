#ifndef SORTING_HPP
#define SORTING_HPP
#include <iostream>
#include "seqLinearList.hpp"

template<class Item>
class Sort
{
	private:

	public:
		void insertionSort(LinearList<Item>& A, int low, int high);
		void bubbleSort(LinearList<Item>& A,int low, int high);
	 	void rankSort(LinearList<Item>& A, int low, int high);
    void selectionSort(LinearList<Item>& A, int low, int high);
    void mergeSort(LinearList<Item>& A, int low, int high);
    void quickSort(LinearList<Item>& A, int low, int high);
		void heapSort(LinearList<Item>& A,int low,int high);
};
#endif
#include "sorting.cpp"
