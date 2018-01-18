/***********************************************************************
* Component:
*    Week 09, Binary Search Tree (BST)
*    Brother Ercanbrack, CS 235
* Author:
*    Br. Helfrich
*    Modified by Scott Ercanbrack - removed most of the the BST class functions,
*                                   but left BST Iterator class.
* Summary:
*    Create a binary search tree
************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack

// forward declaration for the BST iterator
template <class T>
class BSTIterator;

/*****************************************************************
* BINARY SEARCH TREE
* Create a Binary Search Tree
*****************************************************************/
template <class T>
class BST
{
public:
	// constructor
	BST() : root(NULL){};

	// copy constructor
	BST(const BST & rhs);

	~BST();

	int  size() const  { return empty() ? 0 : root->size(); }   // BinaryNode class needs a size function


	// determine if the tree is empty
	bool empty() const
	{
		if (this->root == NULL)
			return true;
		else
			return false;
	}

	// clear all the contests of the tree
	void clear()
	{
		deleteBinaryTree(root);
	}

	// overloaded assignment operator
	BST & operator = (const BST & rhs) throw (const char *)
	{
		deleteBinaryTree(this->root);
		// iterate the rhs tree and insert the values into this tree
		for (BSTIterator<T> it = rhs.begin(); it != rhs.end(); it++)
		{
			insert(*it);
		}

		return *this;
	}

	// insert an item
	void insert(const T & t) throw (const char *);

	// these two method will be used in the remove
	void remove_with_left_child(BinaryNode<T> * & pRemove);
	void remove_with_right_child(BinaryNode<T> * & pRemove);
	// remove an item
	void remove(BSTIterator <T> & it);

	// find a given item
	BSTIterator <T> find(const T & t);

	// the usual iterator stuff
	BSTIterator <T> begin() const;
	BSTIterator <T> end() const             { return BSTIterator <T>(NULL); }
	BSTIterator <T> rbegin() const;
	BSTIterator <T> rend() const           { return BSTIterator <T>(NULL); }

private:

	BinaryNode <T> * root;
};

/*********************************************************
* copy constructor
**********************************************************/
template <class T>
BST<T>::BST(const BST &rhs)
{
	// nothing to copy
	if (rhs.root == NULL)
		this->root = NULL;

	// !!! ALWAYS ASSIGN VARIABLES IN CONSTRUCTORS
	this->root = NULL;
	// iterate the rhs tree and insert the values into this tree
	for (BSTIterator<T> it = rhs.begin(); it != rhs.end(); it++)
	{
		insert(*it);
	}
}

/*****************************************************
* Destructor
*******************************************************/
template <class T>
BST<T>::~BST()
{
	if (root != NULL)
		deleteBinaryTree(root);
}


/*****************************************************
* BST :: BEGIN
* Return the first node (left-most) in a binary search tree
****************************************************/
template <class T>
BSTIterator <T> BST <T> ::begin() const
{
	Stack < BinaryNode <T> * > nodes;

	nodes.push(NULL);
	nodes.push(root);
	while (nodes.top() != NULL && nodes.top()->pLeft)
		nodes.push(nodes.top()->pLeft);

	return BSTIterator<T>(nodes);
}

/*****************************************************
* BST :: RBEGIN
* Return the last node (right-most) in a binary search tree
****************************************************/
template <class T>
BSTIterator <T> BST <T> ::rbegin() const
{
	Stack < BinaryNode <T> * > nodes;

	nodes.push(NULL);
	nodes.push(root);
	while (nodes.top() != NULL && nodes.top()->pRight)
		nodes.push(nodes.top()->pRight);

	return BSTIterator<T>(nodes);
}

