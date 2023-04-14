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

using namespace std;

class Solution
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
		int id = search(vec, 0, vec.size() - 1, val);
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

template <typename T>
void PrintArray(const vector<T> &vec)
{
	cout << "Printing Array : ";
	for (auto x : vec)
	{
		cout << x << " ";
	}
	cout << endl;
}

int main()
{
	Solution sol;
	vector<string> vec = { "at", "", "", "", "ball", "", "", "cat", "", "", "dad", "" };

	PrintArray(vec);

	string str = "ball";

	sol.find(vec, str);

	return 0;
}