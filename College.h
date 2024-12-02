#pragma once
#include <list>
#include "IntHash.h"
#include "StringHash.h"
#include "Course.h"

class College
{
public:
	void addCourse();
	void removeCourse();
	void addStudent();
	void removeStudent();
	void registration();
	void removeReg();
	void print();
	void printStudentsTable();
	void printCoursesTable();
	College(int maxNumOfStudents = 10, int maxNumOfCourses = 10) : students(maxNumOfStudents), courses(maxNumOfCourses) {}

private:
	IntHash<Course> courses;
	StringHash<list<int>> students;
};