#pragma once

/*
	First Common Ancestor :	Find First Common Ancestor of two nodes in a binary tree.
							Avoid storing additional nodes in a DS.
							NOTE : Tree is not necessarily a binary search tree.
*/


#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_8
{
public:
	map<int, BTreeNode*> mMap;

	// Considering there is a link to parent
	BTreeNode* commonAncestor_Sol_1(BTreeNode *pA, BTreeNode *pB)
	{
		int diff = getDepth(pA) - getDepth(pB);

		BTreeNode *pShallowNode = diff > 0 ? pB : pA;
		BTreeNode *pDeepNode = diff > 0 ? pA : pB;

		pDeepNode = goUpBy(pDeepNode, abs(diff));

		while (pShallowNode != pDeepNode && pShallowNode && pDeepNode)
		{
			pShallowNode = pShallowNode->parent;
			pDeepNode = pDeepNode->parent;
		}

		return !pShallowNode || !pDeepNode ? nullptr : pDeepNode;
	}

	// Considering there is a link to parent
	BTreeNode* commonAncestor_Sol_2(BTreeNode *pA, BTreeNode *pB)
	{
		if (covers(pA, pB))
		{
			return pA;
		}

		if (covers(pB, pA))
		{
			return pB;
		}

		BTreeNode *pSibling = getSibling(pA);
		BTreeNode *pParent = pA->parent;

		while (!covers(pSibling, pB))
		{
			pSibling = getSibling(pParent);
			pParent = pParent->parent;
		}

		return pParent;
	}

	// Considering there is NO link to parent
	BTreeNode* commonAncestor_Sol_3(BTreeNode *pRoot, BTreeNode *pA, BTreeNode *pB)
	{
		if (!pRoot || pRoot == pA || pRoot == pB)
		{
			return pRoot;
		}

		bool aIsOnLeft = covers(pRoot->lc, pA);
		bool bIsOnLeft = covers(pRoot->lc, pB);

		if (aIsOnLeft != bIsOnLeft)
		{
			return pRoot;
		}
		BTreeNode*childSide = aIsOnLeft ? pRoot->lc : pRoot->rc;
		return commonAncestor_Sol_3(childSide, pA, pB);
	}
private:

	BTreeNode* getSibling(BTreeNode *pNode)
	{
		if (!pNode || !pNode->parent)
		{
			return nullptr;
		}

		return pNode->parent->lc == pNode ? pNode->parent->rc : pNode->parent->lc;
	}

	bool covers(BTreeNode *pRoot, BTreeNode *pParent)		// check if p is under root
	{
		if (!pRoot)
		{
			return false;
		}

		if (pRoot == pParent)
		{
			return true;
		}

		return covers(pRoot->lc, pParent) || covers(pRoot->rc, pParent);
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

void test_Ch_4_8()
{
	Solution_4_8 sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, NULL_NODE, 8, 9, 10, 11, NULL_NODE, 12, 13 });

	BTreeNode *pRoot = createBinaryTree(vec, sol.mMap);

	cout << "InOrder Traversal \n";
	inorder(pRoot);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(pRoot);
	cout << endl;

	BTreeNode *pNode = sol.commonAncestor_Sol_3(pRoot, sol.mMap[8], sol.mMap[4]);

	if (!pNode)
	{
		cout << "NO COMMON ANCESTOR\n";
	}
	else
	{
		cout << pNode->val << endl;
	}
}