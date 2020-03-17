#include"table.h"

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
		circle.GetCrossToCircle(pointSet, temp);
	}
	circleSet.insert(circle);
}

void Table::insertFromStream(ifstream& infile)
{
	char type;
	double x0, x1, y0, y1;
	infile >> n;
	for (int i = 0; i < n; i++)
	{
		infile >> type;
		switch (type)
		{
		case 'L':
		{
			infile >> x0 >> y0 >> x1 >> y1;
			Straight* straight = new Straight(x0, y0, x1, y1);
			insertLine(*straight);
			break;
		}
		case 'R':
		{
			infile >> x0 >> y0 >> x1 >> y1;
			Ray* ray = new Ray(x0, y0, x1, y1);
			insertLine(*ray);
			break;
		}
		case 'S':
		{
			infile >> x0 >> y0 >> x1 >> y1;
			Segment* segment = new Segment(x0, y0, x1, y1);
			insertLine(*segment);
			break;
		}
		case 'C':
		{
			infile >> x0 >> y0 >> x1;
			Circle circle(Point(x0, y0), x1);
			insertCircle(circle);
			break;
		}
		default:
		{
			// dealing the wrong!
		}
		}
	}
}