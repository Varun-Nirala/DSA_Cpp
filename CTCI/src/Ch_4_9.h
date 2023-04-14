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

	Node* createBST(vector<int> &vec)
	{
		if (vec.empty())
			return nullptr;
		int i = 0;
		Node *root = new Node(vec[i++]);
		mMap[root->val] = root;
		while (i < vec.size())
		{
			push(root, vec[i++]);
		}

		return root;
	}

	vector<list<int>> BST_Sequences(Node *root)
	{
		vector<list<int>> result;

		if (!root)
		{
			result.push_back({});	// add empty list
			return result;
		}

		list<int> prefix;
		prefix.push_back(root->val);

		/* Recurse on left and right subtrees */
		vector<list<int>> leftSeq = BST_Sequences(root->lc);
		vector<list<int>> rightSeq = BST_Sequences(root->rc);

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

	void push(Node *root, int val)
	{
		if (root->val == val)
		{
			return;
		}
		else if (root->val < val)
		{
			if (root->rc)
			{
				push(root->rc, val);
			}
			else
			{
				root->rc = new Node(val);
				mMap[val] = root->rc;
				return;
			}
		}
		else
		{
			if (root->lc)
			{
				push(root->lc, val);
			}
			else
			{
				root->lc = new Node(val);
				mMap[val] = root->lc;
				return;
			}
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
	vector<int> vec({ 2, 3, 1 });

	Node *root = sol.createBST(vec);

	cout << "InOrder Traversal \n";
	inorder(root);
	cout << endl;

	cout << "LevelOrder Traversal \n";
	levelOrder(root);
	cout << endl;

	vector<list<int>> ans = sol.BST_Sequences(root);

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

	return 0;
}

