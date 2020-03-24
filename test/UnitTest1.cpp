#include "pch.h"
#include "CppUnitTest.h"
#include "../ASE_pair_project/table.h"
#include "../ASE_pair_project/geomtry_component.h"
#include "../ASE_pair_project/read_file.h"
#include "../ASE_pair_project/error.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
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
			readFromFile(table, open);
			Assert::AreEqual(4, (int)table.getPointNum());
			Circle circle = Circle(Point(0, 0), 1);
			table.eraseCircle(circle);
			Assert::AreEqual(3, (int)table.getPointNum());
			circle = Circle(Point(2, 0), 1);
			table.eraseCircle(circle);
			Assert::AreEqual(2, (int)table.getPointNum());
			Line* line = new Line(0, 0, 1, 0);
			try
			{
				table.insertLine(*line);
			}
			catch (const Doublication& e)
			{
				Assert::AreEqual(line->toString(), (string)(e.what()));
			}
			Assert::AreEqual(2, (int)table.getPointNum());
			table.eraseLine(line);
			Assert::AreEqual(0, (int)table.getLineSet().size());
		}

		TEST_METHOD(TestMethod7)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "4\n C 0 0 1\nC 3 0 2\nC 2 0 1\nL 0 0 3 0\n" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Circle circle = Circle(Point(0, 0), 1);
			try
			{
				table.insertCircle(circle);
			}
			catch (const Doublication & e)
			{
				Assert::AreEqual(circle.toString(), (string)(e.what()));
			}
		}

		TEST_METHOD(TestMethod8)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "1\nL 0 0 0 0\n" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			try
			{
				readFromFile(table, open);
			}
			catch (const pointDoublication& pd)
			{
				Assert::AreEqual(Line(0, 0, 0, 0).toString(), (string)pd.what());
			}
		}

		TEST_METHOD(TestMethod9)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nL 0 0 1 0\nR 0 1 0 2" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(0, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod10)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nL 0 0 1 0\nS 0 1 0 2" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(0, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod11)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nR -1 0 1 0\nS 0 1 0 2" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(0, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod12)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nC 0 0 1\nS 0 0 0 2" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(1, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod13)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nC 0 0 1\nS 0 0 2 0" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(1, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod14)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nC 0 0 1\nR 0 0 2 0" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(1, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod15)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nS 0 0 1 1\nS 1 1 2 2" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(2, (int)table.getLineSet().size());
			Assert::AreEqual(1, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod16)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nS 0 0 1 1\nR 1 1 2 2" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(2, (int)table.getLineSet().size());
			Assert::AreEqual(1, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod17)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nR 1 1 0 0\nR 1 1 2 2" << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(2, (int)table.getLineSet().size());
			Assert::AreEqual(1, (int)table.getPointNum());
		}

		TEST_METHOD(TestMethod18)
		{
			Table table = Table();
			ofstream output = ofstream("output.txt");
			output << "2\nS 0 0 0 1\nS 1 0 1 1 " << endl;
			output.close();
			ifstream open = ifstream("output.txt");
			readFromFile(table, open);
			Assert::AreEqual(2, (int)table.getLineSet().size());
		}
	};
}
