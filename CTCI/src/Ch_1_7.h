#pragma once

/*
	Rotate Matrix 90 degree Clockwise :
		Given NxN matrix rotate it 90 degree clockwise
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	bool rotate90(vector<vector<char>> &mat)
	{
		if (mat.size() == 0 || mat.size() != mat[0].size())
			return false;

		int n = mat.size();
		for (int layer = 0; layer < n / 2; layer++)
		{
			int first = layer;
			int last = n - 1 - layer;

			for (int i = first; i < last; ++i)
			{
				int offset = i - first;

				int top = mat[first][i];	// Save top

				// left->top
				mat[first][i] = mat[last - offset][first];

				// bottom->left
				mat[last - offset][first] = mat[last][last - offset];

				// right->bottom
				mat[last][last - offset] = mat[i][last];

				// top->right
				mat[i][last] = top;	//right <- saved top
			}
		}
		return true;
	}
};

int main()
{
	vector<vector<char>> input{
		{ 'a', 'b', 'c', 'd', 'e' },
		{ 'p', 'q', 'r', 's', 'f' },
		{ 'o', 'x', 'y', 't', 'g' },
		{ 'n', 'w', 'v', 'u', 'h' },
		{ 'm', 'l', 'k', 'j', 'i' }
	};

	vector<vector<char>> output{
		{ 'm', 'n', 'o', 'p', 'a' },
		{ 'l', 'w', 'x', 'q', 'b' },
		{ 'k', 'v', 'y', 'r', 'c' },
		{ 'j', 'u', 't', 's', 'd' },
		{ 'i', 'h', 'g', 'f', 'e' }
	};

	Solution sol;

	sol.rotate90(input);

	if (input == output)
	{
		cout << "PASSED\n";
	}
	else
	{
		cout << "FAILED\n";
	}
	return 0;
}