/*****************************************************
* BST :: INSERT
* Insert a node at a given location in the tree
****************************************************/
template <class T>
void BST <T> ::insert(const T & t) throw (const char *)
{
	// insert as the root node
	if (root == NULL)
	{
		try
		{
			root = new(nothrow)BinaryNode<T>(t);
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a node";
		}
	}
	// insert as a leaf node
	else
	{
		bool inserted = false;
		BinaryNode<T> * traverse = root;
		// go down the tree until finding the insert place
		// and add the new node at the place 
		while (inserted == false)
		{
			if (t <= traverse->data)
			{
				if (traverse->pLeft == NULL)
				{
					traverse->addLeft(t);
					inserted = true;
				}
				else
					traverse = traverse->pLeft;
			}
			else
			{
				if (traverse->pRight == NULL)
				{
					traverse->addRight(t);
					inserted = true;
				}
				else
					traverse = traverse->pRight;
			}
		}
	}
}

/*************************************************
* BST :: REMOVE_WITH_LEFT_CHILD, REMOVE_WITH_RIGHT_CHILD
* Tese two methods will be used in the REMOVE
************************************************/
template <class T>
void BST <T> ::remove_with_left_child(BinaryNode<T> * & pRemove)
{
	// reassign pointers
	// remove node is a right child
	if (pRemove->pParent->pRight != NULL)
	{
		pRemove->pParent->pRight = pRemove->pLeft;
		pRemove->pLeft->pParent = pRemove->pParent;
	}
	// remove node is a left child
	if (pRemove->pParent->pLeft != NULL)
	{
		pRemove->pParent->pLeft = pRemove->pLeft;
		pRemove->pLeft->pParent = pRemove->pParent;
	}
	// delete the node
	delete pRemove;
}

template <class T>
void BST <T> ::remove_with_right_child(BinaryNode<T> * & pRemove)
{
	// reassign pointers
	// remove node is a right child
	if (pRemove->pParent->pRight == pRemove)
	{
		pRemove->pParent->pRight = pRemove->pLeft;
		pRemove->pRight->pParent = pRemove->pParent;
	}
	// remove node is a left child
	else if (pRemove->pParent->pLeft == pRemove)
	{
		pRemove->pParent->pLeft = pRemove->pRight;
		pRemove->pRight->pParent = pRemove->pParent;
	}
	// delete the node
	delete pRemove;

}
/*************************************************
* BST :: REMOVE
* Remove a given node as specified by the iterator
************************************************/
template <class T>
void BST <T> ::remove(BSTIterator <T> & it)
{
	// the pointer to the node to be removed
	BinaryNode<T> * pRemove = it.getNode();

	// three cases are possible

	// 1) remove the leaf with no children
	if (pRemove->pLeft == NULL && pRemove->pRight == NULL)
	{
		pRemove->pParent->pRight = NULL;
		delete pRemove;
	}

	// 2) remove the node with one child
	// 2a) with left child
	else if (pRemove->pLeft != NULL && pRemove->pRight == NULL)
	{
		// special case (remove the root node with one left child)
		if (pRemove->pParent == NULL)
		{
			root = pRemove->pLeft;
			root->pParent = NULL;
		}
		else
		{
			remove_with_left_child(pRemove);
		}
	}
	// 2b) with right child
	else if (pRemove->pLeft == NULL && pRemove->pRight != NULL)
	{
		remove_with_right_child(pRemove);
	}

	// 3) remove with two children
	// get the in-order successor
	else if (pRemove->pLeft != NULL && pRemove->pRight != NULL)
	{
		BinaryNode<T> * pInOrderSuccessor = pRemove->pRight;
		while (pInOrderSuccessor->pLeft != NULL)
			pInOrderSuccessor = pInOrderSuccessor->pLeft;
		// assign the data in the remove node to the data in the in-order successor node
		pRemove->data = pInOrderSuccessor->data;
		// now just remove the successor (it is always a leaf or a parent with one child) 
		// 3a) as a leaf
		if (pInOrderSuccessor->pRight == NULL)
		{
			delete pInOrderSuccessor;
		}
		// 3b) as a parent with the right child
		else if (pInOrderSuccessor->pRight != NULL)
		{
			remove_with_right_child(pInOrderSuccessor);
		}
	}
}

