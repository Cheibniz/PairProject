#ifndef LINE_H
#define LINE_H
using namespace std;
class Line {
public:
	double a;
	double b;
	double c;
public:
	//Line() {};
	Line(double x0, double y0, double x1, double y1) {
		a = y1 - y0;
		b = x0 - x1;
		c = x1 * y0 - x0 * y1;
	};
	Line(double x0, double y0, double x1) {
		a = x0;
		b = y0;
		c = x1;
	};
	Point GetCrossPoint(Line l1);

	bool operator< (const Line l1)const {
		return memcmp(this, &l1, sizeof(l1)) < 0;
	}
};
class straight : Line
{
public:
	straight(double x0, double y0, double x1, double y1);
	~straight();

private:

};

straight::straight(double x0, double y0, double x1, double y1)
{
	
}

straight::~straight()
{
}

//ray
//segment
#endif // !LINE_H
