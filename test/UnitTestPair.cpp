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
			Straight s(0, 0, 1, 1);
			Ray r(0, 0, 0, 1);
			int result = s.GetCrossPoint(&r);
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(TestMethod2)
		{
			Circle c(Point(0, 0), 1);
			Segment s(0, -1, 0, 1);
			int result = c.GetCrossToLine(s);
			Assert::AreEqual(result, 2);
		}

		TEST_METHOD(TestMethod3)
		{
			Circle c(Point(0, 0), 1);
			Segment s(0, -1, 0, 1);
			Ray r(-1, 0, 5, 0);
			int result = c.GetCrossToLine(s);
			Assert::AreEqual(result, 2);
			Assert::AreEqual(c.GetCrossToLine(r), 2);
			Assert::AreEqual(r.GetCrossPoint(&s), 1);
		}

		TEST_METHOD(TestMethod4)
		{
			Circle c(Point(0, 0), 1);
			Circle c1(Point(3, 0), 2);
			Circle c2(Point(2, 0), 1);
			pointSet.clear();
			c.GetCrossToCircle(c1);
			c1.GetCrossToCircle(c2);
			
			Assert::AreEqual((int)pointSet.size(), 1);
		}

		TEST_METHOD(TestMethod5)
		{
			Circle c(Point(0, 0), 1);
			Circle c1(Point(3, 0), 3);
			Circle c2(Point(2, 0), 1);
			pointSet.clear();
			Assert::AreEqual(c1.GetCrossToCircle(c), 2);
			c2.GetCrossToCircle(c);
			Assert::AreEqual((int)pointSet.size(), 3);
		}
	};
}
