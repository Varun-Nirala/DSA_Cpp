#pragma once

/*
	Paths with sum :		You are given a binary tree n which each node contains an integer value (+ve or -ve).
						Design an algorithm to count the number of paths that sum to a given value.The path does
						not need to start or end at the root or a leaf, but it must go downwards.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_12
{
public:
	map<int, BTreeNode*> mMap;

	int countPathWithSum(BTreeNode *pRoot, int targetSum)
	{
		map<int, int> mm;
		return countPathsUtil(pRoot, 0, targetSum, mm);
	}

private:
	int countPathsUtil(BTreeNode *pNode, int runningSum, const int targetSum, map<int, int> &mm)
	{
		if (!pNode)
		{
			return 0;
		}

		runningSum += pNode->val;

		int sum = runningSum - targetSum;
		int totalPaths = mm[sum];

		if (runningSum == targetSum)
		{
			totalPaths++;
		}

		incrementHashMap(mm, runningSum, 1);
		totalPaths += countPathsUtil(pNode->lc, runningSum, targetSum, mm);
		totalPaths += countPathsUtil(pNode->rc, runningSum, targetSum, mm);
		incrementHashMap(mm, runningSum, -1);
		return totalPaths;
	}

	void incrementHashMap(map<int, int> &mm, int key, int delta)
	{
		int newVal = mm[key] + delta;
		if (newVal == 0)
			mm.erase(key);
		else
			mm[key] = newVal;
	}
};

void test_Ch_4_12()
{
	Solution_4_12 sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, NULL_NODE, 8, 9, 10, 11, NULL_NODE, 12, 13 });

	BTreeNode *pRoot = createBinaryTree(vec, sol.mMap);

	cout << "InOrder Traversal\n";
	inorder(pRoot);
	cout << endl;

	cout << "LevelOrder Traversal\n";
	levelOrder(pRoot);
	cout << endl;

	cout << sol.countPathWithSum(pRoot, 8) << endl;
}