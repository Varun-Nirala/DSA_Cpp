#pragma once

/*
	Search in rotated array :	Given a sorted array of n integers that has been rotated an unknown number of times.
								Write code to find an element in the array. You may assume that the array was originally
								sorted in increasing order.

								Example : 
									input : find 5 in (15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14)
									output : 8 (index of 5 in the array)
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "common.h"

using namespace std;

class Solution_10_3
{
	int search(const vector<int> &vec, int left, int right, int val)
	{
		int mid = (left + right) / 2;
		if (vec[mid] == val)
		{
			return mid;
		}

		if (right < left)
		{
			return -1;
		}

		if (vec[left] < vec[mid])	// Left is normally ordered;
		{
			if (val >= vec[left] && val < vec[mid])
			{
				return search(vec, left, mid - 1, val);
			}
			else
			{
				return search(vec, mid + 1, right, val);
			}
		}
		else if (vec[mid] < vec[right])	// Right is normally ordered;
		{
			if (val <= vec[right] && val > vec[mid])
			{
				return search(vec, mid + 1, right, val);
			}
			else
			{
				return search(vec, left, mid - 1, val);
			}
		}

		// it means left half or right half is all repeats
		if (vec[mid] != vec[right])	// If right is different search it
		{
			return search(vec, mid + 1, right, val);
		}
		else   // else we have to search both left and right
		{
			int id = search(vec, left, mid - 1, val);
			if (id == -1)
			{
				return search(vec, mid + 1, right, val);
			}
			else
			{
				return id;
			}
		}
	}

public:
	void find(const vector<int> &vec, int val)
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

void test_Ch_10_3()
{
	Solution_10_3 sol;
	vector<int> vec = { 15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14 };

	PrintArray(vec, std::string("\n\nPrinting Vec"));

	int num = 5;
	sol.find(vec, num);
}