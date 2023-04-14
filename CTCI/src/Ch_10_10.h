#pragma once

/*
	Rank from Stream :	Imagine you are reading in a stream of integers. Periodically, you wish to be able to look up the rank of a number x
						(the number of values <= x). Implement the data structures and algorithm to support these operations.
						That is, implement the method track(int x), which is called when each number is generated and the method getRankOfNumber(int x)
						, which returns the number of values <= x (not including this x itself).

						Example :
							Stream (in order of appearance) : 5, 1, 4, 4, 5, 9, 7, 13, 3
							getRankOfNumber(1) = 0
							getRankOfNumber(3) = 1
							getRankOfNumber(4) = 3
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef struct RankedNode
{
	RankedNode	*lc;
	RankedNode	*rc;
	int			val;
	int			leftSize;

	RankedNode(int data)
		: val(data)
		, lc(nullptr)
		, rc(nullptr)
		, leftSize(0)
	{}

	void insert(int data)
	{
		if (data <= val)
		{
			if (lc) { lc->insert(data); }
			else { lc = new RankedNode(data); }
			leftSize++;
		}
		else
		{
			if (rc) { rc->insert(data); }
			else { rc = new RankedNode(data); }
		}
	}

	int getRank(int data)
	{
		if (val == data)
		{
			return leftSize;
		}
		else if (data < val)
		{
			if (!lc)
			{
				return -1;
			}
			else
			{
				return lc->getRank(data);
			}
		}
		else
		{
			int rightRank = (rc == nullptr ? -1 : rc->getRank(data));
			if (rightRank == -1)
			{
				return -1;
			}
			else
			{
				return leftSize + 1 + rightRank;
			}
		}
	}
}RankedNode;

class Solution
{
public:
	Solution(const vector<int> &vec)
		: root(nullptr)
	{
		for (auto &x : vec)
		{
			insert(x);
		}
	}

	void insert(int val)
	{
		if (!root)
		{
			root = new RankedNode(val);
		}
		else
		{
			root->insert(val);
		}
	}

	int getRank(int val)
	{
		return root->getRank(val);
	}

private:
	RankedNode *root = nullptr;
};

int main()
{
	//vector<int> vecIn{ 20, 15, 25, 10, 23, 5, 13, 24 };
	vector<int> vecIn{5, 1, 4, 4, 5, 9, 7, 13, 3};
	vector<int> vecRank{1, 3, 4};
	Solution sol(vecIn);

	for (auto x : vecRank)
	{
		cout << "Rank of " << x << " => " << sol.getRank(x) << endl;
	}

	return 0;
}
