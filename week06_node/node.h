/***********************************************************************
* Header:
*    Node
* Summary:
*    Node will be a part of LinkedList class
* Author
*    Yura Vasiuk
************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

/************************************************
* NODE
* A class to be used in LinkedList
***********************************************/
template <typename T>
class Node
{
public:
	T data;
	Node<T> * pNext;

	Node() : pNext(NULL) {}
	Node(T data) { this->data = data; this->pNext = NULL; }
	Node(T data, Node<T> * pNext) { this->data = data; this->pNext = pNext; }
};

/***************************************************
* COPY
* Create a new LinkedList and copy the data into it
**************************************************/
template <typename T>
Node<T> * copy(Node<T> * pOldHead) 
{
	Node<T> * pNewHead = NULL;
	Node<T> * pTraverseOld = NULL;
	Node<T> * pTraverseNew = NULL;

	// nothing to do
	if (pOldHead == NULL)
		return pNewHead;

	// make the first node and assign traverses
	pNewHead = new Node<T>;
	pTraverseNew = pNewHead;
	pTraverseOld = pOldHead;
	
	while (pTraverseOld->pNext != NULL)
	{
        // fill the new node data
		pTraverseNew->data = pTraverseOld->data;
		// making a one more node, fill the new node address
		pTraverseNew->pNext = new Node<T>;
		// move the traverses
		pTraverseOld = pTraverseOld->pNext;
		pTraverseNew = pTraverseNew->pNext;
	}
	// fill the last node data
	pTraverseNew->data = pTraverseOld->data;

	return pNewHead;
}

/***************************************************
* FREEDATA
* Free all nodes and set the passed pointer to NULL
**************************************************/
template <typename T>
void freeData(Node<T> * & pHead)
{
	// there is nothing to delete
	if (pHead == NULL)
		return ;

	// axiliary pointers
	Node<T> * pDelete = pHead;
	Node<T> * pTraverse = pHead->pNext;

	while (pTraverse != NULL)
	{
		delete pDelete;
		pDelete = pTraverse;
		pTraverse = pTraverse->pNext;
	}
	// delete the last node and set the head to NULL 
	delete pDelete;
	pHead = NULL;
}

/***************************************************
* INSERT
* Insert a new value into the list 
* (the optional parameter: true - insert at the head, false - insert elsewhere)
**************************************************/
template <typename T>
void insert(T t, Node<T> * & pPreceeding, bool insertAtHead = false)
{
	// creat the new node
	Node<T> * pInsert = new Node<T>(t);

	// case 1 -- insert at the head
	if (insertAtHead == true)
	{
		pInsert->pNext = pPreceeding;
		pPreceeding = pInsert;
	}
	// case 2 -- insert elsewhere
	else
	{
		// insert as the last node, nowhere to repoint the new node
		if (pPreceeding == NULL)
			pPreceeding = pInsert;
		else
		{
			pInsert->pNext = pPreceeding->pNext;
			pPreceeding->pNext = pInsert;
		}
	}
}

/***************************************************
* OPERATOR<<
* Display the content of the passed Linked List
**************************************************/
template <typename T>
ostream & operator<<(ostream & out, Node<T> * pHead)
{
	// axiliary pointer
	Node<T> * pTraverse = pHead;
	 
	while (pTraverse != NULL)
	{
		out << pTraverse->data;
		pTraverse = pTraverse->pNext;
		if (pTraverse != NULL)
			out << ", ";
	}

	return out;
}

/***************************************************
* FIND
* Find the passed value in the List
**************************************************/
template <typename T>
Node<T> * find(Node<T> * pHead, T t)
{
	Node<T> * pTraverse = pHead;

	while (pTraverse != NULL)
	{
		if (pTraverse->data == t)
			return pTraverse;
		pTraverse = pTraverse->pNext;
	}

	return pTraverse;
}

/***************************************************
* INSERTIONSORT
* Sort an array using a linked list
**************************************************/
template <typename T>
void insertionSort(T ansorted[], int numItems)
{
	// start the list
	Node<T> * pHead = new Node<T>(ansorted[0]);
	// make the axiliary pointer
	Node<T> * pTraverse;

	// find the right place and fill the list
	for (int i = 1; i < numItems; i++)
	{
		// every time start from the head
		pTraverse = pHead;
		// insert at the head case
		if (ansorted[i] < pTraverse->data)
		{
			insert(ansorted[i], pTraverse, true);
			// switch the head
			pHead = pTraverse;
		}
		else
		{
			// just 1 node in the list case
			if (pTraverse->pNext == NULL)
				insert(ansorted[i], pTraverse);
			// more than 1 node and go up the list
			else
			{
				// untill finding the insertion place
				while(pTraverse->pNext->pNext != NULL && 
					pTraverse->pNext->data < ansorted[i])
					pTraverse = pTraverse->pNext;
				// the last node data is still smaller than the data to insert
				if (pTraverse->pNext->pNext == NULL &&
					pTraverse->pNext->data < ansorted[i])
					insert(ansorted[i], pTraverse->pNext);
				// finally
				else
					insert(ansorted[i], pTraverse);
			}
		}
	}

	// copy the list back into the array
	pTraverse = pHead;
	for (int i = 0; i < numItems; i++)
	{
		ansorted[i] = pTraverse->data;
		pTraverse = pTraverse->pNext;
	}
}

#endif // NODE_H