#pragma once

/*
`	Check SubTree : T1 and T2 are two very large binary tree, with T1 much bigger than T2.
					Determine if T2 is a subtree of T1
*/
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_10
{
public:
	map<int, BTreeNode*> mMap;

	bool contains(BTreeNode *pA, BTreeNode *pB)
	{
		if (!pB)
		{
			return true;	// Null tree is always a sub tree
		}
		return subTree(pA, pB);
	}

private:
	bool subTree(BTreeNode *pA, BTreeNode *pB)
	{
		if (!pA)
		{
			return false;
		}
		else if (pA->val == pB->val && match(pA, pB))
		{
			return true;
		}
		return subTree(pA->lc, pB) || subTree(pA->rc, pB);
	}

	bool match(BTreeNode *pA, BTreeNode *pB)
	{
		if (!pA && !pB)
		{
			return true;
		}
		else if (!pA || !pB)
		{
			return false;
		}
		else if (pA->val != pB->val)
		{
			return false;
		}
		return match(pA->lc, pB->lc) && match(pA->rc, pB->rc);
	}

	BTreeNode* getSibling(BTreeNode *pNode)
	{
		if (!pNode || !pNode->parent)
		{
			return nullptr;
		}

		return pNode->parent->lc == pNode ? pNode->parent->rc : pNode->parent->lc;
	}

	bool covers(BTreeNode* pRoot, BTreeNode* p)		// check if p is under root
	{
		if (!pRoot)
		{
			return false;
		}

		if (pRoot == p)
		{
			return true;
		}

		return covers(pRoot->lc, p) || covers(pRoot->rc, p);
	}

	int getDepth(BTreeNode *pNode)
	{
		int depth = 0;
		while (pNode)
		{
			pNode = pNode->parent;
			depth++;
		}
		return depth;
	}

	BTreeNode* goUpBy(BTreeNode *pNode, int up)
	{
		while (up > 0 && pNode)
		{
			up--;
		}
		return pNode;
	}
};

void test_Ch_4_10()
{
	Solution_4_10 sol1;
	Solution_4_10 sol2;
	vector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, NULL_NODE, 8, 9, 10, 11, NULL_NODE, 12, 13 });
	vector<int> vec2({ 4, NULL_NODE, 8 });

	BTreeNode *t1 = createBinaryTree(vec1, sol1.mMap);
	BTreeNode *t2 = createBinaryTree(vec2, sol2.mMap);

	cout << "InOrder Traversal of t1\n";
	inorder(t1);
	cout << endl;

	cout << "LevelOrder Traversal of t1\n";
	levelOrder(t1);
	cout << endl;

	cout << "InOrder Traversal of t2\n";
	inorder(t2);
	cout << endl;

	cout << "LevelOrder Traversal of t2\n";
	levelOrder(t2);
	cout << endl;

	cout << "Does T1 contains t2 ? : " << boolalpha << sol1.contains(t1, t2) << endl;
}
