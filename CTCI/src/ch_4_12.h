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

using namespace std;

const int NULL_NODE = INT_MIN;

typedef struct Node
{
	int		val;
	Node		*lc;
	Node		*rc;
	Node		*parent;

	Node(int v, Node *p = nullptr)
		: val(v)
		, lc(nullptr)
		, rc(nullptr)
		, parent(p)
	{}
}Node;

class Solution
{
public:
	map<int, Node *> mMap;

	Node* createBinaryTree(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;
		int i = 0;
		Node *root = new Node(vec[i++]);

		mMap[root->val] = root;

		queue<Node *> que;
		que.push(root);

		while (i < vec.size())
		{
			Node *n = que.front();
			mMap[n->val] = n;
			que.pop();
			if (vec[i] != NULL_NODE)
			{
				n->lc = new Node(vec[i], n);
				que.push(n->lc);
				mMap[vec[i]] = n->lc;
			}
			i++;

			if (i < vec.size() && vec[i] != NULL_NODE)
			{
				n->rc = new Node(vec[i], n);
				que.push(n->rc);
				mMap[vec[i]] = n->rc;
			}
			i++;
		}
		return root;
	}

	int countPathWithSum(Node *root, int targetSum)
	{
		map<int, int> mm;
		return countPathsUtil(root, 0, targetSum, mm);
	}

private:
	int countPathsUtil(Node *node, int runningSum, const int targetSum, map<int, int> &mm)
	{
		if (!node)
			return 0;

		runningSum += node->val;

		int sum = runningSum - targetSum;
		int totalPaths = mm[sum];

		if (runningSum == targetSum)
		{
			totalPaths++;
		}

		incrementHashMap(mm, runningSum, 1);
		totalPaths += countPathsUtil(node->lc, runningSum, targetSum, mm);
		totalPaths += countPathsUtil(node->rc, runningSum, targetSum, mm);
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

void inorder(Node *root)
{
	if (root)
	{
		inorder(root->lc);
		cout << root->val << " ";
		inorder(root->rc);
	}
}

void levelOrder(Node *root)
{
	if (!root)
		return;
	queue<Node *> que;
	que.push(root);

	int parentCount = 1;

	while (!que.empty())
	{
		Node *node = que.front();
		que.pop();

		if (node)
		{
			cout << node->val << " ";
			que.push(node->lc);
			que.push(node->rc);
		}
		else
		{
			cout << "NULL ";
		}

		if (--parentCount == 0)
		{
			cout << endl;
			parentCount = que.size();
		}
	}
}

int main()
{
	Solution sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, NULL_NODE, 8, 9, 10, 11, NULL_NODE, 12, 13 });

	Node *root = sol.createBinaryTree(vec);

	cout << "InOrder Traversal\n";
	inorder(root);
	cout << endl;

	cout << "LevelOrder Traversal\n";
	levelOrder(root);
	cout << endl;

	cout << sol.countPathWithSum(root, 8) << endl;
	return 0;
}

