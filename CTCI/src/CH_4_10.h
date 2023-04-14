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

	bool contains(Node *t1, Node *t2)
	{
		if (!t2)
			return true;	// Null tree is always a sub tree
		return subTree(t1, t2);
	}

private:
	bool subTree(Node *t1, Node *t2)
	{
		if (!t1)
		{
			return false;
		}
		else if (t1->val == t2->val && match(t1, t2))
		{
			return true;
		}
		return subTree(t1->lc, t2) || subTree(t1->rc, t2);
	}

	bool match(Node *t1, Node *t2)
	{
		if (!t1 && !t2)
			return true;
		else if (!t1 || !t2)
			return false;
		else if (t1->val != t2->val)
			return false;
		return match(t1->lc, t2->lc) && match(t1->rc, t2->rc);
	}

	Node* getSibling(Node *n)
	{
		if (!n || !n->parent)
			return nullptr;

		return n->parent->lc == n ? n->parent->rc : n->parent->lc;
	}

	bool covers(Node *root, Node *p)		// check if p is under root
	{
		if (!root) 	return false;
		if (root == p) return true;

		return covers(root->lc, p) || covers(root->rc, p);
	}

	int getDepth(Node *node)
	{
		int depth = 0;
		while (node)
		{
			node = node->parent;
			depth++;
		}
		return depth;
	}

	Node* goUpBy(Node *node, int up)
	{
		while (up > 0 && node)
		{
			up--;
		}
		return node;
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
	vector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, NULL_NODE, 8, 9, 10, 11, NULL_NODE, 12, 13 });
	vector<int> vec2({ 4, NULL_NODE, 8 });

	Node *t1 = sol.createBinaryTree(vec1);
	Node *t2 = sol.createBinaryTree(vec2);

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

	cout << "Does T1 contains t2 ? : " << boolalpha << sol.contains(t1, t2) << endl;

	return 0;
}
