#pragma once

/*
	Successor :		Find next Node (i.e Inorder successor Node) of a given node in a binary search tree
					Assume that each node point to its parent.
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
	Node *createMinimalUtil(vector<int> &vec, int start, int end, Node *p)
	{
		if (start <= end)
		{
			int mid = (start + end) / 2;
			Node *node = new Node(vec[mid], p);
			node->lc = createMinimalUtil(vec, start, mid - 1, node);
			node->rc = createMinimalUtil(vec, mid + 1, end, node);
			return node;
		}
		return nullptr;
	}

	Node* leftMostChild(Node *node)
	{
		if (!node)
			return nullptr;

		while (node->lc)
		{
			node = node->lc;
		}
		return node;
	}

public:
	Node* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalUtil(vec, 0, vec.size() - 1, nullptr);
	}

	Node* getInOrderSuccessor(Node *node)
	{
		if (!node)
			return nullptr;

		if (node->rc)
		{
			// easy one, return it's left most child
			return leftMostChild(node->rc);
		}
		else
		{
			Node *q = node;
			Node *x = q->parent;

			while (x && x->lc != q)
			{
				q = x;
				x = x->parent;
			}
			return x;
		}
	}

	Node *getNode(Node *root, int val)
	{
		if (root->val == val)
		{
			return root;
		}
		if (root->val < val)
		{
			return getNode(root->rc, val);
		}
		if (root->val > val)
		{
			return getNode(root->lc, val);
		}
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

	Node *node = sol.getInOrderSuccessor(root);
	cout << node->val << endl;

	node = sol.getNode(root, 7);

	Node *node1 = sol.getInOrderSuccessor(node);
	cout << node1->val << endl;

	return 0;
}
