#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <string>
#include "Animal.hpp"
#include "Child.hpp"
#include "BrainChild.hpp"
#include "Hats.hpp"
#include "Parameters.hpp"
#include "Lines.hpp"

void testStaticPolymorphism()
{
	Animal A0{ "charles", 2 };
	Animal A1{ "brent", 3 };
	Animal A2{ "jacques", 5 };
	Animal A3{ "katie", 6 };
	Animal A4{ "fanny", 10 };
	Animal A5{ "karl", 1 };
	Animal A6{ "brenda", 1 };
	std::set<Animal> setAnimals = { A5, A0, A6, A6, A1, A3, A4, A5, A2 };
	std::multiset<Animal> setAnimals2 = { A5, A0, A6, A6, A1, A3, A4, A5, A2 };

	// sorts animals based on age
	for (auto const& idx : setAnimals)
	{
		std::cout << idx.getName() << " " << idx.getAge() << std::endl;
	}

	std::cout << "" << std::endl;

	for (auto const& idx : setAnimals2)
	{
		std::cout << idx.getName() << " " << idx.getAge() << std::endl;
	}

}

static void helperDynamPolyPrint(std::vector<Parent*> &refArr)
{
	// print vector dynamically show name based on derived class
	for (auto const& idx : refArr)
	{
		std::cout << idx->getName() << " " << idx->getAge() << std::endl;
	}
}

void testDynamicPolymorphism()
{
	// base ptr
	Parent* parent_ptr{ new Child("kent", 28) };

	std::cout << parent_ptr->getAge() << std::endl;

	parent_ptr->setAge(40);

	std::cout << parent_ptr->getAge() << "\n" << std::endl;

	std::vector<Parent*> setParents;
	std::string randomletters = "abcdefg";
	int inc = 10;
	for (char c : randomletters)
	{
		std::string s(1, c);
		Parent* new_ptr = nullptr;
		if ((c + 0) % 2 == 0u)
		{
			new_ptr = new Child(s, inc);
		}
		else
		{
			new_ptr = new BrainChild(s, inc);
		}
		setParents.push_back(new_ptr);
		inc++;
	}


	helperDynamPolyPrint(setParents);

	std::cout << std::endl;
	delete parent_ptr;
}

void testStrategyTemplates()
{
	std::set<Person, PersonCompare> s(PersonCompare::NAME);
	s.insert(Person("Biro", "Istvan", 1960));
	s.insert(Person("Abos", "Gergely", 1986));
	s.insert(Person("Gered", "Attila", 1986));

	for (auto &x: s)
	{
		std::cout << x.printFirst() << std::endl;
	}
	
}


void printPointMatrix(const std::multiset<Point>& isClosed)
{
	// Get the maximum element
	int maxedge = 12;

	// Declare memory block of size M
	char** a = new char* [maxedge];
	for (int i = 0; i < maxedge; i++) {

		// Declare a memory block
		a[i] = new char[maxedge];
		for (int j = 0; j < maxedge; j++)
		{
			a[i][j] = '=';
		}
	}
	auto it = isClosed.begin();
	for (; (it != isClosed.end()); )
	{
		if ('X' == a[maxedge - 1 - (int)it->get_y()][(int)it->get_x()])
		{
			a[maxedge - 1 - (int)it->get_y()][(int)it->get_x()] = '*';
		}
		else
		{
			a[maxedge - 1 - (int)it->get_y()][(int)it->get_x()] = 'X';
		}

		it++;
	}
	for (int i = 0; i < maxedge; i++)
	{
		std::cout << "-1";
		for (int j = 0; j < maxedge; j++)
		{
			std::cout << a[i][j];
		}
		std::cout << std::endl;
	}
	for (int j = 0; j < maxedge; j++)
	{
		std::cout << "-1";
	}

	for (int i = 0; i < maxedge; i++)    //To delete the inner arrays
		delete[] a[i];
	delete[] a;
	std::cout << std::endl;
}

void testClosed(const std::multiset<Point>& isClosed)
{
	bool closed = true;
	auto it = isClosed.begin();
	auto it2 = it;
	it2++;
	for (; (it2 != isClosed.end()); )
	{
		std::cout << (int)it->get_x() << " " << (int)it->get_y() << std::endl;
		std::cout << (int)it2->get_x() << " " << (int)it2->get_y() << std::endl;
		if ((it->my_x != it2->my_x) || (it->my_y != it2->my_y))
		{
			closed = false;
		}
		it++;
		it++;
		it2++;
		if (it2 == isClosed.end())
		{
			break;
		}
		it2++;
	}
	std::cout << "closed: " << closed << "" << std::endl;
	printPointMatrix(isClosed);
}

