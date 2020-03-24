
#include "Interface.h"
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char** argv)
{

	try
	{
		string infile;
		ofstream outfile;
		int n;
		if (!strcmp(argv[1], "-i") && !strcmp(argv[3], "-o"))
		{
			infile = argv[2];
			outfile = ofstream(argv[4]);
		}
		else if (!strcmp(argv[3], "-i") && !strcmp(argv[1], "-o"))
		{
			infile = argv[4];
			outfile = ofstream(argv[2]);
		}
		else
		{
			exit(0);
		}
		readFile("in.txt");
		pair<vector<string>, vector<Point>> result;
		result = getResult();
		//cout << result.second.size() << endl;
		outfile << result.second.size() << endl;
	}
	catch (const std::exception&)
	{
		
	}
	return 0;
}

