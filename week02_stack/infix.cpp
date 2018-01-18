/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Yurii Vasiuk
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

// i added the libraries
//#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;
//using namespace boost;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
    string postfix;
	
	char token, topToken;
	Stack <char> ops;
	const string BLANK = " ";
	postfix.append(BLANK);

	for (int i = 0; i < infix.length(); i++)
	{
		token = infix[i];
	
		switch (token)
		{
		// append blanks
		case ' ':
			if (postfix[postfix.length() - 1] != ' ')
				postfix.append(BLANK);
			break;
		// handle parenthesis
		case '(':
			ops.push(token);
			break;
		case ')':
			while (true)
			{
				topToken = ops.top();
				ops.pop();
				if (topToken == '(')
					break;
				postfix.append(BLANK);
				postfix += topToken;
			}
		// handle operators
		case '^':                      // 1
			ops.push(token);
			break;
		case '*': case '/': case '%':  // 2
			while (true)
			{
				if (ops.empty() || ops.top() == '(' ||
					ops.top() == '+' || ops.top() == '-')
				{
					ops.push(token);
					break;
				}
				else
				{
					topToken = ops.top();
					ops.pop();
					if (postfix[postfix.length() - 1] != ' ')
						postfix.append(BLANK);
					postfix += topToken;
				}
			}
			break;
		case '+': case '-':            // 3   
			while (true)
			{
				if (ops.empty() || ops.top() == '(')
				{
					ops.push(token);
					break;
				}
				else
				{
					topToken = ops.top();
					ops.pop();
					if (postfix[postfix.length() - 1] != ' ')
						postfix.append(BLANK);
					postfix += topToken;
				}
			}
			break;
		// handle operands
		default:
			postfix += token;
			break;
		}
	}

	// pop remaining on the stack operators
	while (true)
	{
		if (ops.empty())
			break;
		topToken = ops.top();
		ops.pop();
		postfix.append(BLANK);
		if (topToken != ')')
			postfix += topToken;
	}

    return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
