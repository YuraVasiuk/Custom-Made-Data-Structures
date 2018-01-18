/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Yurii Vasiuk  
* Summary: 
*   The implementation of the heap sort
************************************************************************/
#include <vector>
   
using namespace std;

/*************************************************************************
* Percolate down
**************************************************************************/
template<class T>
void percolateDown(vector<T> & data, int first, int last)
{
	T temp;
	int child = first * 2;
	while (child < last)
	{
		if (child < last - 1 && data[child] < data[child + 1])
			child++;
		if (data[first] < data[child])
		{
			temp = data[first];
			data[first] = data[child];
			data[child] = temp;
			first = child;
			child = first * 2;
		}
		else
			break;
	}
}

/*************************************************************************
* Heapify the tree
**************************************************************************/
template<class T>
void heapify(vector<T> & myHeap)
{
	for (int i = myHeap.size() / 2 - 1; i > 0; i--)
	{
		percolateDown(myHeap, i, myHeap.size());
	}
}

/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(vector<T> & data)
{
	heapify(data);

	T temp;
	for (int i = (data.size() - 1); i > 1; i--)
	{
		temp = data[1];
		data[1] = data[i];
		data[i] = temp;
		percolateDown(data, 1, i);
	}
}
