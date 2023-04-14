#pragma once

/*
	Validate BST	 :	Check if given binary tree is BST
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

typedef struct Node
{
	int		val;
	Node		*lc;
	Node		*rc;

	Node(int v)
		: val(v)
		, lc(nullptr)
		, rc(nullptr)
	{}
}Node;

class Solution
{
	Node *createMinimalUtil(vector<int> &vec, int start, int end)
	{
		if (start <= end)
		{
			int mid = (start + end) / 2;
			Node *node = new Node(vec[mid]);
			node->lc = createMinimalUtil(vec, start, mid - 1);
			node->rc = createMinimalUtil(vec, mid + 1, end);
			return node;
		}
		return nullptr;
	}

	typedef struct Integer
	{
		int		val = 0;
		bool		initialized = false;

		Integer() {}

		explicit Integer(int v)
			: val(v)
			, initialized(true)
		{}
	}Integer;

	bool isBSTUtil(Node *root, Integer min, Integer max)
	{
		if (!root)
		{
			return true;
		}

		if ((min.initialized && root->val <= min.val) || (max.initialized && root->val > max.val))
		{
			return false;
		}

		if (!isBSTUtil(root->lc, min, Integer(root->val)) || !isBSTUtil(root->rc, Integer(root->val), max))
		{
			return false;
		}
		return true;
	}
public:
	Node* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalUtil(vec, 0, vec.size() - 1);
	}

	bool checkIsBST(Node *root)
	{
		return isBSTUtil(root, Integer(), Integer());
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
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });

	Node *root = sol.createMinimal(vec);

	cout << "InOrder Traversal \n";
	inorder(root);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(root);
	cout << endl;

	cout << boolalpha << sol.checkIsBST(root) << endl;


	return 0;
}
