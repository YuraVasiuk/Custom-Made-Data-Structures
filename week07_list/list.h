/***********************************************************************
* Header:
*    List
* Summary:
*    Custom made List analogous to the std::list
*    The class will use Node and ListIterator classes
* Author
*    Yura Vasiuk
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

template <typename T>
class ListIterator;

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
	Node<T> * pPrev;

	Node() : pNext(NULL), pPrev(NULL) {}
	Node(T data) { this->data = data; this->pNext = NULL; this->pPrev = NULL; }
	Node(T data, Node<T> * pNext, Node<T> * pPrev)
	{
		this->data = data; this->pNext = pNext; this->pPrev = pPrev;
	}
};

/************************************************
* LIST
* Custom made List, analogous to the std::list
***********************************************/
template <typename T>
class List
{
public:
	// default constructor
	List() : numItems(0), pHead(NULL) , pTail(NULL) {}     // done

	// copy constructor : copy it
	List(const List<T> & rhs) throw (const char *);        // done

	// destructor
	~List() { clear(); }                                   // done

	// assignment operator
	List<T> & operator=(const List<T> & rhs) throw (const char *);  // done

	// check if empty
	bool empty() { return numItems == 0; }                 // done

	// what is the number of items in the list
	int size() { return numItems; }                        // done

	// empy the list of all the items
	void clear();                                          // done

	// add an item to the back of the list
	void push_back(T t) throw (const char *);              // done

	// add an item to the front of the list
	void push_front(T t) throw (const char *);             // done

	// returnt the element at the front of the list
	T & front() throw (const char *);                      // done

	// return the element at the back of the list
	T & back() throw (const char *);                       // done

	// return the interator to the front of the list
	ListIterator<T> begin() { return ListIterator<T>(pHead); }   // done

	// return the interator to the back of the list
	ListIterator<T> rbegin() { return ListIterator<T>(pTail); }  // done

	// return the iterator to the past-the-front of the list
	ListIterator<T> rend() { return NULL; }                // done

	// return the iterator to the past-the-back of the list
	ListIterator<T> end() { return NULL; }                 // done

	// insert the passed item before the passed pointer
	ListIterator<T> insert(ListIterator<T> pInsertBefore, T t) throw (const char *);

	// remove the item at the passed poiter
	void remove(ListIterator<T> pRemoveHere) throw (const char *);

	// I will need it for BigNumber operator=
	Node<T> * & getHead() { return pHead; }

private:
	int numItems;
	Node<T> * pHead;
	Node<T> * pTail;
};

/***************************************************
* LIST :: COPY CONSTRUCTOR
* Create a new List and copy the data into it
**************************************************/
template <typename T>
List<T> :: List(const List<T> & rhs) throw (const char *)
{
	pHead = NULL;
	pTail = NULL;
	numItems = 0;
	
	// nothing to do
	if (rhs.pHead == NULL)
		return ;

	// axiliary pointers
	Node<T> * pTraverseOld = NULL;
	Node<T> * pTraverseNew = NULL;
	Node<T> * pTemp = NULL;

	// make the first node 
	pHead = new Node<T>;
	pTail = pHead;
	// assign pointers
	pHead->pNext = NULL;
	pHead->pPrev = NULL;
	// assign traverses
	pTraverseNew = pHead;
	pTraverseOld = rhs.pHead;

	while (pTraverseOld->pNext != NULL)
	{
		// fill the new node data
		pTraverseNew->data = pTraverseOld->data;
		// making a one more node, fill the new node address
		pTraverseNew->pNext = new Node<T>;
		// temp
		pTemp = pTraverseNew;
		// move the traverses
		pTraverseOld = pTraverseOld->pNext;
		pTraverseNew = pTraverseNew->pNext;
		// assign pPrev of the current last node and increase numItems
		pTraverseNew->pPrev = pTemp;
		numItems++;
	}
	// fill the last node data and increase numItems
	pTraverseNew->data = pTraverseOld->data;
	numItems++;
	// assign the pTail
	pTail = pTraverseNew;
}

