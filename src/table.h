#include"geomtry_component.h"
#include<fstream>
#include<iostream>
#include<regex>
#include <sstream>
#include "error.h"

#ifndef _TABLE_H_
#define _TABLE_H_

/*
 * make sure every geometry in table is unique
 */
class Table
{
public:
	Table();
	~Table();

	void insertLine(Line& l);
	void insertCircle(Circle& c);
	void insertFromString(string& infile);
	set<Point>& getPointSet();
	set<Line*, LinePtrCmp>& getLineSet();
	set<Circle>& getCircleSet();
	void eraseLine(Line* l);
	void eraseCircle(Circle& c);
	void eraseFromString(string& erase);
	size_t getPointNum();
	vector<exception>& getExceptions();
private:

	set<Point> pointSet;
	set<Line*, LinePtrCmp> lineSet;
	set<Circle> circleSet;
	vector<exception> exceptVector;
	void updatePointSet();
};

#endif // !_TABLE_H_

