#include"table.h"

Table::Table() 
{
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

set<Line*, LinePtrCmp>& Table::getLineSet()
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
	lineSet.erase(l);
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
	if (lineSet.count(&l) > 0)
	{
		throw Doublication(l.toString());
	}
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
	if (circleSet.count(circle) > 0)
	{
		throw Doublication(circle.toString());
	}
	for (auto temp : lineSet) {
		circle.GetCrossToLine(pointSet ,*temp);
	}
	for (Circle temp : circleSet)
	{
		circle.GetCrossToCircle(pointSet, temp);
	}
	circleSet.insert(circle);
}

void Table::insertFromString(string& inStream)
{
	static string number = "(0*[1-9]\\d{0,4})";
	static string radius = "(\\+?" + number + ")";
	static string number0 = "((0+)|(" + number + "))";
	static string snumber0 = "([+-]?" + number0 + ")";
	static regex reg(
		"\\s*("
		"([LRS]\\s+" + snumber0 + "\\s+" + snumber0 + "\\s+" + snumber0 + "\\s+" + snumber0 + ")"
		"|"
		"(C\\s+" + snumber0 + "\\s+" + snumber0 + "\\s+" + radius + ")"
		")\\s*"
	);

	if (!regex_match(inStream, reg)) {
		throw domain_error(inStream);
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
		Straight* straight = new Straight(x0, y0, x1, y1);
		insertLine(*straight);
		break;
	}
	case 'R':
	{
		stream >> x0 >> y0 >> x1 >> y1;
		Ray* ray = new Ray(x0, y0, x1, y1);
		insertLine(*ray);
		break;
	}
	case 'S':
	{
		stream >> x0 >> y0 >> x1 >> y1;
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
		cout << "Here should be  unreachable" << endl;
	}
	}
}

void Table::eraseFromString(string& erase)
{
	static string number = "(0*[1-9]\\d{0,4})";
	static string radius = "(\\+?" + number + ")";
	static string number0 = "((0+)|(" + number + "))";
	static string snumber0 = "([+-]?" + number0 + ")";
	static regex reg(
		"\\s*("
		"([LRS]\\s+" + snumber0 + "\\s+" + snumber0 + "\\s+" + snumber0 + "\\s+" + snumber0 + ")"
		"|"
		"(C\\s+" + snumber0 + "\\s+" + snumber0 + "\\s+" + radius + ")"
		")\\s*"
	);

	if (!regex_match(erase, reg)) {
		throw domain_error(erase);
	}
	stringstream stream;
	stream << erase;
	char type;
	int x0, x1, y0, y1;
	stream >> type;


	switch (type)
	{
	case 'L':
	{
		stream >> x0 >> y0 >> x1 >> y1;
		Straight* straight = new Straight(x0, y0, x1, y1);
		eraseLine(straight);
		break;
	}
	case 'R':
	{
		stream >> x0 >> y0 >> x1 >> y1;
		Ray* ray = new Ray(x0, y0, x1, y1);
		eraseLine(ray);
		break;
	}
	case 'S':
	{
		stream >> x0 >> y0 >> x1 >> y1;
		Segment* segment = new Segment(x0, y0, x1, y1);
		eraseLine(segment);
		break;
	}
	case 'C':
	{
		stream >> x0 >> y0 >> x1;

		Circle circle(Point(x0, y0), x1);
		eraseCircle(circle);
		break;
	}
	default:
	{
		cout << "Here should be  unreachable" << endl;
	}
	}
}