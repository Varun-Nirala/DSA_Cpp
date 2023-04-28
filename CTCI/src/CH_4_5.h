#pragma once

/*
	Validate BST	 :	Check if given binary tree is BST
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_5
{
	struct Integer
	{
		int		val = 0;
		bool		initialized = false;

		Integer() {}

		explicit Integer(int v)
			: val(v)
			, initialized(true)
		{}
	};

	bool isBSTUtil(BTreeNode *pRoot, Integer min, Integer max)
	{
		if (!pRoot)
		{
			return true;
		}

		if ((min.initialized && pRoot->val <= min.val) || (max.initialized && pRoot->val > max.val))
		{
			return false;
		}

		if (!isBSTUtil(pRoot->lc, min, Integer(pRoot->val)) || !isBSTUtil(pRoot->rc, Integer(pRoot->val), max))
		{
			return false;
		}
		return true;
	}
public:
	BTreeNode* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalBSTUtil(vec, 0, (int)vec.size() - 1);
	}

	bool checkIsBST(BTreeNode *pRoot)
	{
		return isBSTUtil(pRoot, Integer(), Integer());
	}
};

void test_Ch_4_5()
{
	Solution_4_5 sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });

	BTreeNode *pRoot = sol.createMinimal(vec);

	cout << "InOrder Traversal \n";
	inorder(pRoot);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(pRoot);
	cout << endl;

	cout << boolalpha << sol.checkIsBST(pRoot) << endl;
}
