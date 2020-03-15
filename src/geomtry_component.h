#include <unordered_set>
#include <set>
#include <iostream>

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

using namespace std;

#define EPS 1e-10

class Point {
public:
	double pointX;
	double pointY;
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
};

class Line {
public:
	double a;
	double b;
	double c;
	Point start;
	Point end;
public:
	//Line() {};
	Line(double x0, double y0, double x1, double y1) : start(x0, y0), end(x1, y1) {
		a = y1 - y0;
		b = x0 - x1;
		c = x1 * y0 - x0 * y1;
	};
	
	int GetCrossPoint(Line* l1);
	virtual bool is_on_self(Point& p);   // The Point p must be on the straight defined by a, b and c.

	bool operator< (const Line& l1)const {
		return memcmp(this, &l1, sizeof(l1)) < 0;
	}
};

class Straight : public Line
{
public:
	Straight(double x0, double y0, double x1, double y1);
	~Straight();

	virtual bool is_on_self(Point& p) { return true; }
private:

};



class Ray : public Line
{
public:

	Ray(double x0, double y0, double x1, double y1) : Line(x0, y0, x1, y1) {};
	~Ray();

	virtual bool is_on_self(Point& p);

private:

};

class Segment : public Line
{
public:
	
	Segment(double x0, double y0, double x1, double y1);
	~Segment();

	virtual bool is_on_self(Point& p) override;

private:

};

class Circle
{
public:
	Point center;
	double r;
	Circle(Point p, double i) : center(p), r(i) {};
	int GetCrossToCircle(Circle c1);
	int GetCrossToLine(Line& l1);
	bool operator< (const Circle c1)const {
		return memcmp(this, &c1, sizeof(c1)) < 0;
	}
};

extern set<Point> pointSet;
#endif // !_GEOMETRY_H_
