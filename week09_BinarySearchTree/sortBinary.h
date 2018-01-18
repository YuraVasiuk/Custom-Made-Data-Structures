/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
	// the tree will be populated with the array values
	BST<T> myTree = BST<T>();

	// populate the tree
	for (int i = 0; i < num; i++)
	{
		myTree.insert(array[i]);
	}

	int index = 0;
	// iterate the tree and return values into the array
	for (BSTIterator<T> it = myTree.begin(); it != myTree.end(); it++)
	{
		array[index] = *it;
		index++;
	}
}


#endif // SORT_BINARY_H