bool existsInAddedIds(const std::set<int>& ids, int idToAdd)
{
	for (int existingId: ids)
	{
		if (existingId == idToAdd)
		{
			return true;
		}
	}
	return false;
}

void testGroups(const std::multiset<Point>& isClosed, const std::map<int,Line>& mappedLines, std::vector<std::vector<Line>>& groups)
{
	std::set<int> lineIdsAdded;
	std::set<int> lineIdsAddedLoners;
	auto it = isClosed.begin();
	auto it2 = it;
	it2++;
	// walk through each pair in the sorted set of points and find matching pairs
	for (; (it2 != isClosed.end()); )
	{
		std::cout << (int)it->get_x() << " " << (int)it->get_y() << " line id: " << (int)it->get_line_id() << std::endl;
		std::cout << (int)it2->get_x() << " " << (int)it2->get_y() << " line id: " << (int)it2->get_line_id() << std::endl;
		int lin_id1 = it->get_line_id();
		int lin_id2 = it2->get_line_id();
		auto line_iter1 = mappedLines.find(lin_id1);
		auto line_iter2 = mappedLines.find(lin_id2);
		if ((it->my_x == it2->my_x)  && (it->my_y == it2->my_y))
		{
			// safety check, if both ids exist in the mapped Lines that were originally present apply to the group
			if ((line_iter1 != mappedLines.end()) && (line_iter2 != mappedLines.end()))
			{
				// new group of connected lines
				bool firstwasadded = existsInAddedIds(lineIdsAdded, lin_id1);
				bool secondwasadded = existsInAddedIds(lineIdsAdded, lin_id2);
				if (groups.empty() || (!firstwasadded && !secondwasadded))
				{
					std::vector<Line> init_line_group{ line_iter1->second, line_iter2->second };
					groups.push_back(init_line_group);
					lineIdsAdded.insert(lin_id1);
					lineIdsAdded.insert(lin_id2);
				}
				else if (firstwasadded ^ secondwasadded)
				{
					int notfoundline = -1;
					int index = 0;
					for (std::vector<Line> subgroups : groups)
					{
						for (Line line : subgroups)
						{
							if (line.get_id() == (firstwasadded? lin_id1 : lin_id2))
							{
								notfoundline = index;
								break;
							}
						}
						//doesn't already exist in group add it.
						if (notfoundline != -1)
						{
							//add second to an existing group
							if (firstwasadded)
							{
								groups.at(notfoundline).push_back(line_iter2->second);
								lineIdsAdded.insert(lin_id2);
							}
							else
							{
								groups.at(notfoundline).push_back(line_iter1->second);
								lineIdsAdded.insert(lin_id1);
							}
							break;
						}
						index++;
					}
				}
			}
		}
		else
		{
			// get potential loners
			if (!existsInAddedIds(lineIdsAdded, lin_id1))
			{
				lineIdsAddedLoners.insert(lin_id1);
			}			
			if (!existsInAddedIds(lineIdsAdded, lin_id2))
			{
				lineIdsAddedLoners.insert(lin_id2);
			}
		}
		it++;
		it2++;
		if (it2 == isClosed.end())
		{
			// add loners
			for (auto& added : lineIdsAddedLoners)
			{
				if (!(lineIdsAdded.count(added) > 0))
				{
					// no matches add
					auto line_iter = mappedLines.find(added);
					std::vector<Line> lclLoner{ line_iter->second };
					groups.push_back(lclLoner);
				}
			}
			break;
		}
	}
}

