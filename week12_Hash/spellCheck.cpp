/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Yurii Vasiuk
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "spellCheck.h"
#include "hash.h"
using namespace std;

/*****************************************
* DISPLAY HASH TABLE
****************************************/
void displayHashTable(const SHash & hash)
{
	for (int i = 0; i < hash.capacity(); i++)
	{
		cout << i; 
		
	}
}
/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
	// read the dictionary into the hash object
	SHash hashedDictionary(232);

	string fileName = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week12_Hash/dictionary.txt";
	ifstream fin(fileName.c_str());
	string word;
	string wordLowCase;

	if (fin.fail())
	{
		cout << "Could not read the file " << fileName << endl;
	}
	
	while (fin >> word)
	{
		hashedDictionary.insert(word);
	}
	
	fin.close();
	// the dictionary is hashed now


	// the spell check
	cout << "What file do you want to check? ";
	cin >> fileName;
	//fileName = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week12_Hash/nephi.txt";
	fileName = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week12_Hash/twoCities.txt";

	// container for the misspelled words
	vector<string> misspelledWords;

	ifstream fin1(fileName.c_str());
	if (fin1.fail())
	{
		cout << "Could not read the file " << fileName << endl;
		return;
	}

	while (fin1 >> word)
	{
		wordLowCase = word;
		transform(wordLowCase.begin(), wordLowCase.end(), wordLowCase.begin(), ::tolower);
		if (!hashedDictionary.find(wordLowCase))
			misspelledWords.push_back(word);
	}

	fin1.close();
	// the misspelled words are in the vector now

	// display the result of the check
	if (misspelledWords.empty())
		cout << "File contains no spelling errors\n";
	else
	{
		cout << "Misspelled: ";
		for (vector<string>::iterator it = misspelledWords.begin(); it != misspelledWords.end(); )
		{
			cout << *it;
			if (++it != misspelledWords.end())
				cout << ", ";
		}
		cout << endl;
	}
}
