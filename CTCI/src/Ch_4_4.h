#pragma once

/*
	Check Balanced :		Check if a binary tree is balanced.
						A balanced tree is defined to be a tree such that the heights of the two subtress of any node
						never differ by more than one.
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

	int checkHeight(Node *root)
	{
		if (!root)
		{
			return -1;
		}

		int leftHeight = checkHeight(root->lc);
		if (leftHeight == INT_MIN)
			return leftHeight;

		int rightHeight = checkHeight(root->rc);
		if (rightHeight == INT_MIN)
			return rightHeight;

		int hDiff = leftHeight - rightHeight;
		if (abs(hDiff) > 1)
			return INT_MIN;
		return max(leftHeight, rightHeight);
	}

public:
	Node* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalUtil(vec, 0, vec.size() - 1);
	}

	bool checkBalanced(Node *root)
	{
		return checkHeight(root) != INT_MIN;
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

	cout << boolalpha << sol.checkBalanced(root) << endl;


	return 0;
}