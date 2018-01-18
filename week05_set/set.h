/***********************************************************************
* Header:
*    Set
* Summary:
*	 This is a custom made set, analogous to the STD set
*
*    This will contain the class definition of:
*        Set               : A class that holds stuff
*        Set Iterator      : An interator through Set
* Author
*    Yurii Vasiuk
************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>

// forward declaration for SetIterator
template <class T>
class SetIterator;

/************************************************
* SET
* A class analogous to the STD set
* The methods are based on the arrangement to keep the set sorted
***********************************************/
template <class T>
class Set
{
public:
	// default constructor : empty and kinda useless
	Set() : _numItems(0), _capacity(0), _data(0x00000000) {} // done

	// copy constructor : copy it
	Set(const Set & rhs) throw (const char *);               // done

	// non-default constructor : pre-allocate
	Set(int capacity) throw (const char *);                  // done

	// assignmetnt operator
	Set<T> & operator=(const Set<T> & rhs) throw(const char *); // done

	// destructor : free everything
	~Set()        { if (_capacity) delete[] _data; }         // done

	// is the set currently empty
	bool empty() const  { return _numItems == 0; }           // done

	// remove all the items from the set
	void clear()        { _numItems = 0; }                   // done

	// how many items are currently in the set?
	int size() const    { return _numItems; }                // done

	// how many items can be put in the set?
	int capacity() const    { return _capacity; }            // done

	// add an item to the set
	void insert(const T & t) throw (const char *);           // done

	// find an item in the set
	SetIterator <T> find(T t);                               // done

	// erase an item in the set
	void erase(SetIterator <T> iterator);                    // done

	// intersection -- return a new set containing element from both sets
	Set <T> operator&&(Set <T> rhs);

	// union -- return a new set containing element from either of two sets
	Set <T> operator||(Set <T> rhs);

	// return an iterator to the beginning of the list
	SetIterator <T> begin() { return SetIterator<T>(_data); } // done

	// return an iterator to the end of the list
	SetIterator <T> end() { return SetIterator<T>(_data + _numItems); } // done

private:
	T * _data;          // dynamically allocated array of T
	int _numItems;      // how many items are currently in the Set?
	int _capacity;      // how many items can I put on the Set before full?

	int searchFor(T t); // auxiliary method to use in insert() and find()
};

/**************************************************
* SET ITERATOR
* An iterator through Set
*************************************************/
template <class T>
class SetIterator
{
public:
	// default constructor
	SetIterator() : _p(0x00000000) {}

	// initialize to direct p to some item
	SetIterator(T * p) : _p(p) {}

	// copy constructor
	SetIterator(const SetIterator & rhs) { *this = rhs; }

	// assignment operator
	SetIterator & operator = (const SetIterator & rhs)
	{
		_p = rhs._p;
		return *this;
	}

	// not equals operator
	bool operator != (const SetIterator & rhs) const
	{
		return rhs._p != _p;
	}

	// dereference operator
	T & operator * ()
	{
		return *_p;
	}

	// prefix increment
	SetIterator <T> & operator ++ ()
	{
		_p++;
		return *this;
	}

	// postfix increment
	SetIterator <T> operator++(int postfix)
	{
		SetIterator tmp(*this);
		_p++;
		return tmp;
	}

private:
	T * _p;
};

