/***********************************************************************
* Header:
*    bNode
* Summary:
*    Node will be a part of BinaryTree class
* Author
*    Yura Vasiuk
************************************************************************/

#ifndef BNODE_H
#define BNODE_H

#include "pair.h"
#include <iostream>
using namespace std;

/************************************************
* NODE
* A class to be used in LinkedList
***********************************************/
template <typename T>
class BinaryNode
{
public:
	BinaryNode<T> * pLeft;
	BinaryNode<T> * pRight;
	BinaryNode<T> * pParent;
	T data;

	// default and non-default constructors
	BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL) {}
	BinaryNode(T data)
	{
		this->data = data; this->pLeft = NULL; this->pRight = NULL; this->pParent = NULL;
	}

	// add left and right
	BinaryNode<T> * addLeft(BinaryNode<T> *p) throw (const char *);
	BinaryNode<T> * addLeft(T t) throw (const char *);
	BinaryNode<T> * addRight(BinaryNode<T> *p) throw (const char *);
	BinaryNode<T> * addRight(T t) throw (const char *);

	int size() const;
};

/***************************************************
* SIZE
* Calculate and return the size of the tree
**************************************************/
template <typename T>
int BinaryNode<T>::size() const
{
	return 1 + (this->pLeft == NULL ? 0 : this->pLeft->size()) +
		(this->pRight == NULL ? 0 : pRight->size());
}

/***************************************************
* ADDLEFT
* Add a node to the left of the current one (two functions, overload)
**************************************************/
template <typename T>
BinaryNode<T> * BinaryNode<T> ::addLeft(BinaryNode<T> *p) throw (const char *)
{
	if (p != NULL)
	{
		p->pParent = this;
	}
	this->pLeft = p;

	return this;
}

template <typename T>
BinaryNode<T> * BinaryNode<T>::addLeft(T t) throw (const char *)
{
	BinaryNode<T> *p;
	try
	{
		p = new(nothrow)BinaryNode<T>(t);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a node";
	}
	addLeft(p);

	return this;
}

/***************************************************
* ADDRIGHT
* Add a node to the right of the current one (two functions, overload)
**************************************************/
template <typename T>
BinaryNode<T> * BinaryNode<T>::addRight(BinaryNode<T> * p) throw (const char *)
{
	if (p != NULL)
	{
		p->pParent = this;
	}
	this->pRight = p;

	return this;
}

template <typename T>
BinaryNode<T> * BinaryNode<T>::addRight(T t) throw (const char *)
{
	BinaryNode<T> *p;
	try
	{
		p = new(nothrow)BinaryNode<T>(t);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a node";
	}
	addRight(p);

	return this;
}

/***************************************************
* DELETE
* Delete all nodes
**************************************************/
template <typename T>
void deleteBinaryTree(BinaryNode<T> * & p)
{
	if (p != NULL)
	{
		if (p->pLeft != NULL)
			deleteBinaryTree(*& p->pLeft);
		if (p->pRight != NULL)
			deleteBinaryTree(*& p->pRight);
		delete p;
	}
	p = NULL;
}

/***************************************************
* OPERATOR<<
* Display the content of the passed Linked List
**************************************************/
template <typename T>
ostream & operator<<(ostream & out, BinaryNode<T> * pRhs)
{
	if (pRhs != NULL)
	{
		out << pRhs->pLeft;
		out << pRhs->data << " ";
		out << pRhs->pRight;
	}

	return out;
}


#endif // BNODE_H



/// THE NEXT THREE METHODS ARE COMMENTED OUT AS WE DO OT NEED TO DO THE TREE BALANCING !!!

// you might want to put these methods into your BinaryNode class
// to help you debug your red-black balancing code

/****************************************************
 * BINARY NODE :: FIND DEPTH
 * Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 * Author: Br. Helfrich
 ****************************************************/
/*
template <class T>
int BinaryNode <T> :: findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);

   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}
*/
/****************************************************
 * BINARY NODE :: VERIFY RED BLACK
 * Do all four red-black rules work here?
 * Author: Br. Helfrich
 ***************************************************/
/*
template <class T>
void BinaryNode <T> :: verifyRedBlack(int depth) const
{
   depth -= (isRed == false) ? 1 : 0;

   // Rule a) Every node is either red or black
   assert(isRed == true || isRed == false); // this feels silly

   // Rule b) The root is black
   if (pParent == NULL)
      assert(isRed == false);

   // Rule c) Red nodes have black children
   if (isRed == true)
   {
      if (pLeft != NULL)
         assert(pLeft->isRed == false);
      if (pRight != NULL)
         assert(pRight->isRed == false);
   }

   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}
*/
/******************************************************
 * VERIFY B TREE
 * Verify that the tree is correctly formed
 * Author: Br. Helfrich
 ******************************************************/
/*
template <class T>
void BinaryNode <T> :: verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);

   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }

   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}
*/