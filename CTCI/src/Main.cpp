#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

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

int main()
{
	int row = 3;
	int col = 4;

	int **mat = my2DAlloc(row, col);

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

	vector<int> vec { 2, 1, 3, 4, 10, 2, 7, 8, 9 };

	findMax(vec);

	return 0;
}