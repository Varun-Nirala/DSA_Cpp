#pragma once

/*
	Sparse search :	Given a sorted array of strings that is interspersed with empty strings, write a method
					to find the location of a given string.

					Example : ball, { "at", "", "", "", "ball", "", "", "cat", "", "", "dad", "" }
						ouput : 4
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "common.h"

using namespace std;

class Solution_10_5
{
	int search(const vector<string> &vec, int left, int right, string val)
	{
		int mid = (left + right) / 2;

		if (vec[mid] == val)
			return mid;

		if (right < left)
			return -1;

		if (vec[mid] == "")
		{
			int lt = mid - 1;
			int rt = mid + 1;

			while (true)
			{
				if (lt < left && rt > right)
				{
					return -1;
				}
				else if (rt <= right && !vec[rt].empty())
				{
					mid = rt;
					break;
				}
				else if (lt >= left && !vec[lt].empty())
				{
					mid = lt;
					break;
				}
				lt--;
				rt++;
			}
		}

		if (val == vec[mid])
		{
			return mid;
		}
		else if (vec[mid] < val)
		{
			return search(vec, mid + 1, right, val);
		}
		else
		{
			return search(vec, left, mid - 1, val);
		}
	}

public:
	void find(const vector<string> &vec, string val)
	{
		cout << "searching for " << val << "\n";
		int id = search(vec, 0, (int)vec.size() - 1, val);
		if (id != -1)
		{
			cout << "Found " << "vec[" << id << "] = " << val << endl;
		}
		else
		{
			cout << "Not Found\n";
		}
	}
};

void test_Ch_10_5()
{
	Solution_10_5 sol;
	vector<string> vec = { "at", "", "", "", "ball", "", "", "cat", "", "", "dad", "" };

	PrintArray(vec, std::string("\n\nPrinting Array"));

	string str = "ball";

	sol.find(vec, str);
}