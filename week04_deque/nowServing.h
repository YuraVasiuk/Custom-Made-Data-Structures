/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Yura Vasiuk
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE
#include <string>
using namespace std;

// the interactive nowServing program
void nowServing();

// my class for handling students
class Student
{
public:
	Student(): _course(""), _name(""), _time(0), _emergency(false) {}
	// setters
	void setCourse(string course) { _course = course; }
	void setName(string name) { _name = name; }
	void setTime(int time) { _time = time; }
	void setEmergency(bool emergency) { _emergency = emergency; }
	// getters
	string getCourse() { return _course; }
	string getName() { return _name; }
	int getTime() { return _time; }
	int getEmergency() { return _emergency; }
	// 2 methods for using in the application
	void decreaseTime() { _time--; }
	/* NO POINTERS IN THE CLASS. NO NEED TO OVERLOAD, THE DEFAUL ONE WORKS OK!!
	Student & operator=(const Student & rhs)
	{
		_course = rhs._course;
		_name = rhs._name;
		_time = rhs._time;
		_emergency = rhs._emergency;

		return *this;
	}
	*/
private:
	string _course;
	string _name;
	int _time;
	bool _emergency;
};

#endif // NOW_SERVING_H

