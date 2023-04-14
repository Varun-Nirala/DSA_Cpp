#pragma once

#include <iostream>
#include <queue>

#include "Common/helper.h"
#include "Common/logger.h"

template <typename T>
class BinaryTree
{
public:
	using dataType = T;

private:
	struct Node
	{
		Node		*m_pLeft{};
		Node		*m_pRight{};
		dataType	m_key{};

		Node() = default;

		explicit Node(dataType val)
			: m_key(val)
		{}
	};

public:
	BinaryTree() = default;
	~BinaryTree() { clear(); }

	size_t size() const { return m_size; }
	bool empty() const { return m_pRoot == nullptr; }

	void clear()
	{
		if (empty()) return;

		std::queue<Node*> que;
		que.push(m_pRoot);

		while (!que.empty())
		{
			Node* node = que.front();
			que.pop();

			if (node->m_pLeft)
			{
				que.push(node->m_pLeft);
			}

			if (node->m_pRight)
			{
				que.push(node->m_pRight);
			}

			delete node;
		}

		m_pRoot = nullptr;
		m_size = 0;
	}

	void push(dataType key)
	{
		std::queue<Node*> que;
		que.push(m_pRoot);

		while (!que.empty())
		{
			Node* node = que.front();
			que.pop();

			if (node->m_pLeft)
			{
				que.push(node->m_pLeft);
			}
			else
			{
				node->m_pLeft = new Node(key);
				return;
			}

			if (node->m_pRight)
			{
				que.push(node->m_pRight);
			}
			else
			{
				node->m_pRight = new Node(key);
				return;
			}
		}
	}

	void pop()
	{
		ASSERT(!empty());

		std::queue<Node*> que;
		que.push(m_pRoot);
		Node* parentNode{};
		while (!que.empty())
		{
			Node* node = que.front();
			que.pop();
			if (node->m_pLeft)
			{
				que.push(node->m_pLeft);
			}

			if (node->m_pRight)
			{
				que.push(node->m_pRight);
			}

			parentNode = node;
		}

		if (parentNode && parentNode->m_pRight)
		{
			std::swap(m_pRoot->m_key, parentNode->m_pRight->m_key);
			delete parentNode->m_pRight;
			parentNode->m_pRight = nullptr;
		}
		else if (parentNode && parentNode->m_pLeft)
		{
			std::swap(m_pRoot->m_key, parentNode->m_pLeft->m_key);
			delete parentNode->m_pLeft;
			parentNode->m_pLeft = nullptr;
		}
	}

	const dataType& first() const
	{
		ASSERT(!empty());
		return m_pRoot->m_key;
	}

	dataType& first()
	{
		ASSERT(!empty());
		return m_pRoot->m_key;
	}

	void erase(const dataType& key)
	{
		std::queue<Node*> que;
		que.push(m_pRoot);

		while (!que.empty())
		{

		}
	}

	void levelOrder()
	{
		ns_Util::Logger::LOG_MSG("Printing Levelorder traversal\n\n");
		std::queue<Node*> que;
		que.push(m_pRoot);

		while (!que.empty())
		{
			for (size_t i = 0, size = que.size(); i < size; ++i)
			{
				Node* node = que.front();
				que.pop();
				ns_Util::Logger::LOG_MSG(node->m_key, "  ");

				if (node->m_pLeft)
				{
					que.push(node->m_pLeft);
				}

				if (node->m_pRight)
				{
					que.push(node->m_pRight);
				}
			}
			ns_Util::Logger::LOG_MSG('\n');
		}
	}

	void preOrder()
	{
		ns_Util::Logger::LOG_MSG("Printing Preorder traversal\n\n");
		preOrder(m_pRoot);
	}

	void inOrder()
	{
		ns_Util::Logger::LOG_MSG("Printing Inorder traversal\n\n");
		inOrder(m_pRoot);
	}

	void postOrder()
	{
		ns_Util::Logger::LOG_MSG("Printing Postorder traversal\n\n");
		postOrder(m_pRoot);
	}

private:
	void preOrder(Node* node)
	{
		if (node)
		{
			ns_Util::Logger::LOG_MSG(node->m_key, "  ");
			preOrder(node->m_pLeft);
			preOrder(node->m_pRight);
		}
	}

	void inOrder(Node* node)
	{
		if (node)
		{
			preOrder(node->m_pLeft);
			ns_Util::Logger::LOG_MSG(node->m_key, "  ");
			preOrder(node->m_pRight);
		}
	}

	void postOrder(Node* node)
	{
		if (node)
		{
			preOrder(node->m_pLeft);
			preOrder(node->m_pRight);
			ns_Util::Logger::LOG_MSG(node->m_key, "  ");
		}
	}

private:
	Node		*m_pRoot{};
	size_t		m_size{};
};