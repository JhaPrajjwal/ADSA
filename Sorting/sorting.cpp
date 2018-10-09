#ifndef SORTING_CPP
#define SORTING_CPP
#include "sorting.hpp"
#include "seqLinearList.hpp"
#include<iostream>

template<class Item>
void swapping(Item &x,Item &y)
{
	Item temp;
	temp=x;
	x=y;
	y=temp;
}

//insertion Sort
template<class Item>
void Sort<Item>::insertionSort(LinearList<Item>& A, int low, int high)
{
	 Item key;
	 int i,j;
   for(i=low+1;i<=high;i++)
   {
       key = A[i];
       j=i-1;

       while(j>=low&& A[j]>key)
       {
				 A[j+1] = A[j];
         j--;
       }
       A[j+1] = key;
   }
}


// bubble Sort
template<class Item>
void Sort<Item>::bubbleSort(LinearList<Item>& A, int low, int high)
{

  for(int i=0;i<=high-low+1;i++)
	{
		for(int j=low;j<=high-i-1;j++)
		{
			if(A[j]>A[j+1]) swapping(A[j],A[j+1]);
		}
	}
}

//selection Sort
template<class Item>
void Sort<Item>::selectionSort(LinearList<Item>& A, int low, int high)
{
  for(int i=low;i<=high;i++)
	{
		int min_index=i;
		for(int j=i+1;j<=high;j++)
		{
			if(A[j]<A[min_index]) min_index=j;
		}
		swapping(A[min_index],A[i]);
	}
}

//rank sort
template<class Item>
void Sort<Item>::rankSort(LinearList<Item>& A, int low, int high)
{
	LinearList<Item> R(A.length());
	//for(int i=low;i<=high;i++) R[i]=0;

	for(int j=low+1;j<=high;j++)
	{
		for(int i=low;i<j;i++)
		{
			if(A[i]<=A[j]) R[j]++;
			else R[i]++;
		}
	}

	LinearList<Item> U(A.length());
	for(int i=low;i<=high;i++) U[R[i]+low]=A[i];//low is added to push ranks up ..so that sorting occurs from [low,high]

	for(int i=low;i<=high;i++) A[i]=U[i];

}

//merge sort
template<class Item>
void merge(LinearList<Item>& A,int low,int mid,int high)
{
	int i=0,j=0,k=low,l_size=mid-low+1,r_size=high-mid;
	LinearList<Item> L(l_size),R(r_size);

	for(int i=0;i<l_size;i++) L[i]=A[low+i];
	for(int i=0;i<r_size;i++) R[i]=A[mid+1+i];

	while(i<l_size&&j<r_size)
	{
		if(L[i]<=R[j])
		{
			 A[k]=L[i];
			 i++;
			 k++;
		}
		else
		{
			A[k]=R[j];
			j++;
			k++;
		}
	}

	while(i<l_size)
	{
		A[k]=L[i];
		i++;
		k++;
	}
	while(j<r_size)
	{
		A[k]=R[j];
		j++;
		k++;
	}
}

template<class Item>
void Sort<Item>::mergeSort(LinearList<Item>& A, int low, int high)
{
	if(high==low) return;
	int mid=(low+high)/2;
	mergeSort(A,low,mid);
	mergeSort(A,mid+1,high);
	merge(A,low,mid,high);
}

// quick sort

template<class Item>
int partition(LinearList<Item>& A,int low,int high)
{
    Item pivot=A[high];
    int p=low-1;
    for(int i=low;i<high;i++)
    {
			if(A[i]<=pivot)
			{
				p++;
				swapping(A[p],A[i]);
			}
    }
    swapping(A[p+1],A[high]);
    return p+1;
}

template<class Item>
void Sort<Item>::quickSort(LinearList<Item>& A, int low, int high)
{
	if(low>=high) return;

	int index=partition(A,low,high);
	quickSort(A,low,index-1);
	quickSort(A,index+1,high);
}


//heap Sort

template<class Item>
void heapify(LinearList<Item>&A,int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l<n&&A[l]>A[largest]) largest=l;
    if(r<n&&A[r]>A[largest]) largest=r;

    if(largest!=i)
    {
			swapping(A[i],A[largest]);
      heapify(A,n,largest);
    }
}

template<class Item>
void Sort<Item>::heapSort(LinearList<Item>&A,int low,int high)
{
	int n=high-low+1;
	LinearList<Item> B(n);
	for(int i=0;i<n;i++) B[i]=A[i+low];

	for(int i=n/2-1;i>=0;i--) heapify(B,n,i);

	for(int i=n-1;i>=0;i--)
	{
		swap(B[0],B[i]);
		heapify(B,i,0);
	}

	for(int i=0;i<n;i++) A[i+low]=B[i];
}
#endif
