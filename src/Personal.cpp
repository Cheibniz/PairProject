#include "read_file.h"

int main(int argc, char** argv)
{
	ifstream infile;
	ofstream outfile;
	
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
		if (!(infile.is_open()))
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

	readFromFile(table, infile);
	
	outfile << table.getPointNum() << endl;
	cout << table.getPointNum() << endl;
	return 0;
}

