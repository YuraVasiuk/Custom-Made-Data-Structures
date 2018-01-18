/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
* Author:
*    Brother Ercanbrack

* Summary: 
*   This is a driver program for showing the heap and merge sorts
************************************************************************/

#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>        // for CIN and COUT
#include <cstring>         // for strcmp
#include <iomanip>         // for SETW
#include "heap.h"
#include "merge.h"

using namespace std;


/**********************************************************************
 * MAIN
 * Get the sort name and filename from the command line.
 * call the appropriate sort to sort the data contained in the file.
 ***********************************************************************/
int main(int argc, const char* argv[])
{

	string programName;
	string sortName;
	string fileName;

   if (argc < 3)
   {
      cout << "Usage: programName sortName fileName" << endl;
	  cin >> programName;
	  cin >> sortName;
	  cin >> fileName;
   }
   //else
   //{
      if (sortName == "heap"/*strcmp(argv[1], "heap") == 0*/)
      {
		  fileName = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week11_HeapMergeSorts/assign11_test1.in";
         // read the file into a vector
		  vector <int> myVector;
		  int data;

		  ifstream fin(fileName.c_str());
		  if (fin.fail())
		  {
			  cout << "Could not read the file " << fileName << endl;
		  }

		  myVector.push_back(-11);
		  while (fin >> data)
		  {
			  myVector.push_back(data);
		  }

		  fin.close();

         // call your heapsort passing the vector as a parameter
		  heapSort(myVector);

         // output the sorted vector.
		  for (vector<int>::iterator it = ++myVector.begin(); it != myVector.end(); it++)
			  cout << setw(3) << *it;
		  cout << endl;
      }
      else if (sortName == "merge"/*strcmp(argv[1], "merge") == 0*/)
      {
		  fileName = "C:/Users/Yura/Desktop/BYUI/5.2016 Spring/CS 235/Visual Studio assignments/week11_HeapMergeSorts/assign11_test2.in";
         // read the file into a linked list
		  list <int> myList;
		  int data;

		  ifstream fin(fileName.c_str());
		  if (fin.fail())
		  {
			  cout << "Could not read the file " << fileName << endl;
		  }

		  while (fin >> data)
		  {
			  myList.push_back(data);
		  }

		  fin.close();
         // call your merge sort
		  mergeSort(myList);

         // output the sorted linked list
		  for (list<int>::iterator it = myList.begin(); it != myList.end(); it++)
			  cout << setw(3) << *it;
      }
      else
      {
         cout << "\nInvalid sort name - must be 'heap' or 'merge'" << endl;
      }
   //}

   system("pause");
   return 0;
}
