#include "Interface.h"
#include "read_file.h"
#include "table.h"

Table table;

void readFile(string inFilePath)
{
    ifstream infile = ifstream(inFilePath);
    readFromFile(table, infile);
    infile.close();
}

void addGeometryObject(string geometryString)
{
    table.insertFromString(geometryString);
}

void removeGeometryObject(string geometryString)
{
    table.eraseFromString(geometryString);
}

pair<vector<string>, vector<InterfacePoint>> getResult()
{
    vector<string> geometries = vector<string>(table.getLineSet().size() + table.getCircleSet().size());
    vector<InterfacePoint> points = vector<InterfacePoint>(table.getPointNum());
    geometries.clear();
    points.clear();
    for (auto i : table.getLineSet())
    {
        geometries.push_back(i->toString());
    }
    for (auto i : table.getCircleSet())
    {
        geometries.push_back(i.toString());
    }
    for (auto i : table.getPointSet())
    {
        points.push_back(InterfacePoint(i.pointX, i.pointY));
    }
    return pair<vector<string>, vector<InterfacePoint>>(geometries, points);
}