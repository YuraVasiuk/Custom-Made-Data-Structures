#include <list>
#include <string>
#include <assert.h>

using namespace std;
/****************************************
* HASH
* The parent template hash class 
****************************************/
template <typename T>
class Hash 
{
public:
	// the constructors
	Hash() : numBuckets(0), numElements(0), buckets(NULL) {}
	Hash(int numBuckets) throw (const char *) ;
	Hash(const Hash & rhs) throw (const char *) ;

	// destructor
	~Hash()
	{
		//if (numBuckets != 0)
			//delete[] buckets;
	}

	// is the hash empty?
	bool empty() const
	{ 
		if (numElements == 0)
			return true;
		else
			return false;
	}
	
	// return the array's capacity
	int capacity() const { return numBuckets; }

	// how many elements does the hash have?
	int size() const { return numElements; }

	// clear the content of the hash
	void clear();

	// is the item in the hash?
	bool find(T item) const;

	// insert the item into the hash
	void insert(T item);

	// pure vitual hash function 
	virtual int hash(T & value) const = 0;
	
private:
	int numBuckets;
	int numElements;
	list<T> * buckets;
};

/****************************************
* HASH : NON-DEFAULT CONSTRUCTOR
* Allocate the array of the passed number of list, assign the variables
****************************************/
template <typename T>
Hash<T>::Hash(int numBuckets) throw (const char *)
{
	this->numBuckets = numBuckets;
	numElements = 0;

	try
	{
		buckets = new list<T> [this->numBuckets];
	}
	catch (bad_alloc)
	{
		cout << "ERROR: Unable to allocate memory for the hash.";
	}
}

/****************************************
* HASH : COPY CONSTRUCTOR
* Make a new hash, the same with the passed one
****************************************/
template <typename T>
Hash<T>::Hash(const Hash & rhs) throw (const char *)
{
	// copy the empty hash with no capacity
	if ((rhs.empty() == true) && (rhs.capacity() == 0))
	{
		this->numBuckets = 0; 
		this->numElements = 0; 
		buckets = NULL;
	}
	// copy the empty hash with some capacity
	else if (rhs.empty() == true)
	{
		this->numBuckets = rhs.numBuckets;
		this->numElements = 0;

		try
		{
			buckets = new list<T>[numBuckets];
		}
		catch (bad_alloc)
		{
			cout << "ERROR: Unable to allocate memory for the hash.";
		}
	}
	// copy the hash with some elements
	else
	{
		this->numBuckets = rhs.numBuckets;
		this->numElements = rhs.numElements;

		try
		{
			buckets = new list<T>[numBuckets];
		}
		catch (bad_alloc)
		{
			cout << "ERROR: Unable to allocate memory for the hash.";
		}

		for (int i = 0; i < rhs.numBuckets; i++)
		{
			if (!rhs.buckets[i].empty())
			{
				this->buckets = rhs.buckets;
			}
		}
	}
}

/****************************************
* HASH : CLEAR
* Clear the content of the hash
****************************************/
template <typename T>
void Hash<T>::clear() 
{
	if (!empty())
	{
		for (int i = 0; i < numBuckets; i++)
		{
			if (!buckets[i].empty())
			{
				buckets[i].clear();
			}
		}
	}
}

/****************************************
* HASH : FIND
* Is the element in the hash?
****************************************/
template <typename T>
bool Hash<T>::find(T element) const
{
	if (!empty())
	{
		int index = hash(element);
		for (list<T>::iterator it = buckets[index].begin(); it != buckets[index].end(); it++)
		{
			if (*it == element)
				return true;
		}
	}
	
	return false;
}

/****************************************
* HASH : INSERT
* Insert the element into the hash?
****************************************/
template <typename T>
void Hash<T>::insert(T element) 
{
	int index = hash(element);

	buckets[index].push_back(element);
	numElements++;
}

/****************************************
* SHASH
* A hash of strings : It inherits from HASH class
****************************************/
class SHash : public Hash <string>
{
public:
	SHash(int numBuckets)    throw (const char *) : Hash <string>(numBuckets) {}
	SHash(const SHash & rhs) throw (const char *) : Hash <string>(rhs)        {}

	// hash function for integers is simply to take the modulous
	int hash(string & word) const
	{
		int index = 0;
		int sumLetters = 0;

		for (string::iterator it = word.begin(); it != word.end(); it++)
		{
			sumLetters += static_cast<int>(*it);
		}
		index = sumLetters % capacity();

		assert(index >= 0 && index < 232);

		return index;
	}
};
