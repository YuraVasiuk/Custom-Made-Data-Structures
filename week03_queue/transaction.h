/***********************************************************************
* Header:
*    TRANSACTION
* Summary:
*    This will represent the data and operations of a transaction
* Author
*    Yurii Vasiuk
************************************************************************/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include <iostream>    // for ISTREAM and OSTREAM
using namespace std;

class Transaction
{
public:
	Transaction() {}
	//Transaction(int shares, Dollars price) : _shares(shares), _price(price) {}
	void display() { cout << _shares << " shares at " << _price << endl; }
	int & getShares() { return _shares; }
	Dollars & getPrice() { return _price; }
	void setShares(int shares) { _shares = shares; }
	void setPrice(Dollars price) { _price = price; }
private:
	int _shares;
	Dollars _price;
};

#endif // TRANSACTION_H