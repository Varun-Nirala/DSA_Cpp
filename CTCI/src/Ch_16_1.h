#pragma once

/*
	Number swapper : Write a function to swap a number in place (that is, without temporary variable)
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution
{
public:
	void swap1(int &a, int &b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}

	void swap2(int &a, int &b)
	{
		a = a - b;
		b = a + b;
		a = b - a;
	}

	void swap3(int &a, int &b)
	{
		a = a ^ b;
		b = a ^ b;
		a = b ^ a;
	}
};

int main()
{
	Solution sol;
	int a = 9;
	int b = 5;

	cout << "Before swapping : a = " << a << ", b = " << b << endl;
	sol.swap3(a, b);
	cout << "After swapping : a = " << a << ", b = " << b << endl;
	return 0;
}