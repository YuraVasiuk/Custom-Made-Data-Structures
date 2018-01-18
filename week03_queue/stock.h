/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Yurii Vasiuk
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include "queue.h"     // for QUEUE
#include "transaction.h"
#include <iostream>    // for ISTREAM and OSTREAM
using namespace std;

// the interactive stock buy/sell function
void stocksBuySell();

// my code
class Stock
{
public:
	Stock(){}
	void buyStock(Transaction theTransaction);
	void sellStock(Transaction theTransaction);
	void displayStock();
private:
	// containers for the stock data
	Queue <Transaction> _boughtStock;
	Queue <Transaction> _soldStock;
	Dollars _proceeds;
};
#endif // STOCK_H