/***************************************************
* LIST :: ASSIGNMENT OPERATOR
* Copy the data into the list
**************************************************/
template <typename T>
List<T> & List<T> :: operator=(const List<T> & rhs) throw (const char *)
{
	// clear the current list
	this->clear();

	// nothing to do
	if (rhs.pHead == NULL)
		return * this;

	// axiliary pointers
	Node<T> * pTraverseOld = NULL;
	Node<T> * pTraverseNew = NULL;
	Node<T> * pTemp = NULL;

	// make the first node 
	this->pHead = new Node<T>;
	this->pTail = this->pHead;
	// assign pointers
	this->pHead->pNext = NULL;
	this->pHead->pPrev = NULL;
	// assign traverses
	pTraverseNew = this->pHead;
	pTraverseOld = rhs.pHead;

	while (pTraverseOld->pNext != NULL)
	{
		// fill the new node data
		pTraverseNew->data = pTraverseOld->data;
		// making a one more node, fill the new node address
		pTraverseNew->pNext = new Node<T>;
		// temp
		pTemp = pTraverseNew;
		// move the traverses
		pTraverseOld = pTraverseOld->pNext;
		pTraverseNew = pTraverseNew->pNext;
		// assign pPrev of the current last node and increase numItems
		pTraverseNew->pPrev = pTemp;
		numItems++;
	}
	// fill the last node data and increase numItems
	pTraverseNew->data = pTraverseOld->data;
	numItems++;
	// assign the pTail
	this->pTail = pTraverseNew;

	return * this;
}

/***************************************************
* LIST :: CLEAR
* Empty the list of all the items
**************************************************/
template <typename T>
void List<T> :: clear()
{
	// there is nothing to delete
	if (pHead == NULL)
		return;

	// axiliary pointers
	Node<T> * pDelete = pHead;
	Node<T> * pTraverse = pHead->pNext;

	while (pTraverse != NULL)
	{
		delete pDelete;
		pDelete = pTraverse;
		pTraverse = pTraverse->pNext;
	}
	// delete the last node and set the head and tail to NULL 
	delete pDelete;
	pHead = NULL;
	pTail = NULL;
	// last thing to do
	numItems = 0;
}

/***************************************************
* LIST :: PUSH_BACK
* Add an item to the back of the list
**************************************************/
template <typename T>
void List<T> :: push_back(T t) throw (const char *)
{
	// attempt to allocate a new node
	try
	{
		if (empty())
		{
			pHead = new Node<T>();
			pTail = pHead;
		}
		else
			pTail->pNext = new Node<T>();
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}

	// case 1) only one node in the list
	if (empty())
	{
		pHead->data = t;
		numItems++;
	}
	// case 2) reassign pTail, assign pPrev, fill with data, add numItems
	else
	{
		Node<T> * temp = pTail;
		pTail = pTail->pNext;
		pTail->pPrev = temp;
		pTail->data = t;
		numItems++;
	}
}


/***************************************************
* LIST :: PUSH_FRONT
* Add an item to the front of the list
**************************************************/
template <typename T>
void List<T> :: push_front(T t) throw (const char *)
{
	// temporary pointer
	Node<T> * temp;
	// attempt to allocate a new node, switch the pointers
	try
	{
		if (empty())
		{
			pHead = new Node<T>();
			pTail = pHead;
		}
		else
		{
			temp = pHead;
			pHead = new Node<T>();
			pHead->pNext = temp;           // the first node pointer
			pHead->pNext->pPrev = pHead;   // the second node pointer
		}
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}

	// finally, fill the data and increment the numItems
	pHead->data = t;
	numItems++;
}

/***************************************************
* LIST :: FRONT
* Return the element at the front of the list
**************************************************/
template <typename T>
T & List<T> :: front() throw (const char *)
{
	if (empty())
		throw "ERROR: unable to access data from an empty list";
	else
		return pHead->data;
}

/***************************************************
* LIST :: BACK
* Return the element at the back of the list
**************************************************/
template <typename T>
T & List<T> ::back() throw (const char *)
{
	if (empty())
		throw "ERROR: unable to access data from an empty list";
	else
		return pTail->data;
}

