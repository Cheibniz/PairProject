#include"geomtry_component.h"
#include<fstream>
#include<iostream>

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
	void insertFromFile(ifstream& infile);
	set<Point> getPointSet();
	set<Line*> getLineSet();
	set<Circle> getCircleSet();
	void eraseLine(Line* l);
	void eraseCircle(Circle& c);
	size_t getPointNum();

private:
	int n;
	set<Point> pointSet;
	set<Line*> lineSet;
	set<Circle> circleSet;

	void updatePointSet();
};

#endif // !_TABLE_H_

