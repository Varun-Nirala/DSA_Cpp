#pragma once

/*
	Recursive Multiply :		Write a recursive function to multiply two positive integers without using the 
							* operator (or / operator). You can use addition, substraction, and bit shifting, but you should minimize
							the number of those operations.
*/

#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

class Solution_8_5
{
	vector<int> memo;
	int multHelper(int smaller, int bigger)
	{
		if (smaller == 0)
			return 0;
		else if (smaller == 1)
			return bigger;

		int s = smaller >> 1;	//divide by 2
		int halfProduct = multHelper(s, bigger);

		if (smaller % 2 == 1)
		{
			return halfProduct + halfProduct + bigger;
		}
		else
		{
			return halfProduct + halfProduct;
		}
	}
public:
	int multiply(int a, int b)
	{
		int bigger = a < b ? b : a;
		int smaller = a < b ? a : b;

		return multHelper(smaller, bigger);
	}
};

void test_Ch_8_5()
{
	Solution_8_5 sol;

	cout << sol.multiply(177, 23) << endl;
}