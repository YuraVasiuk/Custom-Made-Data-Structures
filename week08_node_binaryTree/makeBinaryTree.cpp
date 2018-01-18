#include "huffman.h"       // for HUFFMAN() prototype
using namespace std;


// BUILD THE TREE
BinaryNode<Pair<string, float>> * & buildHuffmanTree(deque<Pair<string, float>> & pairs)
{
	/************************************************************************
	* the pairs are in the sorted deque
	* build the tree
	************************************************************************/

	// the initial root of the tree
	BinaryNode<Pair<string, float>> *root = new BinaryNode<Pair<string, float>>();
	// this will hold the root temporary
	BinaryNode<Pair<string, float>> *temp = new BinaryNode<Pair<string, float>>();
	// the iterator pointing to the pairs in the array
	deque<Pair<string, float>>::iterator it = pairs.begin();

	// building the tree
	// make left leaf
	BinaryNode<Pair<string, float>> *leftLeaf = new BinaryNode<Pair<string, float>>(*it);
	root->addLeft(leftLeaf);
	// keep making the root and the right leaves
	while (pairs.size() > 2)
	{
		// for the access to the first two pairs
		it = pairs.begin();
		// assine the values of the tree root node 
		root->data.second = (it->getSecond()) + ((++it)->getSecond());
		root->data.first = " ";
		// make the right leaf
		BinaryNode<Pair<string, float>> *rightLeaf =
			new BinaryNode<Pair<string, float>>(*it);
		root->addRight(rightLeaf);
		// make the new root pointing left to the current one 
		temp = root;
		root = new BinaryNode<Pair<string, float>>(temp->data);
		root->addLeft(temp);
		// done with the subtree

		// take care of the deque
		pairs.pop_front();
		pairs.pop_front();
		pairs.push_front(root->data);
	}

	// handle the last pair in the deque
	// iterator to the last pair in the deque
	it = pairs.begin();
	// this is the root for the whole tree
	root = new BinaryNode<Pair<string, float>>();
	// root -- fill the data
	root->data.first = " ";
	root->data.second = (it->getSecond()) + ((++it)->getSecond());
	// make the last right leaf
	BinaryNode<Pair<string, float>> *rightLeaf =
		new BinaryNode<Pair<string, float>>(*it);
	// assign the root pointers to the left and the right leaves
	root->pLeft = temp;
	root->addRight(rightLeaf);
	// the tree is built now ---------------------------------------------

	return root;
}
