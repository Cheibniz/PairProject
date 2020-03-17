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
	Table table = Table();
	table.insertFromFile(infile);
	outfile << table.getPointNum() << endl;	
	return 0;
}

