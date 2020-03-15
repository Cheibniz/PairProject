#include"geomtry_component.h"

#ifndef _TABLE_H_
#define _TABLE_H_
extern set<Point> pointSet;
class Table
{
public:
	Table(int n);
	~Table();

	void insertLine(Line& l);
	void insertCircle(Circle& c);

private:
	int n;
	set<Line*> lineSet;
	set<Circle> circleSet;
};

#endif // !_TABLE_H_

