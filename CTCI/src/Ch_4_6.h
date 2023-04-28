#pragma once

/*
	Successor :		Find next Node (i.e Inorder successor Node) of a given node in a binary search tree
					Assume that each node point to its parent.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_6
{
	BTreeNode* leftMostChild(BTreeNode *pNode)
	{
		if (!pNode)
		{
			return nullptr;
		}

		while (pNode->lc)
		{
			pNode = pNode->lc;
		}
		return pNode;
	}

public:
	BTreeNode* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalBSTUtil(vec, 0, (int)vec.size() - 1, nullptr);
	}

	BTreeNode* getInOrderSuccessor(BTreeNode *pNode)
	{
		if (!pNode)
		{
			return nullptr;
		}

		if (pNode->rc)
		{
			// easy one, return it's left most child
			return leftMostChild(pNode->rc);
		}
		else
		{
			BTreeNode *q = pNode;
			BTreeNode *x = q->parent;

			while (x && x->lc != q)
			{
				q = x;
				x = x->parent;
			}
			return x;
		}
	}

	BTreeNode *getNode(BTreeNode *pRoot, int val)
	{
		if (pRoot->val == val)
		{
			return pRoot;
		}
		if (pRoot->val < val)
		{
			return getNode(pRoot->rc, val);
		}
		return getNode(pRoot->lc, val);
	}
};

void test_Ch_4_6()
{
	Solution_4_6 sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });

	BTreeNode *pRoot = sol.createMinimal(vec);

	cout << "InOrder Traversal \n";
	inorder(pRoot);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(pRoot);
	cout << endl;

	BTreeNode *pNode = sol.getInOrderSuccessor(pRoot);
	cout << pNode->val << endl;

	pNode = sol.getNode(pRoot, 7);

	BTreeNode *node1 = sol.getInOrderSuccessor(pNode);
	cout << node1->val << endl;
}
