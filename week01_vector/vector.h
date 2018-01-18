/***********************************************************************
* Header:
*    Vector
* Summary:
*    Custom made vector class (analog to the STD Vector)
*    Custom made iterator 
*
* Author
*    Yurii Vasiuk
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * VECTOR
 * The custom made class analogous to the STD Vector
 ***********************************************/
template <typename T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : _numItems(0), _capacity(0), _data(0x00000000) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int _capacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (_capacity) delete [] _data; }
   
   // is the vector currently empty
   bool empty() const  { return _numItems == 0;         }

   // remove all the items from the vector
   void clear()        { _numItems = 0;                 }

   // how many items are currently in the vector?
   int size() const    { return _numItems;              }

   // add an item to the vector
   void insert(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(_data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(_data + _numItems);}

   // MY METHODS-------------------------------------------------------------
   
   // return the current capasity of the vector
   int capacity() const { return _capacity; }

   // copy data from one vector to another
   Vector <T> & operator = (const Vector <T> & rhs) throw (const char *);

   // return a value from within the vector (return by reference)
   T & operator[](int index) throw (const char *);
   const T & operator[](int index) const throw (const char *);

   // return a value from within the vector (return by value)
   T operator()(int index) throw (const char *);

   // add an element in the end of the vector
   void push_back(const T &t) throw (const char *);

   // END OF MY METHODS------------------------------------------------------
   
private:
   T * _data;          // dynamically allocated array of T
   int _numItems;      // how many items are currently in the Container?
   int _capacity;      // how many items can I put on the Container before full?
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through Vector
 *************************************************/
template <typename T>
class VectorIterator
{
  public:
   // default constructor
  VectorIterator() : p(0x00000000) {}

   // initialize to direct p to some item
  VectorIterator(T * p) : p(p) {}

   // copy constructor
   VectorIterator(const VectorIterator & rhs) { *this = rhs; }

   // assignment operator
   VectorIterator & operator = (const VectorIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <typename T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
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
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the stuff
   assert(rhs._numItems >= 0 && rhs._numItems <= rhs._capacity);
   _capacity = rhs._capacity;
   _numItems = rhs._numItems;
   for (int i = 0; i < _numItems; i++)
      _data[i] = rhs._data[i];
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <typename T>
Vector <T> :: Vector(int capacity) throw (const char *)
{
   assert(_capacity >= 0);
   
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

// MY METHODS----------------------------------------------------------------

/*******************************************
* VECTOR :: ASSIGNMENT OPERATOR
* Copy items from one vector to another.  Return the new vector by reference!!
*******************************************/
template <typename T>
Vector<T> & Vector<T> :: operator=(const Vector<T> & rhs) throw (const char *)
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

/*******************************************
* VECTOR :: OPERATOR []
* Retrun a value from within the vector.  Return by reference!!
*******************************************/
// non-constant
template <typename T>
T & Vector<T> :: operator[](int index) throw (const char *)
{
	if (index < 0 || index >= _numItems)
		throw "Invalid index";

	return _data[index];
}

// constant
template <typename T>
const T & Vector<T> :: operator[](int index) const throw (const char *)
{
	if (index < 0 || index >= _numItems)
		throw "Invalid index";

	return _data[index];
}

/*******************************************
* VECTOR :: OPERATOR ()
* Retrun a value from within the vector.  Return by velue!!
*******************************************/
template <typename T>
T Vector<T> :: operator()(int index) throw (const char *)
{
	if (index < 0 || index > _numItems)
		throw "Invalid index";

	return _data[index];
}

/***************************************************
* VECTOR :: PUSH_BACK
* Insert an item on the end of the vector
**************************************************/
template <typename T>
void Vector<T> :: push_back(const T &t) throw (const char *)
{
	if (_capacity == 0) // case 1 (0 capacity)
	{
		_capacity = 1;
		_numItems = 1;
		_data = new T[_capacity];
		_data[0] = t;
	}
	else               // case 2 (more than 0 capacity)
	{
		if (_capacity == _numItems)
		{
			// temporary holder
			T* temp = _data;
			// double the vector's capacity
			try
			{
				_capacity *= 2;
				_data = new T[_capacity];
				// copy the content of the temp into the newly allocated vector
				for (int i = 0; i < _numItems; i++)
					_data[i] = temp[i];
				// free the temp memory
				delete[] temp;
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: Unable to allocate a new buffer for vector";
			}
		}
		// the capacity has been handled; add an item to the end
		_data[_numItems++] = t;
	}
}

#endif // VECTOR_H
