#pragma once

/*
	Random Node :	You are implementing a BST class from scratch, which in addition to insert, find and delete,
					has a method getRandomNode() which retirns a random node from the tree. All nodes should be equally
					likely to be chosen.
*/


#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

using namespace std;

const int NULL_NODE = INT_MIN;

typedef struct TreeNode
{
	int			val;
	int			size;
	TreeNode		*lc;
	TreeNode		*rc;

	TreeNode(int data)
		: val(data)
		, size(1)
		, lc(nullptr)
		, rc(nullptr)
	{}

	void insertInOrder(int data)
	{
		if (data < val)
		{
			if (lc)
			{
				lc->insertInOrder(data);
			}
			else
			{
				lc = new TreeNode(data);
			}
		}
		else
		{
			if (rc)
			{
				rc->insertInOrder(data);
			}
			else
			{
				rc = new TreeNode(data);
			}
		}
		size++;
	}

	TreeNode *getIthNode(int i)
	{
		int leftSize = lc == nullptr ? 0 : lc->size;

		if (i < leftSize)
		{
			return lc->getIthNode(i);
		}
		else if (i == leftSize)
		{
			return this;
		}
		else
		{
			return rc->getIthNode(i - (leftSize + 1));
		}
	}
}TreeNode;

void inorder(TreeNode *root)
{
	if (root)
	{
		inorder(root->lc);
		cout << root->val << " ";
		inorder(root->rc);
	}
}

void levelOrder(TreeNode *root)
{
	if (!root)
		return;
	queue<TreeNode *> que;
	que.push(root);

	int parentCount = 1;

	while (!que.empty())
	{
		TreeNode *node = que.front();
		que.pop();

		if (node)
		{
			cout << node->val << "[" << node->size << "]" << ", ";
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


class Solution
{
	TreeNode *root = nullptr;
public:
	int size()
	{
		return root->size;
	}

	void insertInOrder(int data)
	{
		if (!root)
		{
			root = new TreeNode(data);
			root->size = 0;
		}
		root->insertInOrder(data);
	}

	TreeNode* getRandom()
	{
		if (!root)
			return nullptr;

		int index = rand();
		cout << "Random no = " << index;
		index = index % size();
		cout << ", Norm no = " << index << " ";
		return root->getIthNode(index);
	}

	void printInOrder()
	{
		inorder(root);
	}

	void printLevelOrder()
	{
		levelOrder(root);
	}
};

int main()
{
	Solution sol;
	vector<int> vec({ 20, 10, 30, 5, 15, 35, 3, 7, 17 });

	for (auto &x : vec)
		sol.insertInOrder(x);

	cout << "InOrder Traversal \n";
	sol.printInOrder();
	cout << endl;

	cout << "LevelOrder Traversal \n";
	sol.printLevelOrder();
	cout << endl;

	for (int i = 0; i < vec.size() * 2; ++i)
	{
		cout << sol.getRandom()->val << endl;
	}

	return 0;
}