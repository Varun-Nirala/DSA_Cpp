#pragma once

/*
	BST Sequences :	A BST was created by traversing through an array from left to right and inserting each element.
					Given a BST with distinct elements, print all possible arrays that could have let to this tree.
*/


#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_9
{
public:
	map<int, BTreeNode*> mMap;

	BTreeNode* createBST(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;
		int i = 0;
		BTreeNode *pRoot = new BTreeNode(vec[i++]);
		mMap[pRoot->val] = pRoot;
		while (i < vec.size())
		{
			push(pRoot, vec[i++]);
		}

		return pRoot;
	}

	vector<list<int>> BST_Sequences(BTreeNode *pRoot)
	{
		vector<list<int>> result;

		if (!pRoot)
		{
			result.push_back({});	// add empty list
			return result;
		}

		list<int> prefix;
		prefix.push_back(pRoot->val);

		/* Recurse on left and right subtrees */
		vector<list<int>> leftSeq = BST_Sequences(pRoot->lc);
		vector<list<int>> rightSeq = BST_Sequences(pRoot->rc);

		/* Weave together each list from the left and right sides */
		for (auto &left : leftSeq)
		{
			for (auto &right : rightSeq)
			{
				vector<list<int>> weaved;
				weaveLists(left, right, weaved, prefix);
				result.insert(result.end(), weaved.begin(), weaved.end());
			}
		}
		return result;
	}
private:
	void weaveLists(list<int> &first, list<int> &second, vector<list<int>> &results, list<int> prefix)
	{
		/*One list is empty. Add remainder to [a cloned] prefix and store result */
		if (first.empty() || second.empty())
		{
			prefix.insert(prefix.end(), first.begin(), first.end());
			prefix.insert(prefix.end(), second.begin(), second.end());
			results.push_back(prefix);
			return;
		}

		int headFirst = first.front();
		first.pop_front();
		prefix.push_back(headFirst);
		weaveLists(first, second, results, prefix);
		prefix.pop_back();
		first.insert(first.begin(), headFirst);

		int headSecond = second.front();
		second.pop_front();
		prefix.push_back(headSecond);
		weaveLists(first, second, results, prefix);
		prefix.pop_back();
		second.insert(second.begin(), headSecond);
	}

	void push(BTreeNode *pRoot, int val)
	{
		if (pRoot->val == val)
		{
			return;
		}
		else if (pRoot->val < val)
		{
			if (pRoot->rc)
			{
				push(pRoot->rc, val);
			}
			else
			{
				pRoot->rc = new BTreeNode(val);
				mMap[val] = pRoot->rc;
				return;
			}
		}
		else
		{
			if (pRoot->lc)
			{
				push(pRoot->lc, val);
			}
			else
			{
				pRoot->lc = new BTreeNode(val);
				mMap[val] = pRoot->lc;
				return;
			}
		}
	}
};
void test_Ch_4_9()
{
	Solution_4_9 sol;
	vector<int> vec({ 2, 3, 1 });

	BTreeNode *pRoot = sol.createBST(vec);

	cout << "InOrder Traversal \n";
	inorder(pRoot);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(pRoot);
	cout << endl;

	vector<list<int>> ans = sol.BST_Sequences(pRoot);

	for (int i = 0; i < ans.size(); ++i)
	{
		list<int> &l = ans[i];
		while (!l.empty())
		{
			cout << l.front() << " ";
			l.pop_front();
		}
		cout << endl;
	}
}