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
		p = new BinaryNode<T>(t);
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
		p = new BinaryNode<T>(t);
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
	if (p->pLeft != NULL)
		deleteBinaryTree(* & p->pLeft);
	if (p->pRight != NULL)
		deleteBinaryTree(* & p->pRight);
	delete p;
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