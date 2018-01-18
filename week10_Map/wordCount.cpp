/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Yurii Vasiuk
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include "pair.h"
#include "bst.h"
#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
using namespace std;

void readFile(Map <string, int/*Count*/> & countsMap, const string & fileName);

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
	string filename;
	cout << "What is the filename to be counted? ";
	cin >> filename;
	filename = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week10_Map/bom.txt";
	//filename = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week10_Map/D_C_121.txt";
	//filename = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week10_Map/fruit.txt";



	Map <string, int> countsMap;
	readFile(countsMap, filename);

	string finish = "";
	// I need the iterator to get to the data in pairs
	MapIterator <string, int> it;
	cout << "What word whose frequency is to be found. Type !when done\n";
	// display the number of searched words in my countsMap 
	while (finish != "!")
	{
		cout << "> ";
		cin >> finish;
		it = countsMap.find(finish);
		// the finish word is not in the countsMap
		if (it == countsMap.end() && finish != "!")
			cout << "\t" << finish << " : 0" << endl;
		// the finish word is in the countsMap
		else if (it != countsMap.end() && finish != "!")
			cout << "\t" << finish << " : " << *it << endl;
	}
}

void readFile(Map <string, int> & countsMap, const string & fileName)
{
	ifstream fin(fileName);
	if (fin.fail())
	{
		cout << "Could not read the file " << fileName << endl;
		return;
	}

	string word;
	MapIterator <string, int> it;
	// inserting and counting will be done here
	while (fin >> word)
	{
		if (countsMap.find(word) == countsMap.end())
		{
			countsMap[word] = 1;
		}
		else
		{
			it = countsMap.find(word);
			(*it)++;
		}
	}

	fin.close();
}
