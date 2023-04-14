#pragma once

/*
	Minimal Tree	 :	Given a sorted (increasing order) array with unique integer elements, wrtie an
					algorithm to create a binary search tree with minimal height
*/

#include <iostream>
#include <vector>
#include <queue>

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

public:
	Node* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalUtil(vec, 0, vec.size() - 1);
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

	return 0;
}