/****************************************************
* BST :: FIND
* Return the node corresponding to a given value
****************************************************/
template <class T>
BSTIterator <T> BST <T> ::find(const T & t)
{
	// for traversing down the tree
	BinaryNode<T> * traverse = root;

	while (true)
	{
		if (traverse->data > t && traverse->pLeft != NULL)
			traverse = traverse->pLeft;
		else if (traverse->data < t && traverse->pRight != NULL)
			traverse = traverse->pRight;
		else if (traverse->data == t)
		{
			// the iterator to be returned
			BSTIterator<T> it = BSTIterator<T>(traverse);
			return it;
		}
		else
			return end();
	}
}


/**********************************************************
* BINARY SEARCH TREE ITERATOR
* Forward and reverse iterator through a BST
*********************************************************/
template <class T>
class BSTIterator
{
public:
	// constructors
	BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p); }
	BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s; }
	BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

	// assignment
	BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
	{
		// need an assignment operator for the Stack class.
		nodes = rhs.nodes;
		return *this;
	}

	// compare
	bool operator == (const BSTIterator <T> & rhs) const
	{
		// only need to compare the leaf node 
		return rhs.nodes.const_top() == nodes.const_top();
	}
	bool operator != (const BSTIterator <T> & rhs) const
	{
		// only need to compare the leaf node 
		return rhs.nodes.const_top() != nodes.const_top();
	}

	// de-reference. Cannot change because it will invalidate the BST
	T & operator * ()
	{
		return nodes.top()->data;
	}

	// iterators
	BSTIterator <T> & operator ++ ();
	BSTIterator <T>   operator ++ (int postfix)
	{
		BSTIterator <T> itReturn = *this;
		++(*this);
		return itReturn;
	}
	BSTIterator <T> & operator -- ();
	BSTIterator <T>   operator -- (int postfix)
	{
		BSTIterator <T> itReturn = *this;
		--(*this);
		return itReturn;
	}

	// must give friend status to remove so it can call getNode() from it
	friend void BST <T> ::remove(BSTIterator <T> & it);

private:

	// get the node pointer
	BinaryNode <T> * getNode() { return nodes.top(); }

	// the stack of nodes
	Stack < BinaryNode <T> * > nodes;
};


/**************************************************
* BST ITERATOR :: INCREMENT PREFIX
* advance by one
*************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
	// do nothing if we have nothing
	if (nodes.top() == NULL)
		return *this;

	// if there is a right node, take it
	if (nodes.top()->pRight != NULL)
	{
		nodes.push(nodes.top()->pRight);

		// there might be more left-most children
		while (nodes.top()->pLeft)
			nodes.push(nodes.top()->pLeft);
		return *this;
	}

	// there are no right children, the left are done
	assert(nodes.top()->pRight == NULL);
	BinaryNode <T> * pSave = nodes.top();
	nodes.pop();

	// if the parent is the NULL, we are done!
	if (NULL == nodes.top())
		return *this;

	// if we are the left-child, got to the parent.
	if (pSave == nodes.top()->pLeft)
		return *this;

	// we are the right-child, go up as long as we are the right child!
	while (nodes.top() != NULL && pSave == nodes.top()->pRight)
	{
		pSave = nodes.top();
		nodes.pop();
	}

	return *this;
}

/**************************************************
* BST ITERATOR :: DECREMENT PREFIX
* advance by one
*************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
	// do nothing if we have nothing
	if (nodes.top() == NULL)
		return *this;

	// if there is a left node, take it
	if (nodes.top()->pLeft != NULL)
	{
		nodes.push(nodes.top()->pLeft);

		// there might be more right-most children
		while (nodes.top()->pRight)
			nodes.push(nodes.top()->pRight);
		return *this;
	}

	// there are no left children, the right are done
	assert(nodes.top()->pLeft == NULL);
	BinaryNode <T> * pSave = nodes.top();
	nodes.pop();

	// if the parent is the NULL, we are done!
	if (NULL == nodes.top())
		return *this;

	// if we are the right-child, got to the parent.
	if (pSave == nodes.top()->pRight)
		return *this;

	// we are the left-child, go up as long as we are the left child!
	while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
	{
		pSave = nodes.top();
		nodes.pop();
	}

	return *this;
}


#endif // BST_H
