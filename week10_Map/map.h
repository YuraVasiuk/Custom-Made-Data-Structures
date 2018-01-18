/***********************************************************************
* Component:
*    Week 10, Map
* Author:
*    Yurii Vasiuk
* Summary:
*    Map class analogous to the stl::map
************************************************************************/

#ifndef MAP_H
#define MAP_H

#include "bst.h"      // for Binary Search Tree
#include "pair.h"     // for Pair

// forward declaration for the Map iterator
template <class K, class V>
class MapIterator;

/*****************************************************************
* MAP
* Create a Map
*****************************************************************/
template <class K, class V>
class Map
{
public:
	// constructor
	Map() : numItems(0), bst(BST<Pair <K, V> >()) { }

	// copy constructor
	Map(const Map & rhs) : numItems(rhs.numItems), bst(BST<Pair <K, V> >(rhs.bst)) { }

	// destructor
	~Map() { bst.~BST(); }

	// overloaded assignment operator
	Map & operator = (const Map & rhs) throw (const char *)
	{
		numItems = rhs.numItems; bst = rhs.bst;   return *this;
	}

	// is the map empty?
	bool empty() const { return bst.empty(); }

	// how big is the map?
	int size() const { return numItems; }

	// delete all the elements in the map
	void clear() { numItems = 0; bst.clear(); }

	// find an item value by the given item key
	MapIterator <K, V> find(const K & k);

	// the key method of the class
	V & operator[](K k);

	// the iterator methods
	MapIterator <K, V> begin() const           { return MapIterator <K, V>(bst.begin()); }
	MapIterator <K, V> end() const             { return MapIterator <K, V>(bst.end()); }
	MapIterator <K, V> rbegin() const           { return MapIterator <K, V>(bst.rbegin()); }
	MapIterator <K, V> rend() const             { return MapIterator <K, V>(bst.rend()); }

private:
	BST <Pair <K, V> > bst;
	int numItems;
};

/****************************************************
* Map :: FIND
* Return the node corresponding to a given value
****************************************************/
template <class K, class V>
MapIterator <K, V> Map <K, V> :: find(const K & k)
{
	V garbage;
	BSTIterator <Pair <K, V> > itBST = bst.find(Pair <K, V>(k, garbage));
	MapIterator <K, V> it = MapIterator <K, V>(itBST);
	return it;
}

/****************************************************
* Map :: ARRAY INDEX OPERAOT 
* 1) if the value is not in the map, insert the data tied to the passed key into the map
* 2) retreive the value found by the passed key 
****************************************************/
template <class K, class V>
V & Map <K, V> :: operator[](K k)
{
	V value;
	Pair <K, V> pairInsert = Pair <K, V>(k, value);
	// see if the value is in the map
	MapIterator <K, V> it = find(k);
	// if not, insert the value
	if (it == end())
	{
		bst.insert(pairInsert);
		numItems++;
	}
	// retreive the found value
	else
	{
		return *it;
	}
	// retreive the inserted value
	it = find(k);
	return *it;
}

/*****************************************************************
* MAP ITERATOR
* Forward and reverse iterator through a Map
*****************************************************************/
template <class K, class V>
class MapIterator
{
public:
	// constructors
	MapIterator() : it(BSTIterator <Pair <K, V> >()) {}
	MapIterator(BSTIterator <Pair <K, V> > itBST) { this->it = itBST; }
	
	// de-reference. Cannot change because it will invalidate the BST
	V & operator * ()
	{
		return (*it).second;
	}

	// compare (equal and not equal)
	bool operator == (const MapIterator <K, V> & rhs) const
	{
		// only need to compare
		return this->it == rhs.it;
	}
	bool operator != (const MapIterator <K, V> & rhs) const
	{
		// only need to compare
		return this->it != rhs.it;
	}

	// iterators
	MapIterator <K, V> & operator ++ ()
	{
		++it;
		return *this;
	}
	MapIterator <K, V>   operator ++ (int postfix)
	{
		MapIterator <K, V> itReturn = *this;
		++(*this);
		return itReturn;
	}
	MapIterator <K, V> & operator -- ()
	{
		--it;
		return *this;
	}
	MapIterator <K, V>   operator -- (int postfix)
	{
		MapIterator <K, V> itReturn = *this;
		--(*this);
		return itReturn;
	}

private:
	BSTIterator <Pair <K, V> > it;
};

#endif // MAP_H