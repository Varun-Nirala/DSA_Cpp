#pragma once

/*
	Check Balanced :		Check if a binary tree is balanced.
						A balanced tree is defined to be a tree such that the heights of the two subtress of any node
						never differ by more than one.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_4
{
	int checkHeight(BTreeNode *pRoot)
	{
		if (!pRoot)
		{
			return -1;
		}

		int leftHeight = checkHeight(pRoot->lc);
		if (leftHeight == INT_MIN)
			return leftHeight;

		int rightHeight = checkHeight(pRoot->rc);
		if (rightHeight == INT_MIN)
			return rightHeight;

		int hDiff = leftHeight - rightHeight;
		if (abs(hDiff) > 1)
			return INT_MIN;
		return max(leftHeight, rightHeight);
	}

public:
	BTreeNode* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalBSTUtil(vec, 0, (int)vec.size() - 1);
	}

	bool checkBalanced(BTreeNode *pRoot)
	{
		return checkHeight(pRoot) != INT_MIN;
	}
};

void test_Ch_4_4()
{
	Solution_4_4 sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });

	BTreeNode *pRoot = sol.createMinimal(vec);

	cout << "InOrder Traversal \n";
	inorder(pRoot);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(pRoot);
	cout << endl;

	cout << boolalpha << sol.checkBalanced(pRoot) << endl;
}