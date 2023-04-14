#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

namespace Searching_1 {
	static int LinearSearch(int arr[], int size, int val)	//O(1)
	{
		for (int i = 0; i < size; ++i)
		{
			if (arr[i] == val)
				return i;
		}
		return -1;
	}

	// A recursive binary search function. It returns 
	// location of x in given array arr[l..r] is present, 
	// otherwise -1 
	static int BinarySearch(int arr[], int l, int r, int val)	// O(logN)
	{
		if (r >= l)
		{
			int mid = l + (r - l) / 2;

			if (arr[mid] > val)
			{
				return BinarySearch(arr, mid + 1, r, val);
			}
			else if (arr[mid] < val)
			{
				return BinarySearch(arr, l, mid - 1, val);
			}
			else
			{
				return mid;
			}
		}
		return -1;
	}

	// Let’s consider the following array: (0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610).
	// Length of the array is 16. Jump search will find the value of 55 with the following steps assuming that the block size(m) to be jumped is 4.
	// STEP 1 : Jump from index 0 to index 4;
	// STEP 2: Jump from index 4 to index 8;
	// STEP 3: Jump from index 8 to index 12;
	// STEP 4: Since the element at index 12 is greater than 55 we will jump back a step to come to index 9.
	// STEP 5 : Perform linear search from index 9 to get the element 55.
	static int JumpSearch(int arr[], int size, int val)	// O(sqrt(n))
	{
		int m = sqrt(size);

		int startIndex = 0;
		int endIndex = m;

		while (arr[endIndex] < val)
		{
			startIndex = endIndex;
			endIndex += m;
			if (endIndex >= size)
			{
				return -1;
			}
		}

		for (startIndex; startIndex < endIndex; startIndex++)
		{
			if (arr[startIndex] == val)
			{
				return startIndex;
			}
		}
		return -1;
	}

	
	//	Let arr[0..n - 1] be the input array and element to be searched be x.
	//	
	//	Find the smallest Fibonacci Number greater than or equal to n.
	//	Let this number be fibM[m’th Fibonacci Number].Let the two Fibonacci numbers preceding it be fibMm1[(m - 1)’th Fibonacci Number] and fibMm2[(m - 2)’th Fibonacci Number].
	//	While the array has elements to be inspected :
	//		Compare x with the last element of the range covered by fibMm2
	//		If x matches, return index
	//		Else If x is less than the element, move the three Fibonacci variables two Fibonacci down, indicating elimination of approximately rear two - third of the remaining array.
	//		Else x is greater than the element, move the three Fibonacci variables one Fibonacci down.Reset offset to index.Together these indicate elimination of approximately front one - third of the remaining array.
	//		
	//		Since there might be a single element remaining for comparison, check if fibMm1 is 1. If Yes, compare x with that remaining element.If match, return index.
	static int FibSearch(int arr[], int size, int val)
	{
		int fibMm2 = 0, fibMm1 = 1, fibM = 0;

		fibM = fibMm1 + fibMm2;

		while (fibM < size)
		{
			fibMm2 = fibMm1;
			fibMm1 = fibM;
			fibM = fibMm2 + fibMm1;
		}

		int offset = -1;

		while (fibM > 1)
		{
			int i = min(offset + fibMm2, size - 1);

			if (arr[i] < val)
			{
				fibM = fibMm1;
				fibMm1 = fibMm2;
				fibMm2 = fibM - fibMm1;
				offset = i;
			}
			else if (arr[i] > val)
			{
				fibM = fibMm2;
				fibMm1 = fibMm1 - fibMm2;
				fibMm2 = fibM = fibMm1;
			}
			else
				return i;
		}

		if (fibMm1 && arr[offset + 1] == val)
		{
			return offset + 1;
		}

		return -1;
	}

	static int main(int argc, char *argv[])
	{
		int arr[] = { 2, 3, 4, 10, 40 };
		int x = 50;
		int n = sizeof(arr) / sizeof(arr[0]);
		int result = BinarySearch(arr, 0, n, x);
		(result == -1) ? cout << "Element is not present in array"
			: cout << "\nElement is present at index " << result << endl;

		result = JumpSearch(arr, n, x);
		(result == -1) ? cout << "\nElement is not present in array"
			: cout << "\nElement is present at index " << result << endl;

		int arr2[] = { 10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100 };
		n = sizeof(arr2) / sizeof(arr2[0]);
		x = 85;
		cout << "\nFound at index : " << FibSearch(arr2, n, x) << endl;
	
		return 0;
	}
}