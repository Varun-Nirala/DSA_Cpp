#pragma once

/*
	Minimal Tree	 :	Given a sorted (increasing order) array with unique integer elements, wrtie an
					algorithm to create a binary search tree with minimal height
*/

#include <iostream>
#include <vector>
#include <queue>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_2
{
public:
	BTreeNode* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalBSTUtil(vec, 0, (int)vec.size() - 1);
	}
};

void test_Ch_4_2()
{
	Solution_4_2 sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });

	BTreeNode *pRoot = sol.createMinimal(vec);

	cout << "InOrder Traversal \n";
	inorder(pRoot);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(pRoot);
	cout << endl;
}