/***************************************************
* LIST :: INSERT
* Insert the passed element before the passed pointer 
* and return the pointer to the inserted element 
**************************************************/
template <typename T>
ListIterator<T> List<T> :: insert(ListIterator<T> pInsertBefore, T t) throw (const char *)
{
	// convert the pointer from ListIterator to Node type
	Node<T> * pNodeInsertBefore = pInsertBefore.p;

	Node<T> * temp;
	// attempt to allocate a new node
	try
	{
		temp = new Node<T>(t);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}
	
	// special cases
	// 1) insert after the list
	if (pNodeInsertBefore == NULL)
	{
		push_back(t);
		return NULL;
	}
	// 2) insert before the list
	if (pNodeInsertBefore->pPrev == NULL)
	{
		push_front(t);
		return NULL;
	}
	
	// usual cases
	// case 1) insert into empty list
	if (pHead == 0)
	{
		pHead = temp;
		pTail = temp;
	}
	// case 2) insert before the last node
	else if (pNodeInsertBefore == pTail)
	{
		pTail->pPrev->pNext = temp;
		temp->pPrev = pTail->pPrev;
		temp->pNext = pTail;
		pTail->pPrev = temp;
	}
	// case 3, 4) the rest: insert in the middle, insert before the first node
	else
	{
		temp->pNext = pNodeInsertBefore->pPrev->pNext;
		temp->pPrev = pNodeInsertBefore->pPrev;
		pNodeInsertBefore->pPrev = temp;
		// before the first, repoint the pHead
		if (pNodeInsertBefore == pHead)
			pHead = temp;
		else
			temp->pPrev->pNext = temp;
	}
	
	// the last thing to do
	numItems++;

	return NULL;
}

/***************************************************
* LIST :: REMOVE
* Remove the element at the passed pointer
**************************************************/
template <typename T>
void List<T> :: remove(ListIterator<T> pRemoveHere) throw (const char *)
{
	// nothing to remove
	if (pRemoveHere == end())
		throw "ERROR: unable to remove from an invalid location in a list";

	// convert the pointer from ListIterator to Node type
	Node<T> * pNodeRemoveHere = pRemoveHere.p;

	// reassign the pointers
	// case 1) remove the fist node
	if (pHead == pNodeRemoveHere)
	{
		pNodeRemoveHere->pNext->pPrev = NULL;
		pHead = pHead->pNext;
	}
	// case 2) remover the last node
	else if (pTail == pNodeRemoveHere)
	{
		pTail = pTail->pPrev;
		pTail->pNext = NULL;
	}
	// case 3) the rest, remove in the middle
	else
	{
		pNodeRemoveHere->pPrev->pNext = pNodeRemoveHere->pNext;
		pNodeRemoveHere->pNext->pPrev = pNodeRemoveHere->pPrev;
	}
	// delete the node
	delete pNodeRemoveHere;

	// last thing to do
	numItems--;
}

/**************************************************
* LIST ITERATOR
* An iterator through List
*************************************************/
template <typename T>
class ListIterator
{
public:
	// default constructor
	ListIterator() : p(0x00000000) {}

	// initialize to direct p to some item
	ListIterator(Node<T> * p) : p(p) {}

	// copy constructor
	ListIterator(const ListIterator<T> & rhs) { *this = rhs; }

	// assignment operator
	ListIterator<T> & operator = (const ListIterator<T> & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	// not equals operator
	bool operator != (const ListIterator<T> & rhs) const
	{
		return rhs.p != this->p;
	}

	// equals operator
	bool operator == (const ListIterator<T> & rhs) const
	{
		return rhs.p == this->p;
	}

	// dereference operator
	T & operator * ()
	{
		return p->data;
	}

	// prefix increment
	ListIterator<T> & operator++()
	{
		//p++;
		p = p->pNext;
		return *this;
	}

	// prefix decrement
	ListIterator<T> & operator--()
	{
		//p++;
		p = p->pPrev;
		return *this;
	}

	// these two functions will need the access to the iterator's private *p
	friend ListIterator<T> List<T>::insert(ListIterator<T> pInsertBefore, T t);
	friend void List<T>::remove(ListIterator<T> pRemoveHere);

private:
	Node<T> * p;
};

#endif // LIST_H