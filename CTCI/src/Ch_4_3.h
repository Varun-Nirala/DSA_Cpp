#pragma once

/*
	List Of Depths :		Given a binary tree, design an algorithm which creates a linked list of all
						the nodes at each depth (e.g., if you have a tree with depth D, you'll have D linked lists
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_3
{
	void createLevelLinkedListUtil(BTreeNode *pRoot, vector<list<BTreeNode*>> &vList, int level)
	{
		if (!pRoot)
		{
			return;
		}

		if (vList.size() == level)
		{
			vList.push_back({});
		}
		list<BTreeNode*> &l = vList[level];

		l.push_back(pRoot);
		createLevelLinkedListUtil(pRoot->lc, vList, level + 1);
		createLevelLinkedListUtil(pRoot->rc, vList, level + 1);
	}

public:
	BTreeNode* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalBSTUtil(vec, 0, (int)vec.size() - 1);
	}

	vector<list<BTreeNode*>> createLevelLinkedList(BTreeNode *pRoot)
	{
		vector<list<BTreeNode*>> vList;
		createLevelLinkedListUtil(pRoot, vList, 0);
		return vList;
	}

	vector<list<BTreeNode*>> createLevelLinkedListIterative(BTreeNode *pRoot)
	{
		vector<list<BTreeNode*>> vList;

		list<BTreeNode*> current;
		if (pRoot)
		{
			current.push_back(pRoot);
		}

		while (!current.empty())
		{
			vList.push_back(current);

			list<BTreeNode*> parent = current;
			current.clear();
			for (BTreeNode *pNode : parent)
			{
				if (pNode->lc)
				{
					current.push_back(pNode->lc);
				}
				if (pNode->rc)
				{
					current.push_back(pNode->rc);
				}
			}
		}

		return vList;
	}
};

void test_Ch_4_3()
{
	Solution_4_3 sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });

	BTreeNode *pRoot = sol.createMinimal(vec);

	cout << "InOrder Traversal \n";
	inorder(pRoot);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(pRoot);
	cout << endl;

	vector<list<BTreeNode*>> vList = sol.createLevelLinkedListIterative(pRoot);

	for (int i = 0; i < vList.size(); ++i)
	{
		for (BTreeNode *pNode : vList[i])
		{
			cout << pNode->val << " ";
		}
		cout << endl;
	}
}