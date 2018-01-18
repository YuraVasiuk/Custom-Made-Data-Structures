/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "bnode.h"
#include "pair.h"
#include <iostream>    // for streams
#include <fstream>     // for files
#include <string>      // for strings
#include <deque>       // for deque (in making the tree)
#include <vector>      // for vector (in coding the tree)
#include <algorithm>   // for sort()
using namespace std;

void huffman(string fileName);

#endif // HUFFMAN_h
