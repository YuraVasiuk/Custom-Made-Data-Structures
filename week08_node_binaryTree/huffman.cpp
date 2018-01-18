/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Yurii Vasiuk
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype
using namespace std;

// the prototipes
BinaryNode<Pair<string, float>> * buildHuffmanTree(deque<Pair<string, float>> & pairs);
string & makeHuffmanCode(BinaryNode<Pair<string, float>> * & root, string code, string & table);

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(string fileName)
{
	// temporary, for using in the Visual Studio only
	//fileName = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week08_node_binaryTree/huffman1.txt";
	fileName = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week08_node_binaryTree/huffman2.txt";
	//fileName = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week08_node_binaryTree/huffman3.txt";
	
	// the container for reading data from the file
	Pair<string, float> thePair = Pair<string, float>();
	// the container to store the pairs
	deque<Pair<string, float>> pairs;
	
	// read from the file
	ifstream fin(fileName);
	if (fin.fail())
	{
		cout << "Could not open the file " << fileName << endl;
		return;
	}
	while (fin >> thePair)
	{
		pairs.push_back(thePair);
	}
	// finish with the file reading
	fin.close();

	// sort the deque of pairs by the frequency
	sort(pairs.begin(), pairs.end());

	// build the tree
	BinaryNode<Pair<string, float>> *theHuffmanTree = new BinaryNode<Pair<string, float>>();
	theHuffmanTree = buildHuffmanTree(pairs);
	
	// make the Huffman code
	// the containers for 1 string of code and the whole table of code strings
	string code = "";
	string table;
	makeHuffmanCode(theHuffmanTree, code, table);

	// display the Huffman code
	cout << table;

    return;
}

// BUILD THE TREE
BinaryNode<Pair<string, float>> * buildHuffmanTree(deque<Pair<string, float>> & pairs0)
{
	// transform all pairs into binary nodes
	deque<BinaryNode<Pair<string, float>> *> pairs;
	BinaryNode<Pair<string, float>> * p;
	for (deque<Pair<string, float>>::iterator it = pairs0.begin(); 
		it < pairs0.end(); it++)
	{
		p = new BinaryNode<Pair<string, float>>(*it);
		pairs.push_back(p);
	}
	
	/************************************************************************
	* the binary node pairs are in the sorted deque
	* build the tree
	************************************************************************/
	
	// the initial root of the tree
	BinaryNode<Pair<string, float>> *root = new BinaryNode<Pair<string, float>>();
	
	// the iterators pointing to the pairs in the deque
	deque<BinaryNode<Pair<string, float>> * >::iterator it = pairs.begin();
	deque<BinaryNode<Pair<string, float>> * >::iterator itTemp = pairs.begin();
	
	// building the tree
	while (pairs.size() > 1)
	{
		// finish all leaves and merge the subtrees
		if (((*it)->data.getFirst() != " " && (*(it + 1))->data.getFirst() != " ") ||
			(*it)->data.getFirst() == " " && (*(it + 1))->data.getFirst() == " ")
		{
			// make and merge subtrees
			root = new BinaryNode<Pair<string, float>>();
			root->addLeft(*it);
			root->addRight(*(it + 1));
			root->data.first = " ";
			root->data.second = ((*it)->data.getSecond()) + (*(it + 1))->data.getSecond();
			// handle the deque of pairs
			pairs.pop_front();
			pairs.pop_front();
			pairs.push_back(root);
			it = pairs.begin();
		}
		// in case one leaf is left first
		else if ((*it)->data.getFirst() != " " && (*(it + 1))->data.getFirst() == " ")
		{
			// move into the end of the deque
			itTemp = it;
			pairs.push_back(*itTemp);
			pairs.pop_front();
			it = pairs.begin();
		}
		// in case one leaf is left last in the deque
		else if ((*it)->data.getFirst() == " " && (*(it + 1))->data.getFirst() != " ")
		{
			// make a subtree
			root = new BinaryNode<Pair<string, float>>();
			root->addLeft(*it);
			root->addRight(*(it + 1));
			root->data.first = " ";
			root->data.second = ((*it)->data.getSecond()) + (*(it + 1))->data.getSecond();
			// handle the deque of pairs
			pairs.pop_front();
			pairs.pop_front();
		}
	}
	
	return root;
}

// MAKE CODE BASED UPON THE TREE
string & makeHuffmanCode
(BinaryNode<Pair<string, float>> * & root, string code, string & table)
{
	if (root->pLeft == NULL && root->pRight == NULL)
	{
		table = table + root->data.getFirst() + " = " + code + "\n";
		cout << "l: " << root->data.getFirst() << root->data.getSecond() << endl;
	}
	else
	{
		makeHuffmanCode(root->pLeft, code += "0", table);
		makeHuffmanCode(root->pRight, code += "1", table);
	}

	return table;
}


