#pragma once

#include "helper.h"

int binSearch(int *arr, int low, int high, int value)
{
	if (low > high)
		return -1;

	int mid = (low + high) / 2;

	if (arr[mid] == value)
		return mid;
	else if (arr[mid] < value)
		binSearch(arr, mid + 1, high, value);
	else
		binSearch(arr, low, mid - 1, value);
}

void test_binSearch()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	int size = sizeof(arr) / sizeof(arr[0]);

	printArray(arr, size);

	int val = 2;
	cout << "Searching for " << val << " -> found at " << binSearch(arr, 0, size - 1, val) << endl;

	val = 1;
	cout << "Searching for " << val << " -> found at " << binSearch(arr, 0, size - 1, val) << endl;

	val = 10;
	cout << "Searching for " << val << " -> found at " << binSearch(arr, 0, size - 1, val) << endl;

	val = 11;
	cout << "Searching for " << val << " -> found at " << binSearch(arr, 0, size - 1, val) << endl;
}
