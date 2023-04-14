#pragma once

/*
	List Of Depths :		Given a binary tree, design an algorithm which creates a linked list of all
						the nodes at each depth (e.g., if you have a tree with depth D, you'll have D linked lists
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

	void createLevelLinkedListUtil(Node *root, vector<list<Node *>> &vList, int level)
	{
		if (!root)
			return;

		if (vList.size() == level)
		{
			vList.push_back({});
		}
		list<Node *> &l = vList[level];

		l.push_back(root);
		createLevelLinkedListUtil(root->lc, vList, level + 1);
		createLevelLinkedListUtil(root->rc, vList, level + 1);
	}

public:
	Node* createMinimal(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;

		return createMinimalUtil(vec, 0, vec.size() - 1);
	}

	vector<list<Node *>> createLevelLinkedList(Node *root)
	{
		vector<list<Node *>> vList;
		createLevelLinkedListUtil(root, vList, 0);
		return vList;
	}

	vector<list<Node *>> createLevelLinkedListIterative(Node *root)
	{
		vector<list<Node *>> vList;

		list<Node *> current;
		if (root)
		{
			current.push_back(root);
		}

		while (!current.empty())
		{
			vList.push_back(current);

			list<Node *> parent = current;
			current.clear();
			for (Node *n : parent)
			{
				if (n->lc)
				{
					current.push_back(n->lc);
				}
				if (n->rc)
				{
					current.push_back(n->rc);
				}
			}
		}

		return vList;
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

	vector<list<Node *>> vList = sol.createLevelLinkedListIterative(root);

	for (int i = 0; i < vList.size(); ++i)
	{
		for (Node *x : vList[i])
		{
			cout << x->val << " ";
		}
		cout << endl;
	}

	return 0;
}