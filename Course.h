// DO NOT CHANGE AND DO NOT SUBMIT
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Course
{
private:
	string name;
	int num;

public:
	Course(string _name = "", int _num = 0);
	string getName();
	int getNum();
	void setName(string _name);
	void setNum(int _num);
	friend ostream &operator<<(ostream &os, const Course &c);
	friend istream &operator>>(istream &is, Course &c);
};
