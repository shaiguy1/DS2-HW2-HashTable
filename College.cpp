#include "College.h"
// renamed lst to be more meaningfull, it is now courseList
void College::addCourse()
{
	string name;
	int num;
	cout << "enter course name" << endl;
	cin >> name;
	cout << "enter course id" << endl;
	cin >> num;
	// TODO: Add the course to the courses table
	// course takes in a name and a course ID
	Course newCourse(name, num);
	// inserting into the name we need the number we're using for hashing, the ID
	// and the piece of data we're inserting, newCourse
	courses.insert(num, newCourse);
}

void College::removeCourse()
{
	int num;
	cout << "enter course id" << endl;
	cin >> num;
	// TODO: Remove the course from the course table
	// delete from the hash table based on ID since that's how it was inserted/added in the first place
	courses.remove(num);
}

void College::addStudent()
{
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	list<int> courseList; // every student will take courses,
	// this is a list that will contain all the courses after they are added in the registration method

	// TODO: Insert the student to the students table
	// give the name of the student for the hash to be based on
	// give the data of the student, course list
	students.insert(name, courseList);
}

void College::removeStudent()
{
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	// TODO: Remove the student from the student table
	students.remove(name);
}

void College::registration()
{
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	int num;
	cout << "enter course id" << endl;
	cin >> num;
	try
	{
		// TODO: add the course id (if it exists) to the end of the student's course-list
		// inside the search method, all routes (branchs?) lead to a throw or a return statement
		// if it's a regular return then we found the thing
		// if we reached a throw, this catch block will prevent us from needing to check if the search was bad before adding
		// we will only add if the search was successful
		list<int> courseList = students.search(name);
		courseList.push_back(num);
		students.insert(name, courseList);
	}
	catch (const char *msg)
	{
		cout << msg << endl;
	}
}

void College::removeReg()
{
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	int num;
	cout << "enter course id" << endl;
	cin >> num;
	try
	{
		// TODO: remove the course id (if it exists) from the student's list
		// same logic applies here as in the registration method
		list<int> courseList = students.search(name);
		courseList.remove(num);
		students.insert(name, courseList);
	}
	catch (const char *msg)
	{
		cout << msg << endl;
	}
}

void College::print()
{
	// this method prints all the courses the student is taking
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	try
	{
		// list<int> courseList; //<--old // TODO: fix, so this would be the student's courses lis
		list<int> courseList = students.search(name);
		// now have all the courses a student is taking
		for (int courseID : courseList) // go through each ID in the course list
		{
			// Course c; // TODO: fix
			Course c = courses.search(courseID);
			cout << c.getName() << ' ';
		}

		cout << endl;
	}
	catch (const char *msg)
	{
		cout << msg << endl;
	}
}

void College::printStudentsTable()
{
	students.print();
}

void College::printCoursesTable()
{
	courses.print();
}