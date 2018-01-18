/***********************************************************************
* Header:
*    Big Number
* Summary:
*    This class will be used for calculating big Fibonacci numbers.
*    I need to overload +, =, and << operators
* Author
*    Yura Vasiuk
************************************************************************/

#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include "list.h"
#include <iostream>
using namespace std;

/************************************************
* BIGNUMBER
*************************************************/
class BigNumber
{
public:
	// default constructor
	BigNumber() {}

	// non-default constructor
	BigNumber(int num) { myNumber.push_front(num); }

	// operator = (assign rhs big number to the lhs big number)
	Node<int> * & operator=(BigNumber rhs)
	{
		this->myNumber.getHead() = rhs.myNumber.getHead();
		return this->myNumber.getHead();
	}

	// operator + (add two big numbers, return the new big number)
	BigNumber & operator+(BigNumber rhs);

	// operator << (display the big number accordingly to the Test Bed requirements)
	friend ostream & operator<<(ostream & out, BigNumber rhs);

private:
	List<int> myNumber;
};

/***************************************************
* BIGNUMBER :: ADDITION OPERATOR
* Add one big number to another
**************************************************/
BigNumber & BigNumber::operator+(BigNumber rhs) 
{
	BigNumber theSum = BigNumber(0);
	int sum = 0;
	int keep = 0;
	int carry = 0;
	ListIterator<int> itTHIS = this->myNumber.rbegin();
	ListIterator<int> itRHS = rhs.myNumber.rbegin();
	
	while (itTHIS != NULL || itRHS != NULL)
	{
		keep = 0;
		sum = *itTHIS + *itRHS + carry;
		if (sum > 999)
		{
			keep %= 1000;
			carry = keep / 1000;
		}
		else
		{
			keep = sum;
			carry = 0;
		}
		theSum.myNumber.push_front(keep);
		// move the iterators
		--itTHIS;
		--itRHS;
	}
	// the last addition
	if (itTHIS == NULL && itRHS != NULL)
	{
		keep = *itRHS + carry;
		theSum.myNumber.push_front(keep);
		--itTHIS;
	}
	if (itRHS == NULL && itTHIS != NULL)
	{
		keep = *itTHIS + carry;
		theSum.myNumber.push_front(keep);
		--itRHS;
	}
	
	// keep going if there data to push
	while (itTHIS != NULL)
	{
		keep = *itTHIS;
		theSum.myNumber.push_front(keep);
		--itTHIS;
	}
	while (itRHS != NULL)
	{
		keep = *itRHS;
		theSum.myNumber.push_front(keep);
		--itRHS;
	}

	return theSum;
};

/***************************************************
* BIGNUMBER :: OUTPUT OPERATOR
* Output the big number
**************************************************/
ostream & operator<<(ostream & out, BigNumber rhs) 
{ 
	ListIterator<int> it = rhs.myNumber.begin();

	while (it != NULL)
	{
		out << *it;
		--it;
		if (it != NULL)
			out << ", ";
	}
	
	return out;
};

#endif // BIGNUMBER_H