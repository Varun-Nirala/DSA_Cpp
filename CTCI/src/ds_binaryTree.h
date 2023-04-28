#pragma once

#include <queue>
#include <vector>
#include <map>
#include <iostream>

struct BTreeNode
{
	int			val{};
	BTreeNode	*lc{};
	BTreeNode	*rc{};
	BTreeNode	*parent{};
	int			size{1};

	BTreeNode(int v, BTreeNode *p = nullptr)
		: val(v)
		, parent(p)
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
				lc = new BTreeNode(data);
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
				rc = new BTreeNode(data);
			}
		}
		size++;
	}

	BTreeNode* getIthNode(int i)
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
};

const int NULL_NODE = INT_MIN;

BTreeNode* createMinimalBSTUtil(vector<int>& vec, int start, int end)
{
	if (start <= end)
	{
		int mid = (start + end) / 2;
		BTreeNode *pNode = new BTreeNode(vec[mid]);
		pNode->lc = createMinimalBSTUtil(vec, start, mid - 1);
		pNode->rc = createMinimalBSTUtil(vec, mid + 1, end);
		return pNode;
	}
	return nullptr;
}

BTreeNode* createMinimalBSTUtil(vector<int>& vec, int start, int end, BTreeNode *parent)
{
	if (start <= end)
	{
		int mid = (start + end) / 2;
		BTreeNode *pNode = new BTreeNode(vec[mid], parent);
		pNode->lc = createMinimalBSTUtil(vec, start, mid - 1, pNode);
		pNode->rc = createMinimalBSTUtil(vec, mid + 1, end, pNode);
		return pNode;
	}
	return nullptr;
}

BTreeNode* createBinaryTree(std::vector<int>& vec, std::map<int, BTreeNode*>& mMap)
{
	if (vec.empty())
	{
		return nullptr;
	}

	int i = 0;
	BTreeNode* pRoot = new BTreeNode(vec[i++]);

	mMap[pRoot->val] = pRoot;

	queue<BTreeNode*> que;
	que.push(pRoot);

	while (i < vec.size())
	{
		BTreeNode* pNode = que.front();
		mMap[pNode->val] = pNode;
		que.pop();
		if (vec[i] != NULL_NODE)
		{
			pNode->lc = new BTreeNode(vec[i], pNode);
			que.push(pNode->lc);
			mMap[vec[i]] = pNode->lc;
		}
		i++;

		if (i < vec.size() && vec[i] != NULL_NODE)
		{
			pNode->rc = new BTreeNode(vec[i], pNode);
			que.push(pNode->rc);
			mMap[vec[i]] = pNode->rc;
		}
		i++;
	}
	return pRoot;
}

void inorder(BTreeNode* pRoot)
{
	if (pRoot)
	{
		inorder(pRoot->lc);
		std::cout << pRoot->val << " ";
		inorder(pRoot->rc);
	}
}

void levelOrder(BTreeNode* pRoot)
{
	if (!pRoot)
	{
		return;
	}

	std::queue<BTreeNode*> que;
	que.push(pRoot);

	int parentCount = 1;

	while (!que.empty())
	{
		BTreeNode* pNode = que.front();
		que.pop();

		if (pNode)
		{
			std::cout << pNode->val << " ";
			que.push(pNode->lc);
			que.push(pNode->rc);
		}
		else
		{
			std::cout << "NULL ";
		}

		if (--parentCount == 0)
		{
			std::cout << std::endl;
			parentCount = (int)que.size();
		}
	}
}