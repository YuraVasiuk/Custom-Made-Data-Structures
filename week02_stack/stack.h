/***********************************************************************
* Header:
*    Stack
* Summary:
*    Custom made Stack, analofous to the STD stack.
*
* Author
*    Br. Helfrich, Yurii Vasiuk
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>

/************************************************
* STACK
* A class that holds stuff
***********************************************/
template <typename T>
class Stack
{
public:
	// default constructor : empty and kinda useless
	Stack() : _top(-1), _capacity(0), _data(0x00000000) {} //done

	// copy constructor : copy it
	Stack(const Stack & rhs) throw (const char *); //done

	// non-default constructor : pre-allocate
	Stack(int capacity) throw (const char *); //done

	// destructor : free everything
	~Stack()        { if (_capacity) delete[] _data; } //done

	// copy data from one stack to another
	Stack <T> & operator=(const Stack <T> & rhs) throw (const char *); //done

	// is the stack currently empty
	bool empty() const  { return _top == -1; } //done

	// how many items are currently in the stack?
	int size() const    { return _top + 1; } //done

	// return the current capasity of the stack
	int capacity() const { return _capacity; } //done

	// add an item to the stack
	void push(const T & t) throw (const char *); //done

	// remove an item from the end of the stack
	void pop() throw (const char *); //done

	// return the item that is at the end of the stack
	T & top() throw (const char *);

private:
	T * _data;          // dynamically allocated array of T
	int _top;      // how many items are currently in the Stack?
	int _capacity;      // how many items can I put on the Stack before full?
};


/*******************************************
* STACK :: COPY CONSTRUCTOR
*******************************************/
template <typename T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
	assert(rhs._capacity >= -1);

	// do nothing if there is nothing to do
	if (rhs._capacity == 0)
	{
		_capacity = 0;
		_top = -1;
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

	// copy over the stuff
	assert(rhs._top >= -1 && rhs._top < rhs._capacity);
	_capacity = rhs._capacity;
	_top = rhs._top;
	for (int i = 0; i <= _top; i++)
		_data[i] = rhs._data[i];
}

/**********************************************
* STACK : NON-DEFAULT CONSTRUCTOR
* Preallocate the stack to "capacity"
**********************************************/
template <typename T>
Stack <T> :: Stack(int capacity) throw (const char *)
{
	assert(capacity >= 0);

	// do nothing if there is nothing to do
	if (capacity == 0)
	{
		_capacity = 0;
		_top = -1;
		_data = 0x00000000;
		return;
	}

	// assign capacity and numItems
	_capacity = capacity;
	_top = -1;
	// allocate
	try
	{
		_data = new T[capacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

}

/*******************************************
* STACK :: ASSIGNMENT OPERATOR
* Copy items from one stack to another.  Return the new stack by reference!!
*******************************************/
template <typename T>
Stack <T> & Stack <T> :: operator=(const Stack <T> & rhs) throw (const char *)
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
			throw "ERROR: Unable to allocate buffer";
		}
	}

	// copy over the stuff
	assert(rhs._top >= -1 && rhs._top < rhs._capacity);
	_capacity = rhs._capacity;
	_top = rhs._top;
	for (int i = 0; i <= _top; i++)
		_data[i] = rhs._data[i];

	// the rest needs to be filled with the default value for T
	for (int i = (_top + 1); i < _capacity; i++)
		_data[i] = T();

	return *this;
}

/***************************************************
* STACK :: PUSH
* Push an item on the top of the stack
**************************************************/
template <typename T>
void Stack <T> :: push(const T & t) throw (const char *)
{
	if (_capacity == 0) // case 1 (0 capacity)
	{ 
		_capacity = 1;
		_top = 0;
		_data = new T[_capacity];
		_data[_top] = t;
	}
	else               // case 2 (more than 0 capacity)
	{
		if (_capacity == (_top + 1))
		{
			// temporary holder
			T* temp = _data;
			// double the vector's capacity
			try
			{
				_capacity *= 2;
				_data = new T[_capacity];
				// copy the content of the temp into the newly allocated vector
				for (int i = 0; i <= _top; i++)
					_data[i] = temp[i];
				// free the temp memory
				delete[] temp;
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: Unable to allocate a new buffer for Stack";
			}
		}
		// the capacity has been handled; add an item to the end
		_data[++_top] = t;
	}
}

/***************************************************
* STACK :: POP
* Remove an item from the end of the stack
**************************************************/
template <typename T>
void Stack <T> :: pop() throw (const char *)
{
	if (_top == -1)
		throw "ERROR: Unable to pop from an empty Stack";
	else
		_top--;
}

/***************************************************
* STACK :: TOP
* Return an item from the top of the stack
**************************************************/
template <typename T>
T & Stack <T> ::top() throw (const char *)
{
	if (_top == -1)
		throw "ERROR: Unable to reference the element from an empty Stack";
	else
		return _data[_top];
}

#endif // CONTAINER_H
