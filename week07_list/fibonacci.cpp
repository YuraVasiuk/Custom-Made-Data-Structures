/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "bigNumber.h"   // for big number class
using namespace std;

/************************************************
* CALCULATEFIBONACCI
* Calculate and return the passed Fibonacci number
***********************************************/
int calculateFibonacci(int num)
{
	int fibonacci = 0;
	int temp1 = 0;
	int temp2 = 1;

	for (int i = 1; i <= num; i++)
	{
		if (i == 1)
			fibonacci = 1;
		else
		{
			fibonacci = temp1 + temp2;
			temp1 = temp2;
			temp2 = fibonacci;
		}
	}

	return fibonacci;
}

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   for (int i = 1; i <= number; i++)
	   cout << "\t" << calculateFibonacci(i) << endl;

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   cout << "\t" << calculateFibonacci(number) << endl;
}




