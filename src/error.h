#ifndef ERROR_H
#define ERROR_H
#include<exception>
#include<stdexcept>
using namespace std;
class Doublication : public exception
{
public:
	Doublication() {};
	const char* what()
	{
		return "Component Doublication";
	}
private:

};

class pointDoublication : public exception
{
public:
	pointDoublication() {};
	const char* what()
	{
		return "point Doublication";
	}
private:

};
#endif // !ERROR_H
