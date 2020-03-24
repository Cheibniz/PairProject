#include "geomtry_component.h"

Straight::Straight(double x0, double y0, double x1, double y1)
	: Line(x0, y0, x1, y1)
{}

Straight::~Straight()
{
}

string Straight::toString() const
{
	return "L " + to_string(start.pointX) + " " + to_string(start.pointY) + " " + to_string(end.pointX) + " " + to_string(end.pointY);
}

Ray::~Ray()
{
}

bool Ray::is_on_self(Point& p) const
{
	return ((end.pointX - start.pointX) * (p.pointX - start.pointX)) >= 0 
		&& ((end.pointY - start.pointY) * (p.pointY - start.pointY)) >= 0;
}

string Ray::toString() const
{
	return "R " + to_string(start.pointX) + " " + to_string(start.pointY) + " " + to_string(end.pointX) + " " + to_string(end.pointY);
}

Segment::Segment(double x0, double y0, double x1, double y1)
	: Line(x0, y0, x1, y1)
{
	if (start < end)
	{
		max_p = end;
	}
	else
	{
		max_p = start;
	}
}

Segment::~Segment()
{
}

bool Segment::is_on_self(Point& p) const
{
	return ((p.pointX - start.pointX) * (p.pointX - end.pointX)) <= 0 
		&& ((p.pointY - start.pointY) * (p.pointY - end.pointY)) <= 0;
}

string Segment::toString() const
{
	return "S " + to_string(start.pointX) + " " + to_string(start.pointY) + " " + to_string(end.pointX) + " "  + to_string(end.pointY);
}

