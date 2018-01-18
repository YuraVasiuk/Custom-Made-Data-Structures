/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Yurii Vasiuk
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
	// instructions
	cout << "This program will allow you to buy and sell stocks. "
		<< "The actions are:\n";
	cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
	cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
	cout << "  display         - Display your current stock portfolio\n";
	cout << "  quit            - Display a final report and quit the program\n";

	// your code here...
	cin.clear();
	cin.ignore(256, '\n');

	// make working objects
	Dollars price;
	Transaction myTransaction;
	Stock myStock;

	// get the user input and put it into the right container
	string input = " ";              // for getting the input
	string command, sharesS, priceS; // temporary holders 
	int shares;                      // converted number of shares
	double priceD;                   // temporary holder

	while (input != "quit")
	{
		// get the user input
		cout << "> ";
		getline(cin, input);

		// parse the input
		command = input.substr(0, input.find(" "));
		if (command == "buy" || command == "sell")
		{
			sharesS = input.substr(input.find(" "), input.find(" "));
			priceS = input.substr(input.find("$") + 1);
		}

		shares = stoi(sharesS);
		priceD = stod(priceS);
		price = priceD;
		myTransaction.setShares(shares);
		myTransaction.setPrice(price);
		// myTransaction.display();  used for debugging

		if (command == "buy")
			myStock.buyStock(myTransaction);
		if (command == "sell")
			myStock.sellStock(myTransaction);
		if (command == "display")
			myStock.displayStock();
	}
}

/***************************************************
* STOCK :: BUYSTOCK
* Add the transation to the transaction queue
**************************************************/
void Stock::buyStock(Transaction theTransaction) 
{
	_boughtStock.push(theTransaction);
}

/***************************************************
* STOCK :: SELLSTOCK
* Subtract the transaction while adding the procceds
**************************************************/
void Stock::sellStock(Transaction theTransaction)
{
	int trShares = theTransaction.getShares();
	Dollars trPrice = theTransaction.getPrice();
	int stShares = _boughtStock.front().getShares();
	Dollars stPrice = _boughtStock.front().getPrice();

	Transaction transactionSold;
	
	// case 1 and 2 -- less than or equal
	if (trShares < stShares || trShares == stShares)
	{
		// calculate the transaction profit
		Dollars profit = 0;
		Dollars oneShareProfit = stPrice - trPrice;
		for (int i = 0; i < trShares; i++)
			profit += oneShareProfit;
		// add to the proceeds
		_proceeds += profit;
		// case 1 -- less
		if (trShares < stShares)
		{
			// subtract the sold shares
			int newShares = stShares - trShares;
			// set the bought and sold queues
			_boughtStock.front().setShares(newShares);
			transactionSold.setShares(trShares);
			transactionSold.setPrice(trPrice);
			_soldStock.push(transactionSold);
		}
		// case 2 -- equal
		if (trShares == stShares)
		{
			_boughtStock.pop();
			_soldStock.push(transactionSold);
		}
	}
	
	// case 3 -- more than
	// !!! to finish
}

/***************************************************
* STOCK :: DISPLAYSTOCK
* Add a transation to the transaction queue
**************************************************/
void Stock::displayStock()
{
	Transaction displayTransaction;
	cout << "Currently held:\n";
	Queue <Transaction> displayQueue(_boughtStock);  // make a copy 
	// use the copy -- display and pop
	while (!displayQueue.empty())
	{
		cout << "\tBought ";
		displayTransaction = _boughtStock.front();
		displayTransaction.display();
		_boughtStock.pop();  // !!! bug in looping and wrong number of shares displayed
	}

	cout << "Sell history:\n";
	// !!! to finish
	cout << "Proceeds: " << _proceeds << endl;
	// !!! to finish
}



