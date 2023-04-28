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

#include "ds_binaryTree.h"

using namespace std;

class Solution_4_11
{
	BTreeNode *m_pRoot = nullptr;
public:
	int size()
	{
		return m_pRoot->size;
	}

	void insertInOrder(int data)
	{
		if (!m_pRoot)
		{
			m_pRoot = new BTreeNode(data);
			m_pRoot->size = 0;
		}
		m_pRoot->insertInOrder(data);
	}

	BTreeNode* getRandom()
	{
		if (!m_pRoot)
		{
			return nullptr;
		}

		int index = rand();
		cout << "Random no = " << index;
		index = index % size();
		cout << ", Norm no = " << index << " ";
		return m_pRoot->getIthNode(index);
	}

	void printInOrder()
	{
		inorder(m_pRoot);
	}

	void printLevelOrder()
	{
		levelOrder(m_pRoot);
	}
};

void test_Ch_4_11()
{
	Solution_4_11 sol;
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
}