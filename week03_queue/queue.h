/***********************************************************************
* Header:
*    Queue
* Summary:
*    Custome made queue, analogous to the STD queue.
*    (the class is implemented with size and capacity,
*     and with back pointing at the next element after the last one)
* Author
*    Yura Vasiuk
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

/************************************************
* QUEUE
* Custom made queue
***********************************************/
template <typename T>
class Queue
{
public:
	// default constructor : empty and kinda useless
	Queue() : _numItems(0), _capacity(0), _front(0), _back(0), _data(0x00000000) {} // done

	// copy constructor : copy it
	Queue(const Queue & rhs) throw (const char *);

	// non-default constructor : pre-allocate
	Queue(int _capacity) throw (const char *);

	// destructor : free everything
	~Queue()        { if (_capacity) delete[] _data; }                // done 

	// assignment operator
	Queue <T> & operator=(const Queue <T> & rhs) throw (const char *);

	// is the queue currently empty
	bool empty() const  { return _numItems == 0; }                  // done

	// remove all the items from the container
	void clear()        { _numItems = 0; _front = 0; _back = 0; }   // done

	// how many items are currently in the queue?
	int size() const    { return _numItems; }                       // done

	// what is the capasity?
	int capacity() const { return _capacity; }                      // done

	// add an item to the end of the queue
	void push(const T & t) throw (const char *);

	// remove an element from the beginning of the queue
	void pop() throw (const char *);

	// access to the first element
	T & front() throw (const char *);

	// access to the last element
	T & back() throw (const char *);


private:
	T * _data;          // dynamically allocated array of T
	int _front;         // the index of the first element 
	int _back;          // the index of the next after the last element
	int _numItems;      // how many items are currently in the Container?
	int _capacity;      // how many items can I put on the Container before full?

	// reallocate (this work on the current object) 
	void realloc();
};

/**********************************************
* QUEUE : NON-DEFAULT CONSTRUCTOR
* Preallocate the queue to "capacity"
**********************************************/
template <typename T>
Queue <T>::Queue(int capacity) throw (const char *)
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
* QUEUE :: COPY CONSTRUCTOR
*******************************************/
template <typename T>
Queue <T>::Queue(const Queue <T> & rhs) throw (const char *)
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
* QUEUE :: ASSIGNMENT OPERATOR
* Copy items from one queue to another.  Return the new queue by reference!!
*******************************************/
template <typename T>
Queue <T> & Queue <T>::operator=(const Queue <T> & rhs) throw (const char *)
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
* QUEUE :: REALLOC
* This reallocates the current object to a twice bigger (tor using in the push())
*******************************************/
template <typename T>
void Queue <T>::realloc()
{
	// temporary holders
	T* temp = _data;
	int tempCapacity = _capacity;

	// allocate a new queue
	_capacity *= 2;
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
		_data[i] = temp[j];
	}

	// free the temp memory
	delete[] temp;

	// assign front and back of the new queue
	_front = 0;
	_back = _numItems;
}

/***************************************************
* QUEUE :: PUSH
* Push an item on the end of the queue
**************************************************/
template <typename T>
void Queue <T>::push(const T & t) throw (const char *)
{
	if (_capacity == 0) // case 1 (0 capacity)
	{
		_capacity = 2;
		//_front = 0;
		//_back = 0;
		_data = new T[_capacity];
		_data[_back++] = t;
		_numItems++;
	}
	else                // case 2
	{
		if (_capacity == _numItems)
			realloc();
		_data[_back] = t;
		_back = (_back + 1) % _capacity;
		_numItems++;
	}
}

/***************************************************
* QUEUE :: POP
* Pop an item from the beginning of the queue
**************************************************/
template <typename T>
void Queue <T>::pop() throw (const char *)
{
	if (empty())
		throw "ERROR: attempting to pop from an empty queue";
	else
	{
		_front = (_front + 1) % _capacity;
		_numItems--;
	}
}

/***************************************************
* QUEUE :: FRONT
* Return an item from the beginning of the queue
**************************************************/
template <typename T>
T & Queue <T>::front() throw (const char *)
{
	if (empty())
		throw "ERROR: attempting to access an item in an empty queue";
	else
		return _data[_front];
}

/***************************************************
* QUEUE :: BACK
* Return an item from the end of the queue
**************************************************/
template <typename T>
T & Queue <T>::back() throw (const char *)
{
	if (empty())
		throw "ERROR: attempting to access an item in an empty queue";
	else
		return _data[_back];
}

#endif // QUEUE_H
