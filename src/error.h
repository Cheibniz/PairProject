#ifndef ERROR_H
#define ERROR_H
#include<exception>
#include<stdexcept>
using namespace std;
class Doublication : public exception
{
public:
	string messege;

	Doublication(string m)
	{
		messege = m;
	};

	const char* what() const
	{
		return messege.c_str();
	}
private:

};

class pointDoublication : public exception
{
public:
	string messege;

	pointDoublication(string m)
	{
		messege = m;
	}

	const char* what() const
	{
		return messege.c_str();
	}
private:

};
#endif // !ERROR_H
