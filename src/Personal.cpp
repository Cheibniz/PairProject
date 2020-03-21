#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include"geomtry_component.h"
#include"table.h"
#include <random>
#include <regex>
#include <string>
#include <sstream>
#include "error.h"

using namespace std;

int main(int argc, char** argv)
{
	ifstream infile;
	ofstream outfile;
	string getLine;
	int n;
	if (!strcmp(argv[1], "-i") && !strcmp(argv[3], "-o"))
	{
		infile = ifstream(argv[2]);
		outfile = ofstream(argv[4]);
		if (!(infile.is_open()))
		{
			cout << "open file fail" << endl;
			exit(0);
		}
	}
	else if (!strcmp(argv[3], "-i") && !strcmp(argv[1], "-o"))
	{
		infile = ifstream(argv[4]);
		outfile = ofstream(argv[2]);
		if (!(infile.is_open()))//TODO : is_open or good
		{
			cout << "open file fail" << endl;
			exit(0);
		}
	}
	else
	{
		exit(0);
	}
	Table table = Table();

	getline(infile, getLine);
	regex reg1("\\s*\\d+\\s*");
	if (!regex_match(getLine, reg1)) {
		//input n error
		
		cout << "n is out of range" << endl;
	}
	stringstream stream;
	stream << getLine;
	stream >> n;
	if (!n) {
		cout << "n is 0" << endl;
	}
	
	for (int i = 0; i < n; i++)
	{
		try
		{
			if (!getline(infile, getLine))
			{
				cout << "n is smaller than the true line num or IO error" << endl;
				break;
			}
			
			table.insertFromString(getLine);
		}
		catch (const std::domain_error& de)
		{
			cout << de.what() << " domain" << endl;
		}
		catch (Doublication & dl)
		{
			cout << dl.what() << " dl" << endl;
		}
		catch (pointDoublication & pdl)
		{
			cout << pdl.what() << " pointd" << endl;
		}
	}
	
	outfile << table.getPointNum() << endl;
	cout << table.getPointNum() << endl;
	return 0;
}

