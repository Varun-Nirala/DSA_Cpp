#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "Ch_1_1.h"
#include "Ch_1_2.h"
#include "Ch_1_3.h"
#include "Ch_1_4.h"
#include "Ch_1_5.h"
#include "Ch_1_6.h"
#include "Ch_1_7.h"

#include "Ch_2_1.h"
#include "Ch_2_2.h"
#include "Ch_2_3.h"
#include "Ch_2_4.h"
#include "Ch_2_5.h"
#include "Ch_2_6.h"

#include "Ch_4_1.h"
#include "Ch_4_2.h"
#include "Ch_4_3.h"
#include "Ch_4_4.h"
#include "Ch_4_5.h"
#include "Ch_4_6.h"
#include "Ch_4_7.h"
#include "Ch_4_8.h"
#include "Ch_4_9.h"
#include "Ch_4_10.h"
#include "Ch_4_11.h"
#include "Ch_4_12.h"

#include "Ch_8_1.h"
#include "Ch_8_2.h"
#include "Ch_8_3.h"
#include "Ch_8_4.h"
#include "Ch_8_5.h"
#include "Ch_8_6.h"
#include "Ch_8_7.h"
#include "Ch_8_8.h"
#include "Ch_8_9.h"
#include "Ch_8_10.h"
#include "Ch_8_11.h"
#include "Ch_8_12.h"
#include "Ch_8_13.h"

#include "Ch_10_1.h"
#include "Ch_10_2.h"
#include "Ch_10_3.h"
#include "Ch_10_4.h"
#include "Ch_10_5.h"
#include "Ch_10_9.h"
#include "Ch_10_10.h"
#include "Ch_10_11.h"

#include "Ch_16_1.h"
#include "Ch_16_3.h"
#include "Ch_16_4.h"
#include "Ch_16_5.h"
#include "Ch_16_6.h"
#include "Ch_16_7.h"
#include "Ch_16_8.h"
#include "Ch_16_9.h"
#include "Ch_16_10.h"
#include "Ch_16_13.h"
#include "Ch_16_14.h"

using namespace std;

int** my2DAlloc(int row, int col)
{
	int headerSize = row * sizeof(int *);
	int dataSize = row * col * sizeof(int);

	int **arr = new int*[headerSize + dataSize];

	int *buf = (int *)(arr + row);
	for (int i = 0; i < row; ++i)
	{
		arr[i] = buf + i * col;
	}
	return arr;
}

int maxIndex(const vector<int> &vec, int index)
{
	if (index + 1 < vec.size())
	{
		int id = maxIndex(vec, index + 1);
		if (id != -1 && vec[index] > vec[id])
		{
			return index;
		}
		return id;
	}
	return index;
}

void findMax(const vector<int> &vec)
{
	if (vec.empty())
		return;

	int id = maxIndex(vec, 0);
	if (id > -1)
	{
		cout << "Max " << ", vec[" << id << "] = " << vec[id] << endl;
	}
}

void test2DAlloc()
{
	int row = 3;
	int col = 4;

	int** mat = my2DAlloc(row, col);

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; j++)
		{
			mat[i][j] = 0;
		}
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

void testFindMaxIndex()
{
	vector<int> vec{ 2, 1, 3, 4, 10, 2, 7, 8, 9 };

	findMax(vec);
}

int main()
{
	test2DAlloc();
	testFindMaxIndex();

	test_Ch_1_1();
	test_Ch_1_2();
	test_Ch_1_3();
	test_Ch_1_4();
	test_Ch_1_5();
	test_Ch_1_6();
	test_Ch_1_7();

	test_Ch_2_1();
	test_Ch_2_2();
	test_Ch_2_3();
	test_Ch_2_4();
	test_Ch_2_5();
	test_Ch_2_6();

	test_Ch_4_1();
	test_Ch_4_2();
	test_Ch_4_3();
	test_Ch_4_4();
	test_Ch_4_5();
	test_Ch_4_6();
	test_Ch_4_7();
	test_Ch_4_8();
	test_Ch_4_9();
	test_Ch_4_10();
	test_Ch_4_11();
	test_Ch_4_12();

	test_Ch_8_1();
	test_Ch_8_2();
	test_Ch_8_3();
	test_Ch_8_4();
	test_Ch_8_5();
	test_Ch_8_6();
	test_Ch_8_7();
	test_Ch_8_8();
	test_Ch_8_9();
	test_Ch_8_10();
	test_Ch_8_11();
	test_Ch_8_12();

	test_Ch_10_1();
	test_Ch_10_2();
	test_Ch_10_3();
	test_Ch_10_4();
	test_Ch_10_5();
	test_Ch_10_9();
	test_Ch_10_10();
	test_Ch_10_11();

	test_Ch_16_1();
	test_Ch_16_3();
	test_Ch_16_5();
	test_Ch_16_6();
	test_Ch_16_7();
	test_Ch_16_8();
	test_Ch_16_9();
	test_Ch_16_10();
	test_Ch_16_13();
	return 0;
}