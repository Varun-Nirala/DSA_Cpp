#pragma once

/*
	Number max :		Write a method that finds the maximun of two numbers. You should not use if-else or
					any other comparision operator.

					Number are : a and b
					Logic behind its solution:
						let k = sign of (a - b) such that if (a - b) >= 0 then k = 1, else k = 0
						let q = inverse of k
						then max of a and b will be a * k + b * q;

					Let check that out with an 
					example 1
						a = 9
						b = 10
							then (a - b) => -1, 
								so  k = 0
								and q = 1
								max = k * a + b * q => 0 * 9 + 1 * 10 => 10

					example 2
						a = 10
						b = 9
							then (a - b) => 1,
								so  k = 1
								and q = 0
								max = k * a + b * q => 1 * 10 + 0 * 9 => 10


					But it crumble if (a-b) overflows, so to fix that
					we need to modify it a little bit.
					We also need to check if signs are same or different, 
					as it only overflows when both are of different sign
					otherwise our above algo work fine

					so our modification will be in assigning value to k
					if a and b are of same sign, then k = sign(a-b)
					otherwise k = sign(a) or slip of sign of b (will use former one)
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution_16_7
{
	/* Flips a 1 to 0 and a 0 to 1 */
	int flip(int bit)
	{
		return 1 ^ bit;
	}

	/* Returns 1 if num is positive, and 0 if num is negative */
	int sign(int num)
	{
		return flip((num >> 31) & 1);
	}
public:
	int numberMax(int a, int b)
	{
		int c = a - b;
		int sa = sign(a);	// if a > 0 then 1 else 0
		int sb = sign(b);	// if b > 0 then 1 else 0
		int sc = sign(c);	// Depens on whether or not (a - b) overflows

		/* if a and b have different sign */
		/* if a > 0, then b < 0 and k = 1 */
		/* if b > 0, then a < 0 and k = 0 */

		// if a and b have different signs, then k = sign(a)
		int useSignOfA = sa ^ sb;			// Will be 0 if same sign otherwise 1

		// if a and b have same signs, then k = sign(a - b)
		int useSignOfC = flip(sa ^ sb);		// Will be 1 if same sign otherwise 0

		int k = useSignOfA * sa + useSignOfC * sc;
		int q = flip(k);

		return a * k + b * q;
	}
};

void test_Ch_16_7()
{
	int numA = 9;
	int numB = 10;
	Solution_16_7 sol;
	cout << "Max of (" << numA << ", " << numB << ") is " << sol.numberMax(numA, numB) << endl;
}