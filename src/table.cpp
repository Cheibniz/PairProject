#include"table.h"

Table::Table(int n) 
	: n(n)
{
	lineSet.clear();
	circleSet.clear();
}

Table::~Table()
{
}

void Table::insertLine(Line& l)
{
	for (auto temp : lineSet) {
		temp->GetCrossPoint(&l);
	}
	for (Circle temp : circleSet) {
		temp.GetCrossToLine(l);
	}
	lineSet.insert(&l);
}

void Table::insertCircle(Circle& circle)
{
	for (auto temp : lineSet) {
		circle.GetCrossToLine(*temp);
	}
	for (Circle temp : circleSet)
	{
		circle.GetCrossToCircle(temp);
	}
	circleSet.insert(circle);
}
