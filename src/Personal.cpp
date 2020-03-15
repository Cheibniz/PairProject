#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include"geomtry_component.h"
#include"table.h"
#include <random>

using namespace std;

int main(int argc, char** argv)
{
	ifstream infile;
	ofstream outfile;
	int n;
	double x0, x1, y0, y1;
	char type;
	if (!strcmp(argv[1], "-i") && !strcmp(argv[3], "-o"))
	{
		infile = ifstream(argv[2]);
		outfile = ofstream(argv[4]);
	}
	else if (!strcmp(argv[3], "-i") && !strcmp(argv[1], "-o"))
	{
		infile = ifstream(argv[4]);
		outfile = ofstream(argv[2]);
	}
	else
	{
		exit(0);
	}
	infile >> n;
	Table table(n);
	for (int i = 0; i < n; i++)
	{
		infile >> type;
		switch (type)
		{
			case 'L':
			{
				infile >> x0 >> y0 >> x1 >> y1;
				Straight straight(x0, y0, x1, y1);
				table.insertLine(straight);
				break;
			}
			case 'R':
			{
				infile >> x0 >> y0 >> x1 >> y1;
				Ray ray(x0, y0, x1, y1);
				table.insertLine(ray);
				break;
			}
			case 'S':
			{
				infile >> x0 >> y0 >> x1 >> y1;
				Segment segment(x0, y0, x1, y1);
				table.insertLine(segment);
				break;
			}
			case 'C':
			{
				infile >> x0 >> y0 >> x1;
				Circle circle(Point(x0, y0), x1);
				table.insertCircle(circle);
				break;
			}
			default:
			{
				// dealing the wrong!
			}
		}
	}
	outfile << pointSet.size() << endl;	
	return 0;
}

