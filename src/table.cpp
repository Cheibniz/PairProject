#include"table.h"
#include<regex>
#include <sstream>
#include "error.h"
Table::Table() 
{
	n = 0;
	lineSet.clear();
	circleSet.clear();
	pointSet.clear();
}

Table::~Table()
{}

set<Point>& Table::getPointSet()
{
	return pointSet;
}

set<Line*>& Table::getLineSet()
{
	return lineSet;
}


set<Circle>& Table::getCircleSet()
{
	return circleSet;
}

size_t Table::getPointNum()
{
	return pointSet.size();
}

vector<exception>& Table::getExceptions()
{
	return exceptVector;
}

void Table::eraseLine(Line* l)
{
	
	for (auto i = lineSet.begin(); i != lineSet.end(); i++)
	{
		if (**i == *l)
		{
			lineSet.erase(i);
			break;
		}
	}
	updatePointSet();
}

void Table::eraseCircle(Circle& c)
{
	circleSet.erase(c);
	updatePointSet();
}

void Table::updatePointSet()
{
	pointSet.clear();
	for (auto i = lineSet.begin(); i != lineSet.end(); i++)
	{
		auto temp = i;
		for (auto j = ++temp; j != lineSet.end(); j++)
		{
			(*j)->GetCrossPoint(pointSet, (*i));
		}
		for (auto j = circleSet.begin(); j != circleSet.end(); j++)
		{
			((Circle)*j).GetCrossToLine(pointSet, **i);
		}
	}

	for (auto i = circleSet.begin(); i != circleSet.end(); i++)
	{
		auto tmp = i;
		for (auto j = ++tmp; j != circleSet.end(); j++)
		{
			((Circle)*j).GetCrossToCircle(pointSet, *i);
		}
	}
}

void Table::insertLine(Line& l)
{
	for (auto temp : lineSet) {
		if (*temp == l)
		{
			throw Doublication();
		}
		temp->GetCrossPoint(pointSet ,&l);
	}
	for (Circle temp : circleSet) {
		temp.GetCrossToLine(pointSet, l);
	}
	lineSet.insert(&l);
}

void Table::insertCircle(Circle& circle)
{
	for (auto temp : lineSet) {
		circle.GetCrossToLine(pointSet ,*temp);
	}
	for (Circle temp : circleSet)
	{
		if (temp == circle)
		{
			throw Doublication();
		}
		circle.GetCrossToCircle(pointSet, temp);
	}
	circleSet.insert(circle);
}

void Table::insertFromString(string& inStream)
{
	regex reg1("\\s+((L|R|S)\\s+\\d+\\s+\\d+\\s+\\d+\\s+\\d+\\s+) | (C\\s+\\d+\\s+\\d+\\s+\\d+\\s+)");
	regex reg3("\\s*((L|R|S)\\s+(0+|0*[1-9]\\d{0,4})\\s+(0+|0*[1-9]\\d{0,4})\\s+(0+|0*[1-9]\\d{0,4})\\s+(0+|0*[1-9]\\d{0,4})\\s+)|(C\\s+(0+|0*[1-9]\\d{0,4})\\s+(0+|0*[1-9]\\d{0,4})\\s+(0*[1-9]\\d{0,4}))\\s*");

	if (!regex_match(inStream, reg3)) {
		//throw domain_error(inStream);
	}
	stringstream stream;
	stream << inStream;
	char type;
	int x0, x1, y0, y1;
	stream >> type;

	
	switch (type)
	{
	case 'L':
	{
		stream >> x0 >> y0 >> x1 >> y1;
		if (Point(x0, y0) == Point(x1, y1))
		{
			throw pointDoublication();
		}
		Straight* straight = new Straight(x0, y0, x1, y1);
		insertLine(*straight);
		break;
	}
	case 'R':
	{
		stream >> x0 >> y0 >> x1 >> y1;
		if (Point(x0, y0) == Point(x1, y1))
		{
			throw pointDoublication();
		}
		Ray* ray = new Ray(x0, y0, x1, y1);
		insertLine(*ray);
		break;
	}
	case 'S':
	{
		stream >> x0 >> y0 >> x1 >> y1;
		if (Point(x0, y0) == Point(x1, y1))
		{
			throw pointDoublication();
		}
		Segment* segment = new Segment(x0, y0, x1, y1);
		insertLine(*segment);
		break;
	}
	case 'C':
	{
		stream >> x0 >> y0 >> x1;
		
		Circle circle(Point(x0, y0), x1);
		insertCircle(circle);
		break;
	}
	default:
	{
		// dealing the wrong!
		cout << "Here is unreachable" << endl;
	}
	}
	
}