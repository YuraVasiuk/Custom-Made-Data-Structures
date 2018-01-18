/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    Yurii Vasiuk
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  2.0 hrs   
*    Actual:     2.0 hrs
*      Opening the file was the most difficult part.
************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
	int matches = 0;
	Card card;
	Set <Card> cards;

	// get the cards
	ifstream fin("/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week05_set/hand.txt");
	if (fin.fail())
	{
		cout << "Could not open the file";
		return ;
	}

	while (!fin.eof())
	{
		fin >> card;
		if (!card.isInvalid())
			cards.insert(card);
	}

	fin.close();

	// play the game
	Card userInput = "";
	SetIterator <Card> found;
	cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
	for (int i = 1; i <= 5; i++)
	{
		cout << "round " << i << ": ";
		cin >> userInput;
		if (cards.find(userInput) != cards.end())
		{
			matches++;
			cards.erase(cards.find(userInput));
			cout << "\tYou got a match!\n";
		}
		else
		{
			cout << "\tGo Fish!\n";
		}
	}

	cout << "You have " << matches << " matches!" << endl;
	cout << "The remaining cards: ";
	for (SetIterator <Card> it = cards.begin(); it != cards.end(); it++)
	{
		if (it != cards.begin())
			cout << ", ";
		cout << *it;
	}
	cout << endl;
   return ;
}