void generateAndSortMultiSetPointsAndFindGroupsOfLines()
{
	Point p1a(1, 4);
	Point p2a(1, 1);
	Point p3a(1, 1);
	Point p4a(2, 1);
	Point p5a(5, 1);
	Point p6a(5, 2);
	Point p7a(5, 2);
	Point p8a(6, 2);
	Point p9a(8, 1);
	Point p10a(8, 3);
	Point p11a(8, 3);
	Point p12a(10, 1);
	Point p13a(10, 1);
	Point p14a(10, 3);
	Point p15a(4, 3);
	Point p16a(4, 5);
	Line l1(1, p1a, p2a);
	Line l2(2, p3a, p4a);
	Line l3(3, p5a, p6a);
	Line l4(4, p7a, p8a);
	Line l5(5, p9a, p10a);
	Line l6(6, p11a, p12a);
	Line l7(7, p13a, p14a);
	Line l8(8, p15a, p16a);
	//std::multiset<Line> setLinesmixed = { l6, l1, l2, l5, l3, l4, l7, l8 };
	std::multiset<Line> setLinesmixed = { l1, l5, l4, l8 };
	std::map<int, Line> mapLines;
	std::multiset<Point> setPointsClosed;
	std::vector<std::vector<Line>> groupedLines;
	std::cout << "" << std::endl;
	// assume all lines on 2d plane
	for (auto const& idx : setLinesmixed)
	{
		mapLines.insert(std::pair<int, Line>((int)idx.get_id(), idx));
		// points sorted by euclidian squared distance from origin
		setPointsClosed.insert(idx.my_endpoint1);
		setPointsClosed.insert(idx.my_endpoint2);
		std::cout << "id: " << idx.get_id() << " p1->p2 slope: " << (double)idx.point1_to_point2_slope() << " p2->p1 slope: " << (double)idx.point2_to_point1_slope() << std::endl;
	}
	std::cout << "" << std::endl;
	// pass the sorted points, the known lines map and grab the result from group passed by reference
	testGroups(setPointsClosed, mapLines, groupedLines);
	std::cout << "Groups:" << std::endl;
	int idx = 0;
	for (std::vector<Line> subgroups: groupedLines)
	{
		std::cout << "Group" << ++idx << ": "<< std::endl;
		for (Line line: subgroups)
		{
			std::cout << "Line: " << line.get_id() << std::endl;
		}
	}
}


void generateAndSortMultiSetPoints()
{
	Point p1a(1, 2);	
	Point p2a(4, 2);
	Point p3a(4, 2);
	Point p4a(5, 3);
	Point p5a(5, 3);
	Point p6a(8, 2);
	Point p7a(8, 2);
	Point p8a(7, 1);
	Point p9a(7, 1);
	Point p10a(3, 1);
	Point p11a(3, 1);
	Point p12a(1, 2);
	Point p13a(3, 1);
	Point p14a(1, 3);
	Line l1(1,p1a, p2a);
	Line l2(2,p3a, p4a);
	Line l3(3,p5a, p6a);
	Line l4(4,p7a, p8a);
	Line l5(5,p9a, p10a);
	Line l6(6,p11a, p12a);
	Line l7(7, p13a, p14a);
	std::multiset<Line> setLines = { l4, l1, l3, l5, l2, l6 };
	std::multiset<Line> setLinesmixed = { l6, l1, l2, l5, l3, l4 };
	std::multiset<Point> setPointsClosed;
	std::multiset<Line> setLinesNotClosed = { l4, l1, l3, l5, l2, l7 };
	std::multiset<Point> setPointsNotClosed;
	std::cout << "" << std::endl;
	for (auto const& idx : setLinesNotClosed)
	{
		setPointsNotClosed.insert(idx.my_endpoint1);
		setPointsNotClosed.insert(idx.my_endpoint2);
		std::cout << "id: "<< idx.get_id() << " p1->p2 slope: " << (double)idx.point1_to_point2_slope() << " p2->p1 slope: " << (double)idx.point2_to_point1_slope() << std::endl;
	}
	std::cout << "" << std::endl;
	for (auto const& idx : setLinesmixed)
	{
		setPointsClosed.insert(idx.my_endpoint1);
		setPointsClosed.insert(idx.my_endpoint2);
		std::cout << "id: " << idx.get_id() << " p1->p2 slope: " << (double)idx.point1_to_point2_slope() << " p2->p1 slope: " << (double)idx.point2_to_point1_slope() << std::endl;
	}
	std::cout << "" << std::endl;
	testClosed(setPointsNotClosed);
	std::cout << "" << std::endl;
	testClosed(setPointsClosed);
}



int main(int argc, char *argv[])
{
	std::cout << "in main" << std::endl;
	testStaticPolymorphism();
	testDynamicPolymorphism();
	testStrategyTemplates();
	generateAndSortMultiSetPoints();
	generateAndSortMultiSetPointsAndFindGroupsOfLines();

    getchar();
}