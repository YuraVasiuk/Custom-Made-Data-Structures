/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Yurii Vasiuk  
* Summary: 
*   The implemetation of the merge sort
************************************************************************/
#include <list>
   
using namespace std;

/*************************************************************************
* This function will be used in the merge sort
**************************************************************************/
template<class T>
bool split(list<T> & data, list<T> & list1, list<T> & list2)
{
	list<T>::iterator itF = data.begin();
	list<T>::iterator itS = ++data.begin();
	int numElList1 = 0;
	
	// till the end of the data list
	while (itS != data.end())
	{
		// filling the first sublist
		list1.push_back(*itF);
		numElList1++;
		while (itS != data.end() && *itF < *itS)
		{
			list1.push_back(*itS);
			itF++;
			itS++;
			numElList1++;
		}
		if (itS != data.end())
		{
			itF++;
			itS++;
		}
		// already sorted, return true
		if (numElList1 == data.size())
			return true;

		// filling the second sublist
		list2.push_back(*itF);
		while (itS != data.end() && *itF < *itS)
		{
			list2.push_back(*itS);
			itF++;
			itS++;
		}
		if (itS != data.end())
		{
			itF++;
			itS++;
		}
	}
	
	// the data is not sorted yet, there will be more splitting
	return false;
}

/*************************************************************************
* This function will be used in the merge sort
**************************************************************************/
template<class T>
void merge(list<T> & data, list<T> & list1, list<T> & list2)
{
	// for list1
	list<T>::iterator it11 = list1.begin();   // the beginning of the sublist
	list<T>::iterator it12 = list1.begin(); // the next after the end of the sublist
	// for list2
	list<T>::iterator it21 = list2.begin();   // the beginning of the sublist
	list<T>::iterator it22 = list2.begin(); // the next after the end of the sublist

	// until the end of the one of the lists
	while (next(it12) != list1.end() && next(it22) != list2.end())
	{
		// special case -- both sublists have 1 element
		if (!(*it12 < *next(it12)) && !(*it22 < *next(it22)))
		{
			if (*it11 < *it21)
			{
				data.push_back(*it11);
				data.push_back(*it21);
				++it11; ++it12; ++it21; ++it22;
			}
			else
			{
				data.push_back(*it21);
				data.push_back(*it11);
				++it11; ++it12; ++it21; ++it22;
			}
		}
		// make limits for the sublists
		while (next(it12) != list1.end() && *it12 < *next(it12))
			++it12;
		while (next(it22) != list2.end() && *it22 < *next(it22))
			++it22;

		// working with the sublists----------------------------------
		// until the end of the one of the sublists
		while (it11 != it12 && it21 != it22)
		{
			// compare, dump into the data, move the iterator
			if (*it11 < *it21)
			{
				data.push_back(*it11);
				++it11;
			}
			else
			{
				data.push_back(*it21);
				++it21;
			}
		}
		// this is the end of the one of the sublists
		// dumpt the rest of the elements into the data
		while (it11 != it12)
		{
			data.push_back(*it11);
			++it11;
		}
		while (it21 != it22)
		{
			data.push_back(*it21);
			++it21;
		}
		// handle the lats elements of the sublists
		if (next(it12) != list1.end())
		{
			if (*it11 < *it21)
			{
				data.push_back(*it11);
				data.push_back(*it21);
			}
			++it12; // step beyond the sublist
		}
		if (next(it22) != list2.end())
		{
			if (*it11 >= *it21)
			{
				data.push_back(*it21);
				data.push_back(*it11);
			}
			++it22; // step beyond the sublist
		}

		// the ends of both sublists, everything has been dumped into the data
		// both iterators stepped beyond the sublists
		// and are pointing at the first elements or at the end of one of the sublists
	}
	
	// at this point one of the iterators is pointing at the last element of the sublist
	// dump this element into the data and dump the rest elements from another sublist
	if (next(it12) == list1.end())
	{
		data.push_back(*it11);
		while (it21 != list2.end())
		{
			data.push_back(*it21);
			++it21;
		}
	}
	else if (next(it22) == list2.end())
	{
		data.push_back(*it21);
		while (it11 != list1.end())
		{
			data.push_back(*it11);
			++it11;
		}
	}
}
/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template<class T>
void mergeSort(list<T> & data)
{
	list<T> list1;
	list<T> list2;

	while (!split(data, list1, list2))
	{
		data.clear();
		merge(data, list1, list2);
		list1.clear();
		list2.clear();
	}
}



