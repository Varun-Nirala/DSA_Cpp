#pragma once

/*
	Sorted Search, No Size :		You are given an array line DS Listy which lacks a size method. It does, however
								have an elementAt(i) method that returns the element at index i in O(1) time.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "common.h"

using namespace std;

class Listy
{
public:
	Listy(const initializer_list<int> &ll)
		:m_vec(ll)
	{}

	int elementAt(int i) const
	{
		return i < m_vec.size() ? m_vec[i] : -1;
	}

	vector<int> getVec()
	{
		return m_vec;
	}

private:
	vector<int>		m_vec;
};

class Solution_10_4
{
	int search(const Listy &listy, int left, int right, int val)
	{
		int mid;

		while (left <= right)
		{
			mid = (left + right) / 2;
			int middle = listy.elementAt(mid);

			if (middle > val || middle == -1)
			{
				return search(listy, left, mid - 1, val);
			}
			else if (middle < val)
			{
				return search(listy, mid + 1, right, val);
			}
			else
			{
				return mid;
			}
		}
		return -1;
	}

public:
	void find(const Listy &listy, int val)
	{
		cout << "searching for " << val << "\n";

		int id = 1;

		while (listy.elementAt(id) != -1 && listy.elementAt(id) < val)
		{
			id *= 2;
		}

		id = search(listy, id / 2, id, val);
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

void test_Ch_10_4()
{
	Solution_10_4 sol;
	Listy ll({ 1, 3, 4, 5, 7, 10, 14, 15, 16, 19, 20, 25 });

	PrintArray(ll.getVec(), std::string("\n\nPrinting Array"));

	sol.find(ll, 25);
}