int Line::GetCrossPoint(set<Point>& pointSet, Line* l1)
{
	double D;
	D = l1->a * this->b - this->a * l1->b;
	if (!D)
	{
		if (this->type() == RAY && l1->type() == RAY 
			&& abs(this->a - l1->a) < EPS && abs(this->b - l1->b) < EPS && abs(this->c - l1->c) < EPS)
		{
			if (this->start == l1->start && !this->is_on_self(l1->end))
			{
				pointSet.insert(this->start);
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (this->type() == RAY && l1->type() == SEGMENT
			&& abs(this->a - l1->a) < EPS && abs(this->b - l1->b) < EPS && abs(this->c - l1->c) < EPS)
		{
			Line* seg = l1;
			Line* ray = this;
			if (!ray->is_on_self(seg->start) && seg->end == ray->start)
			{
				pointSet.insert(ray->start);
				return 1;
			}
			else if (!ray->is_on_self(seg->end) && seg->start == ray->start)
			{
				pointSet.insert(ray->start);
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (this->type() == SEGMENT && l1->type() == RAY
			&& abs(this->a - l1->a) < EPS && abs(this->b - l1->b) < EPS && abs(this->c - l1->c) < EPS)
		{
			Line* seg = this;
			Line* ray = l1;
			if (seg->end == ray->start && !ray->is_on_self(seg->start))
			{
				pointSet.insert(ray->start);
				return 1;
			}
			else if (seg->start == ray->start && !ray->is_on_self(seg->end))
			{
				pointSet.insert(ray->start);
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (this->type() == SEGMENT && l1->type() == SEGMENT
			&& abs(this->a - l1->a) < EPS && abs(this->b - l1->b) < EPS && abs(this->c - l1->c) < EPS)
		{
			Point* align_1 = NULL;
			Point* align_2 = NULL;
			Point* tail_1 = NULL;
			Point* tail_2 = NULL;
			if (this->start == l1->start)
			{
				align_1 = &(this->start);
				tail_1 = &(this->end);
				align_2 = &(l1->start);
				tail_2 = &(l1->end);
			}
			else if (this->start == l1->end)
			{
				align_1 = &(this->start);
				tail_1 = &(this->end);
				align_2 = &(l1->end);
				tail_2 = &(l1->start);
			}
			if (this->end == l1->start)
			{
				align_1 = &(this->end);
				tail_1 = &(this->start);
				align_2 = &(l1->start);
				tail_2 = &(l1->end);
			}
			else if (this->end == l1->end)
			{
				align_1 = &(this->end);
				tail_1 = &(this->start);
				align_2 = &(l1->end);
				tail_2 = &(l1->start);
			}
			else
			{
				return 0;
			}
			if (align_1 != NULL)
			{
				if (((tail_1->pointX - align_1->pointX) * (tail_2->pointX - align_1->pointX) < 0)
					|| ((tail_1->pointY - align_1->pointY) * (tail_2->pointY - align_1->pointY) < 0))
				{
					pointSet.insert(*align_1);
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			return 0;
		}
	}
	Point pTemp(0, 0);
	pTemp.pointX = (l1->b * this->c - this->b * l1->c) / D;
	pTemp.pointY = (l1->c * this->a - this->c * l1->a) / D;
	bool b1 = this->is_on_self(pTemp);
	bool b2 = l1->is_on_self(pTemp);
	if (!this->is_on_self(pTemp) || !l1->is_on_self(pTemp))
	{
		return 0;
	}
	pointSet.insert(pTemp);
	return 1;
}

bool Line::is_on_self(Point& p) const
{
	return true;
}

string Line::toString() const
{
	return "L " + to_string(start.pointX) + " " + to_string(start.pointY) + " " + to_string(end.pointX) + " " + to_string(end.pointY);
}

// a1b2-a2b1=0,b1c2-b2c1=0
bool Line::operator== (const Line& l1)const
{
	if (this->type() != l1.type())
	{
		return false;
	}
	bool doublication = false;
	if (abs(this->b) > EPS || abs(l1.b) > EPS)
	{
		double B, D;
		D = l1.a * this->b - this->a * l1.b;
		B = b * l1.c - l1.b * c;
		if (abs(D - 0) < EPS && abs(B - 0) < EPS)
		{
			doublication = true;
		}
	}
	else
	{
		if (abs(this->a * l1.c - this->c * l1.a) < EPS)
		{
			doublication = true;
		}
	}
	if (doublication)
	{
		if (this->type() == STRAIGHT)
		{
			return true;
		}
		else if (this->type() == RAY)
		{
			if (this->start == l1.start && this->is_on_self((Point&)l1.end))
			{
				return true;
			}
		}
		else if (this->type() == STRAIGHT)
		{
			return (this->start == l1.start && this->end == l1.end) || (this->start == l1.end && this->end == l1.start);
		}
	}
	return false;
}

bool Line::operator< (const Line& l1)const {
	if (this->type() == l1.type())
	{
		if (abs(a - l1.a) > EPS)
		{
			return a < l1.a;
		}
		else if (abs(b - l1.b) > EPS)
		{
			return b < l1.b;
		}
		else if (abs(c - l1.c) > EPS)
		{
			return c < l1.c;
		}
		else
		{
			if (this->type() == STRAIGHT)
			{
				return false;
			}
			else if (this->type() == RAY)
			{
				if (!(this->start == l1.start))
				{
					return this->start < l1.start;
				}
				else if (!(this->is_on_self((Point&)l1.end)))
				{
					return this->end < l1.end;
				}
				else
				{
					return false;
				}
			}
			else if (this->type() == SEGMENT)
			{
				if (!((this->start == l1.start && this->end == l1.end) || (this->start == l1.end && this->end == l1.start)))
				{
					return ((Segment*)this)->max_p < ((Segment&)l1).max_p;
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return this->type() < l1.type();
	}
	return false;
}

bool LinePtrCmp::operator() (const Line* first, const Line* second) const
{
	if (first->type() == second->type())
	{
		if (abs(first->a - second->a) > EPS)
		{
			return first->a < second->a;
		}
		else if (abs(first->b - second->b) > EPS)
		{
			return first->b < second->b;
		}
		else if (abs(first->c - second->c) > EPS)
		{
			return first->c < second->c;
		}
		else
		{

			if (first->type() == STRAIGHT)
			{
				return false;
			}
			else if (first->type() == RAY)
			{
				if (!(first->start == second->start))
				{
					return first->start < second->start;
				}
				else if (!(first->is_on_self((Point&)second->end)))
				{
					return first->end < second->end;
				}
				else
				{
					return false;
				}
			}
			else if (first->type() == SEGMENT)
			{
				if (!((first->start == second->start && first->end == second->end)
					|| (first->start == second->end && first->end == second->start)))
				{
					return ((Segment*)first)->max_p < ((Segment*)second)->max_p;
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return first->type() < second->type();
	}
	return false;
}

int Circle::GetCrossToCircle(set<Point>& pointSet, Circle c1)
{
	double a1, b1, r1, a0, b0, r0;
	a0 = center.pointX;
	b0 = center.pointY;
	r0 = r;
	a1 = c1.center.pointX;
	b1 = c1.center.pointY;
	r1 = c1.r;
	double a12 = a1 * a1, b12 = b1 * b1, r12 = r1 * r1, a02 = a0 * a0, b02 = b0 * b0, r02 = r0 * r0;
	double delta = (-a02 + 2 * a0 * a1 - a12 - b02 + 2 * b0 * b1 - b12 + r02 + 2 * r0 * r1 + r12) * (a02 - 2 * a0 * a1 + a12 + b02 - 2 * b0 * b1 + b12 - r02 + 2 * r0 * r1 - r12);
	if (delta < 0)
	{
		return 0;
	}
	double delta_1 = a0 * b02 - a02 * a1 - a0 * a12 + a0 * b12 + a1 * b02 + a1 * b12 - a0 * r02 + a0 * r12 + a1 * r02 - a1 * r12 + a02 * a0 + a12 * a1 - 2 * a0 * b0 * b1 - 2 * a1 * b0 * b1;
	double delta_2 = sqrt(delta);
	double delta_3 = 2 * (a02 - 2 * a0 * a1 + a12 + b02 - 2 * b0 * b1 + b12);
	double delta_4 = a02 * b0 + a02 * b1 + a12 * b0 + a12 * b1 - b0 * b12 - b02 * b1 - b0 * r02 + b0 * r12 + b1 * r02 - b1 * r12 + b0 * b02 + b1 * b12 - 2 * a0 * a1 * b0 - 2 * a0 * a1 * b1;
	Point cross1((delta_1 - b0 * delta_2 + b1 * delta_2) / delta_3, (delta_4 + a0 * delta_2 - a1 * delta_2) / delta_3);
	Point cross2((delta_1 + b0 * delta_2 - b1 * delta_2) / delta_3, (delta_4 - a0 * delta_2 + a1 * delta_2) / delta_3);
	pointSet.insert(cross1);
	pointSet.insert(cross2);
	return 2;
}

int Circle::GetCrossToLine(set<Point>& pointSet, Line& l1)
{
	double a0 = l1.a, b0 = l1.b, c0 = l1.c, a1 = center.pointX, b1 = center.pointY, r1 = r;
	double a12 = a1 * a1, b12 = b1 * b1, r12 = r1 * r1, a02 = a0 * a0, b02 = b0 * b0, c02 = c0 * c0;
	double delta = -a02 * a12 + a02 * r12 - 2 * a0 * a1 * b0 * b1 - 2 * a0 * a1 * c0 - b02 * b12 + b02 * r12 - 2 * b0 * b1 * c0 - c02;
	if (delta < 0) {
		return 0;
	}
	double delta_1 = a02 + b02;
	double delta_2 = sqrt(delta);
	double delta_3 = a0 * c0 - a1 * b02 + a0 * b0 * b1;
	double delta_4 = b0 * c0 - a02 * b1 + a0 * a1 * b0;
	Point cross1(-(delta_3 - b0 * delta_2) / delta_1, -(delta_4 + a0 * delta_2) / delta_1);
	Point cross2(-(delta_3 + b0 * delta_2) / delta_1, -(delta_4 - a0 * delta_2) / delta_1);
	if (l1.is_on_self(cross1))
	{
		pointSet.insert(cross1);
	}
	if (l1.is_on_self(cross2))
	{
		pointSet.insert(cross2);
	}
	return 2;
}

bool Circle::operator== (const Circle c1)const
{
	return (center == c1.center) && abs(r - c1.r) < EPS;
}

bool Circle::operator< (const Circle c1)const
{
	if (abs(r - c1.r) > EPS)
	{
		return r < c1.r;
	}
	else
	{
		return center < c1.center;
	}
}

string Circle::toString() const
{
	return "C " + to_string(center.pointX) + " " + to_string(center.pointY) + " " + to_string(r);
}