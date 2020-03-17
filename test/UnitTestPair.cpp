#include "pch.h"
#include "CppUnitTest.h"
#include "../PairProject/geomtry_component.h"
#include "../PairProject/table.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestPair
{
	TEST_CLASS(UnitTestPair)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Table table = Table();
			Straight s(0, 0, 1, 1);
			Ray r(0, 0, 0, 1);
			int result = s.GetCrossPoint(table.getPointSet(), &r);
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(TestMethod2)
		{
			Table table = Table();
			Circle c(Point(0, 0), 1);
			Segment s(0, -1, 0, 1);
			int result = c.GetCrossToLine(table.getPointSet(), s);
			Assert::AreEqual(result, 2);
		}

		TEST_METHOD(TestMethod3)
		{
			Table table = Table();
			Circle c(Point(0, 0), 1);
			Segment s(0, -1, 0, 1);
			Ray r(-1, 0, 5, 0);
			int result = c.GetCrossToLine(table.getPointSet(), s);
			Assert::AreEqual(result, 2);
			Assert::AreEqual(c.GetCrossToLine(table.getPointSet(), r), 2);
			Assert::AreEqual(r.GetCrossPoint(table.getPointSet(), &s), 1);
		}

		TEST_METHOD(TestMethod4)
		{
			Table table = Table();
			Circle c(Point(0, 0), 1);
			Circle c1(Point(3, 0), 2);
			Circle c2(Point(2, 0), 1);
			c.GetCrossToCircle(table.getPointSet(), c1);
			c1.GetCrossToCircle(table.getPointSet(), c2);
			
			Assert::AreEqual(1, (int)(table.getPointNum()));
		}

		TEST_METHOD(TestMethod5)
		{
			Table table = Table();
			Circle c(Point(0, 0), 1);
			Circle c1(Point(3, 0), 3);
			Circle c2(Point(2, 0), 1);
			
			Assert::AreEqual(c1.GetCrossToCircle(table.getPointSet(), c), 2);
			c2.GetCrossToCircle(table.getPointSet(), c);
			Assert::AreEqual((int)table.getPointNum(), 3);
		}

		TEST_METHOD(TestMethod6)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "4\n C 0 0 1\nC 3 0 2\nC 2 0 1\nL 0 0 3 0\n" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			table.insertFromStream(open);
			Assert::AreEqual(4, (int)table.getPointNum());
			Circle circle = Circle(Point(0, 0), 1);
			table.eraseCircle(circle);
			Assert::AreEqual(3, (int)table.getPointNum());
			circle = Circle(Point(2, 0), 1);
			table.eraseCircle(circle);
			Assert::AreEqual(2, (int)table.getPointNum());
			Line* line = new Line(0, 0, 1, 0);
			table.insertLine(*line);
			Assert::AreEqual(2, (int)table.getPointNum());
			table.eraseLine(line);
			Assert::AreEqual(1, (int)table.getLineSet().size());
		}
	};
}
