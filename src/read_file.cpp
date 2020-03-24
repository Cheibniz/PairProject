#include "read_file.h"

void readFromFile(Table& table, ifstream& infile)
{
	string getLine;
	int n;
	int lineNumber = 0;

	getline(infile, getLine);
	lineNumber++;

	regex reg1("\\s*\\+?0*[1-9]\\d*\\s*");
	if (!regex_match(getLine, reg1)) {
		cout << "Error: the first line of input file is not a regular positive number." << endl;
	}

	stringstream stream;
	stream << getLine;
	stream >> n;

	for (int i = 0; i < n; i++)
	{
		if (!getline(infile, getLine))
		{
			cout << "n is smaller than the true number of geometry or IO error" << endl;
			break;
		}

		lineNumber++;

		try
		{
			table.insertFromString(getLine);
		}
		catch (const std::domain_error & de)
		{
			cout << "Error: in " << lineNumber << " line of input file: " << de.what() << " is not a regular geometry or the parameter is out of range." << endl;
		}
		catch (Doublication & dl)
		{
			cout << "Error: in " << lineNumber << " line of input file: " << dl.what() << " has infinity intersection points with other geometry in smaller number of line." << endl;
		}
		catch (pointDoublication & pdl)
		{
			cout << "Error: in " << lineNumber << " line of input file: " << pdl.what() << " is consisted of two same define-points." << endl;
		}
	}
}