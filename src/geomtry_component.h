#include <unordered_set>
#include <set>
#include <iostream>
#include <string>
#include "error.h"

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#define LINE 0
#define STRAIGHT 0
#define RAY 1
#define SEGMENT 2
#define CIRCLE 3

using namespace std;

#define EPS 1e-10

class Point {
public:
	double pointX;
	double pointY;

	Point() { pointX = 0; pointY = 0; }
	Point(double x, double y) { pointX = x; pointY = y; }

	bool operator< (const Point l1)const {
		//return memcmp(this, &l1, sizeof(l1)) < 0;

		if (fabs(pointX - l1.pointX) < EPS)
		{
			return pointY < l1.pointY && fabs(pointY - l1.pointY) > EPS;
		}
		else
		{
			return pointX < l1.pointX;
		}
		return true;
	}

	bool operator== (const Point p1)const {
		return (abs(pointX - p1.pointX) < EPS && abs(pointY - p1.pointY) < EPS);
	}
};

class Line {
public:
	double a;
	double b;
	double c;
	Point start;
	Point end;
public:
	Line(double x0, double y0, double x1, double y1) : start(x0, y0), end(x1, y1) {
		if (start == end)
		{
			throw pointDoublication(this->toString());
		}

		a = y1 - y0;
		b = x0 - x1;
		c = x1 * y0 - x0 * y1;
		double s_add = sqrt(a * a + b * b + c * c);
		a = a / s_add;
		b = b / s_add;
		c = c / s_add;
		if (a < 0)
		{
			a = -a;
			b = -b;
			c = -c;
		}
	};
	
	int GetCrossPoint(set<Point>& pointSet,Line* l1);

	virtual bool is_on_self(Point& p) const;   // The Point p must be on the this line.
	virtual string toString() const;
	virtual int type() const { return LINE; }

	bool operator< (const Line& l1)const;
	bool operator== (const Line& l1)const;
};

struct LinePtrEqual
{
	bool operator() (const Line* first, const Line* second) const
	{
		if (first->type() != second->type())
		{
			return false;
		}
		bool doublication = false;
		if (abs(first->b) > EPS || abs(second->b) > EPS)
		{
			double B, D;
			D = second->a * first->b - first->a * second->b;
			B = first->b * second->c - second->b * first->c;
			if (abs(D - 0) < EPS && abs(B - 0) < EPS)
			{
				doublication = true;
			}
		}
		else
		{
			if (abs(first->a * second->c - first->c * second->a) < EPS)
			{
				doublication = true;
			}
		}
		if (doublication)
		{
			if (first->type() == STRAIGHT)
			{
				return true;
			}
			else if (first->type() == RAY)
			{
				if (first->start == second->start && first->is_on_self((Point&)second->end))
				{
					return true;
				}
			}
			else if (first->type() == STRAIGHT)
			{
				return (first->start == second->start && first->end == second->end) 
					|| (first->start == second->end && first->end == second->start);
			}
		}
		return false;
	}
};

struct LinePtrCmp
{
	bool operator() (const Line* first, const Line* second) const;
};

class Straight : public Line
{
public:
	Straight(double x0, double y0, double x1, double y1);
	~Straight();

	virtual bool is_on_self(Point& p) const { return true; }
	virtual string toString() const;
	virtual int type() const { return STRAIGHT; }
private:

};



class Ray : public Line
{
public:

	Ray(double x0, double y0, double x1, double y1) : Line(x0, y0, x1, y1) {};
	~Ray();

	virtual bool is_on_self(Point& p) const;
	virtual string toString() const;
	virtual int type() const { return RAY; }

private:

};

class Segment : public Line
{
public:
	Point max_p;
	
	Segment(double x0, double y0, double x1, double y1);
	~Segment();

	virtual bool is_on_self(Point& p) const;
	virtual string toString() const;
	virtual int type() const { return SEGMENT; }

private:

};

class Circle
{
public:
	Point center;
	double r;
	Circle(Point p, double i) : center(p), r(i) {};
	int GetCrossToCircle(set<Point>& pointSet, Circle c1);
	int GetCrossToLine(set<Point>& pointSet, Line& l1);

	virtual string toString() const;
	virtual int type() const { return CIRCLE; }

	bool operator== (const Circle c1)const;
	bool operator< (const Circle c1)const;
};
#endif // !_GEOMETRY_H_
