/***********************************************************************
* Header:
*    Deque
* Summary:
*    Custome made deque, analogous to the STD deque.
*    (the class is implemented with size and capacity,
*     and with back pointing at the next element after the last one)
* Author
*    Yura Vasiuk
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

/************************************************
* DEQUE
* Custom made deque
***********************************************/
template <typename T>
class Deque
{
public:
	// default constructor : empty and kinda useless
	Deque() : _numItems(0), _capacity(0), _front(0), _back(0), _data(0x00000000) {} // done

	// copy constructor : copy it
	Deque(const Deque & rhs) throw (const char *);                    // done

	// non-default constructor : pre-allocate
	Deque(int _capacity) throw (const char *);                        // done

	// destructor : free everything
	~Deque()        { if (_capacity) delete[] _data; }                // done 

	// assignment operator
	Deque <T> & operator=(const Deque <T> & rhs) throw (const char *); // done

	// is the deque currently empty
	bool empty() const  { return _numItems == 0; }                    // done

	// remove all the items from the deque
	void clear()        { _numItems = 0; _front = 0; _back = 0; }     // done

	// how many items are currently in the deque?
	int size() const    { return _numItems; }                         // done

	// what is the capasity?
	int capacity() const { return _capacity; }                        // done

	// add an item to the end of the deque
	void push_back(const T & t) throw (const char *);                 // 

	// add an item to the beggining of the deque
	void push_front(const T & t) throw (const char *);                //

	// remove an element from the beginning of the deque
	void pop_front() throw (const char *);                            //

	// remove an element from the end of the deque
	void pop_back() throw (const char *);                             //

	// access to the first element
	T & front() throw (const char *);                                 //

	// access to the last element
	T & back() throw (const char *);                                  //


private:
	T * _data;          // dynamically allocated array of T
	int _front;         // the index of the first element 
	int _back;          // the index of the next after the last element (exept when _numItems == 0)
	int _numItems;      // how many items are currently in the Container?
	int _capacity;      // how many items can I put on the Container before full?

	// reallocate (this works on the current object) 
	void realloc();
};

/**********************************************
* DEQUE : NON-DEFAULT CONSTRUCTOR
* Preallocate the deque to "capacity"
**********************************************/
template <typename T>
Deque <T>::Deque(int capacity) throw (const char *)
{
	assert(capacity >= 0);

	// front and back do not depend on the capacity
	_front = _back = 0;

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
* DEQUE :: COPY CONSTRUCTOR
*******************************************/
template <typename T>
Deque <T>::Deque(const Deque <T> & rhs) throw (const char *)
{
	assert(rhs._capacity >= 0);

	// do nothing if there is nothing to do
	if (rhs._capacity == 0)
	{
		_capacity = _numItems = _front = _back = 0;
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
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the stuff (with shifting the data down to front = 0)
	assert(rhs._numItems >= 0 && rhs._numItems <= rhs._capacity);
	_capacity = rhs._capacity;
	_numItems = rhs._numItems;
	// copy the elements
	int j = rhs._front;
	for (int i = 0; i < _numItems; i++, j = (j + 1) % _capacity)
	{
		_data[i] = rhs._data[j];
	}

	// assign front and back of the new queue
	_front = 0;
	_back = _numItems;
}

/*******************************************
* DEQUE :: ASSIGNMENT OPERATOR
* Copy items from one deque to another.  Return the new dequeue by reference!!
*******************************************/
template <typename T>
Deque <T> & Deque <T>::operator=(const Deque <T> & rhs) throw (const char *)
{
	assert(rhs._capacity >= 0);

	// attempt to allocate in case the new object is smaller than the old one
	if (_capacity < rhs._capacity)
	{
		try
		{
			delete[] _data;  // prevents memory leak!!!
			_data = new T[rhs._capacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}
	}

	// copy over the stuff (with shifting the data down to front = 0)
	assert(rhs._numItems >= 0 && rhs._numItems <= rhs._capacity);
	_capacity = rhs._capacity;
	_numItems = rhs._numItems;
	// copy the elements
	int j = rhs._front;
	for (int i = 0; i < _numItems; i++, j = (j + 1) % _capacity)
	{
		_data[i] = rhs._data[j];
	}

	// assign front and back of the new queue
	_front = 0;
	_back = _numItems;

	return *this;
}

/*******************************************
* DEQUE :: REALLOC
* This reallocates the current object to a twice bigger (tor using in the push())
*******************************************/
template <typename T>
void Deque <T>::realloc()
{
	if (_capacity == 0)
	{
		_capacity = 1;
		_data = new T[_capacity];
	}
	else
	{
		// temporary
		T * _temp = _data;
		int tempCapacity = _capacity;
		// handle capacity
		_capacity *= 2;
		// allocate the new array
		try
		{
			_data = new T[_capacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer for queue";
		}

		// copy the elements
		int j = _front;
		for (int i = 0; i < _numItems; i++, j = (j + 1) % tempCapacity)
		{
			_data[i] = _temp[j];
		}

		// free the old memory
		delete[] _temp;

		// assign front and back of the new queue
		_front = 0;
		_back = _numItems;
	}
}

/***************************************************
* DEQUE :: PUSH_BACK
* Push an item on the end of the deque
**************************************************/
template <typename T>
void Deque <T>::push_back(const T & t) throw (const char *)
{
	if (_capacity == _numItems)
		realloc();
	_data[_back] = t;
	_back = (_back + 1) % _capacity;
	_numItems++;
}

/***************************************************
* DEQUE :: PUSH_FRONT
* Push an item on the beginning of the deque
**************************************************/
template <typename T>
void Deque <T>::push_front(const T & t) throw (const char *)
{
	if (_capacity == _numItems)
		realloc();
	// move the front
	if (_front == 0)
		_front = _capacity - 1;
	else
		_front--;
	// push (assign a value to the new front)
	_data[_front] = t;
	_numItems++;
}

/***************************************************
* DEQUE :: POP_FRONT
* Pop an item from the beginning of the deque
**************************************************/
template <typename T>
void Deque <T>::pop_front() throw (const char *)
{
	if (empty())
		throw "ERROR: unable to pop from the front of empty deque";
	else
	{
		_front = (_front + 1) % _capacity;
		_numItems--;
	}
}

/***************************************************
* DEQUE :: POP_BACK
* Pop an item from the beginning of the deque
**************************************************/
template <typename T>
void Deque <T>::pop_back() throw (const char *)
{
	if (empty())
		throw "ERROR: unable to pop from the back of empty deque";
	else
	{
		if (_back > 0)
			_back--;
		else
			_back = _capacity - 1;
		_numItems--;
	}
}

/***************************************************
* DEQUE :: FRONT
* Return an item from the beginning of the deque
**************************************************/
template <typename T>
T & Deque <T>::front() throw (const char *)
{
	if (empty())
		throw "ERROR: unable to access data from an empty deque";
	else
		return _data[_front];
}

/***************************************************
* DEQUE :: BACK
* Return an item from the end of the deque
**************************************************/
// ?????????bug
template <typename T>
T & Deque <T>::back() throw (const char *)
{
	if (empty())
		throw "ERROR: unable to access data from an empty deque";
	if (_back > 0)
		return _data[_back - 1];
	else
		return _data[_capacity - 1];
}

#endif // QUEUE_H