/*******************************************
* SET :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Set <T>::Set(const Set <T> & rhs) throw (const char *)
{
	assert(rhs._capacity >= 0);

	// do nothing if there is nothing to do
	if (rhs._capacity == 0)
	{
		_capacity = _numItems = 0;
		_data = 0x00000000;
		return;
	}

	// attempt to allocate
	try
	{
		_data = new T[rhs._capacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for Set.";
	}

	// copy over the stuff
	assert(rhs._numItems >= 0 && rhs._numItems <= rhs._capacity);
	_capacity = rhs._capacity;
	_numItems = rhs._numItems;
	for (int i = 0; i < _numItems; i++)
		_data[i] = rhs._data[i];
}

/**********************************************
* SET : NON-DEFAULT CONSTRUCTOR
* Preallocate the set to "capacity"
**********************************************/
template <class T>
Set <T>::Set(int capacity) throw (const char *)
{
	assert(capacity >= 0);

	// do nothing if there is nothing to do
	if (capacity == 0)
	{
		_capacity = _numItems = 0;
		_data = 0x00000000;
		return;
	}

	// attempt to allocate
	try
	{
		_data = new T[capacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}


	// copy over the stuff
	_capacity = capacity;
	_numItems = 0;
}

/*******************************************
* SET :: ASSIGNMENT OPERATOR
* Assign one set to another.  Return by reference!
*******************************************/
template <class T>
Set<T> & Set <T>::operator=(const Set <T> & rhs) throw (const char *)
{
	assert(rhs._capacity >= 0);

	// attempt to allocate
	if (_capacity < rhs._capacity)
	{
		try
		{
			delete[] _data;  // prevents memory leak!!!
			_data = new T[rhs._capacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for Set";
		}
	}

	// copy over the stuff
	assert(rhs._numItems >= 0 && rhs._numItems <= rhs._capacity);
	_capacity = rhs._capacity;
	_numItems = rhs._numItems;
	for (int i = 0; i < _numItems; i++)
		_data[i] = rhs._data[i];

	// the rest needs to be filled with the default value for T
	for (int i = _numItems; i < _capacity; i++)
		_data[i] = T();

	return *this;
}

/***************************************************
* SET :: INSERT
* Insert an item into the set
**************************************************/
template <class T>
void Set <T>::insert(const T & t) throw (const char *)
{
	// case 1) insert into the empty set
	if (_numItems == 0)
	{
		_capacity = 2;
		_data = new T[_capacity];
		_data[0] = t;
		_numItems = 1;
		return ;
	}
	
	int searchResult = searchFor(t);
	// case 2) the element is already in the set
	if (searchResult > 0 && searchResult != _numItems)
		return ;
	
	// case 3) the element will be inserted
	else
	{
		// not enough memory, reallocate-------------------------  
		if (_numItems == _capacity)
		{
			T * temp = _data;
			_capacity *= 2;
			// attempt to allocate
			try
			{
				_data = new T[_capacity];
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: Unable to allocate buffer for the set";
			}
			// copy the stuff
			for (int i = 0; i < _numItems; i++)
				_data[i] = temp[i];
			// nullify the rest of the array
			for (int i = _numItems; i < _capacity; i++)
				_data[i] = T();
			// free the old memory
			delete[] temp;
		}
		// end of reallocation------------------------------------------

		// 3a) insert on the end of the array, add numItems, leave
		if (searchResult == _numItems)
		{
			_data[_numItems] = t;
			_numItems++;
			return;
		}
		// 3b) insert in the middle of the set, add numItems
		if (searchResult <= 0)
		{
			// single case: 0 index element is already in the set
			if (_data[0] == t)
				return ;
			// the insertion point
			int insertionPoint = -1 * searchResult;
			// shift the bigger part of the array
			for (int i = _numItems; i > insertionPoint; i--)
				_data[i] = _data[i - 1];
			// insert
			_data[insertionPoint] = t;
			_numItems++;
		}
	}
}

/***************************************************
* SET :: SEARCHFOR
* A precaution must be remembered when using this method: 
* it returns 0 in two cases -- when the item that equals 0 index element is in the set 
* and when the item is smaller than any element in the set!!
* This is a private function that returns 
* if found:
* 1)the index of found element (0 or positive int, but not numItems); 
* if not found:
* 2a) numItems if all elements are smaller than t and insertion comes on the end of the array,
* 2b) the -1 * index as a place to insert if t is smaller and insertion comes inside the array,
* 2c) 0 if the insertion index is 0
**************************************************/
template <class T>
int Set <T>::searchFor(T t) 
{
	/* the item is smaller than the first in the set or bigger than the last in the set
	/* there is nothing to do
	 */
	if (t < _data[0])
		return 0;
	if (t > _data[_numItems - 1])
		return _numItems;

	// binary search
	int begin = 0;
	int end = _numItems - 1;
	int middle = 0;

	while (begin <= end)
	{
		middle = (begin + end) / 2;
		if (t == _data[middle])
			return middle;
		// both conditions check if the item comes to insert between
		// middle and middle - 1
		if (t < _data[middle])
		{
			if (t == _data[middle - 1])
				return middle - 1;
			else if (t > _data[middle - 1])
				return -1 * middle;
			else
				end = middle - 1;
		}
		// middle and middle + 1
		else
		{
			if (t == _data[middle + 1])
				return middle + 1;
			else if (t < _data[middle + 1])
				return -1 * (middle + 1);
			else
				begin = middle + 1;
		}
	}
}

/***************************************************
* SET :: FIND
* Find an item in the set
**************************************************/
template <class T>
SetIterator <T> Set <T>::find(T t)
{
	int index = searchFor(t);

	// check the 0 index before doing anything else
	if (index == 0 && _data[index] == t)
		return _data; 
	
	// the item is found
	if (index > 0 && index < _numItems)
		return _data + index; 

	// the item is not found
	if (index <= 0 || index == _numItems)
		return Set::end();
}

/***************************************************
* SET :: ERASE
* Erase an item in the set (shift down the elements of the set)
**************************************************/
template <class T>
void Set <T>::erase(SetIterator <T> iterator)
{
	SetIterator <T> firstItem = iterator;
	SetIterator <T> nextItem = ++iterator; 

	for (firstItem; nextItem != end(); ++firstItem)
	{
		*firstItem = *nextItem;
		nextItem++;
	}

	// decrease the Set by one number of items
	_numItems--;
}

/***************************************************
* SET :: INTERSECTION
* Instantiate and return a new set -- elements have to be in both this and rhs 
**************************************************/
template <class T>
Set <T> Set <T>::operator&&(Set <T> rhs)
{
	Set <T> newSet;
	int index1 = 0;
	int index2 = 0;

	while (index1 < _numItems || index2 < rhs._numItems)
	{
		// this set is empty, return the empty set
		if (index1 == _numItems)
			return newSet;
		// rhs set is empty, return the empty set
		else if (index2 == rhs._numItems)
			return newSet;
		// the sets are not empty
		// 1) this == rhs, insert into the new set
		else if (_data[index1] == rhs._data[index2])
		{
			newSet.insert(_data[index1]);
			index1++;
			index2++;
		}
		// 2) this < rhs, increment this and skip
		else if (_data[index1] < rhs._data[index2])
			index1++;
		// 3) this > rhs, increment rhs and skip
		else if (_data[index1] > rhs._data[index2])
			index2++;
	}

	return newSet;
}

/***************************************************
* SET :: UNION
* Instantiate and return a new set -- elements have to be in one of either this or rhs  
**************************************************/
template <class T>
Set <T> Set <T>::operator||(Set <T> rhs)
{
	Set <T> newSet;
	int index1 = 0;
	int index2 = 0;

	while (index1 < _numItems || index2 < rhs._numItems)
	{
		// this set is empty, return the rhs set
		if (index1 == _numItems)
			newSet.insert(rhs._data[index2++]);
		// rhs set is empty, return this set
		else if (index2 == rhs._numItems)
			newSet.insert(_data[index1++]);
		// the sets are not empty
		// 1) this == rhs
		else if (_data[index1] == rhs._data[index2])
		{
			newSet.insert(_data[index1]);
			index1++;
			index2++;
		}
		// 2) this < rhs
		else if (_data[index1] < rhs._data[index2])
			newSet.insert(_data[index1++]);
		// 3) this > rhs
		else if (_data[index1] > rhs._data[index2])
			newSet.insert(rhs._data[index2++]);
	}

	return newSet;
}

#endif // SET_H

