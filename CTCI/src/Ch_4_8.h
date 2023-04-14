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

	// Considering there is a link to parent
	Node* commonAncestor_Sol_1(Node *a, Node *b)
	{
		Node *ancestor = nullptr;

		int diff = getDepth(a) - getDepth(b);

		Node *shallowNode = diff > 0 ? b : a;
		Node *deepNode = diff > 0 ? a : b;

		deepNode = goUpBy(deepNode, abs(diff));

		while (shallowNode != deepNode && shallowNode && deepNode)
		{
			shallowNode = shallowNode->parent;
			deepNode = deepNode->parent;
		}

		return !shallowNode || !deepNode ? nullptr : deepNode;
	}

	// Considering there is a link to parent
	Node* commonAncestor_Sol_2(Node *a, Node *b)
	{
		if (covers(a, b))
			return a;

		if (covers(b, a))
			return b;

		Node *sibling = getSibling(a);
		Node *parent = a->parent;

		while (!covers(sibling, b))
		{
			sibling = getSibling(parent);
			parent = parent->parent;
		}

		return parent;
	}

	// Considering there is NO link to parent
	Node* commonAncestor_Sol_3(Node *root, Node *a, Node *b)
	{
		if (!root || root == a || root == b)
			return root;

		bool aIsOnLeft = covers(root->lc, a);
		bool bIsOnLeft = covers(root->lc, b);

		if (aIsOnLeft != bIsOnLeft)
			return root;
		Node *childSide = aIsOnLeft ? root->lc : root->rc;
		return commonAncestor_Sol_3(childSide, a, b);
	}
private:

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
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, NULL_NODE, 8, 9, 10, 11, NULL_NODE, 12, 13 });

	Node *root = sol.createBinaryTree(vec);

	cout << "InOrder Traversal \n";
	inorder(root);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(root);
	cout << endl;

	Node *n = sol.commonAncestor_Sol_3(root, sol.mMap[8], sol.mMap[4]);

	if (!n)
	{
		cout << "NO COMMON ANCESTOR\n";
	}
	else
	{
		cout << n->val << endl;
	}

	return 0;
}