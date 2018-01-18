/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   std::cout << "Every prompt is one minute.  The following input is accepted:\n";
   std::cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   std::cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   std::cout << "\tnone                         : no new request this minute\n";
   std::cout << "\tfinished                     : end simulation\n";

   // your code here

   // container for a signed up student 
   Student newStudent;
   // container for the student that is being served
   Student beingServed;
   // signed up students make a line
   Deque <Student> line;

   string input;
   // inputs will be counted
   int inputNumber = 0;
   // and finished
   bool finish = false;
   // inputs will be split
   string course;
   string name;
   int time;
   
   // everything is done in the while loop
   while (!finish)
   {
	   std::cout << "<" << inputNumber << "> ";
	   cin >> input;
	   // emergency insertion
	   if (input == "!!")          
	   {
		   cin >> course;
		   cin >> name;
		   cin >> time;
		   // a new student just signed up
		   newStudent.setCourse(course);
		   newStudent.setName(name);
		   newStudent.setTime(time);
		   newStudent.setEmergency(true);
		   line.push_front(newStudent);
	   }
	   // subtruct time only from the being served student
	   else if (input == "none")
	   {
		   // just skip, no entry
	   }
	   // finish the simulation
	   else if (input == "finished")
	   {
		   finish = true;
	   }
	   // non-emergency insertion
	   else
	   {
		   course = input;
		   cin >> name;
		   cin >> time;
		   // a new student just signed up
		   newStudent.setCourse(course);
		   newStudent.setName(name);
		   newStudent.setTime(time);
		   newStudent.setEmergency(false);
		   line.push_back(newStudent);
	   }

	   // no time left, get a new currently served and pop him from the line
	   if (beingServed.getTime() == 0 && !line.empty())
	   {
		   beingServed = line.front();
		   line.pop_front();
	   }
	   // show non-emergency student being served
	   if (beingServed.getTime() != 0 && beingServed.getEmergency() == false)
	   {
		   cout << "\tCurrently serving " << beingServed.getName() << " for class "
			   << beingServed.getCourse() << ". Time left: "
			   << beingServed.getTime() << endl;
	   }
	   // show emergency student being served
	   if (beingServed.getTime() != 0 && beingServed.getEmergency() == true)
	   {
		   cout << "\tEmergency for " << beingServed.getName() << " for class "
			   << beingServed.getCourse() << ". Time left: "
			   << beingServed.getTime() << endl;
	   }

	   // last two steps: decrease time for currently served and increase input counts
	   if (beingServed.getTime() > 0)
		   beingServed.decreaseTime();
	   inputNumber++;
   }

   // end
   std::cout << "End of simulation\n";
}


