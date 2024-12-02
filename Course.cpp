// DO NOT CHANGE AND DO NOT SUBMIT
#include "Course.h"

Course::Course(string _name, int _num)
{
    setName(_name);
    setNum(_num);
}

string Course::getName()
{
    return name;
}

int Course::getNum()
{
    return num;
}

void Course::setName(string _name)
{
    name = _name;
}

void Course::setNum(int _num)
{
    num = _num;
}

ostream &operator<<(ostream &os, const Course &c)
{
    os << c.num << '\t' << c.name << endl;
    return os;
}

istream &operator>>(istream &is, Course &c)
{
    is >> c.num >> c.name;
    return is;
}
