#pragma once

#include <iostream>
#include <queue>

#include "Common/helper.h"
#include "Common/logger.h"

// No duplicate keys
template <typename T>
class BinarySearchTreeWithParent
{
public:
	using dataType = T;

private:
	struct Node
	{
		Node		*m_pLeft{};
		Node		*m_pRight{};
		Node		*m_pParent{};
		dataType	m_key{};

		Node() = default;

		explicit Node(dataType val, Node *parent = nullptr)
			: m_key(val)
			, m_pParent(parent)
		{}
	};

public:
	BinarySearchTreeWithParent() = default;
	~BinarySearchTreeWithParent() { clear(); }

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
		Node* node = m_pRoot;

		while (node)
		{
			if (key < node->m_key)
			{
				if (node->m_pLeft)
				{
					node = node->m_pLeft;
				}
				else
				{
					node->m_pLeft = new Node(key, node);
					++m_size;
					return;
				}
			}
			else if (key > node->m_key)
			{
				if (node->m_pRight)
				{
					node = node->m_pRight;
				}
				else
				{
					node->m_pRight = new Node(key, node);
					++m_size;
					return;
				}
			}
			else
			{
				ns_Util::Logger::LOG_MSG("Duplicate Key!\n");
				break;
			}
		}
	}

	void erase(const dataType& key)
	{
		m_pRoot = erase(m_pRoot, key);
		//erase2(m_pRoot, key);
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
	Node* erase(Node* root, const dataType& key)
	{
		if (!root)
		{
			return nullptr;
		}

		if (key < root->m_key)
		{
			root->m_pLeft = erase(root->m_pLeft, key);
		}
		else if (key > root->m_key)
		{
			root->m_pRight = erase(root->m_pRight, key);
		}
		else
		{
			if (root->m_pLeft == nullptr && root->m_pRight == nullptr)
			{
				delete root;
				--m_size;
				return nullptr;
			}
			else if (root->m_pLeft == nullptr)
			{
				Node* right = root->m_pRight;
				--m_size;
				delete root;
				return right;
			}
			else if (root->m_pRight == nullptr)
			{
				Node* left = root->m_pLeft;
				--m_size;
				delete root;
				return left;
			}
			else
			{
				Node* minValNode = root->m_pRight;
				while (minValNode && minValNode->m_pLeft)
				{
					minValNode = minValNode->m_pLeft;
				}

				root->m_key = minValNode->m_key;

				root->m_pRight = erase(root->m_pRight, minValNode->m_key);
			}
		}
		return root;
	}

	Node* erase2(Node* root, const dataType& key)
	{
		if (!root)
		{
			ns_Util::Logger::LOG_MSG("Tree is empty!\n");
			return;
		}

		Node* parent = nullptr;
		while (root)
		{
			if (key < root->m_key)
			{
				parent = root;
				root = (root->m_pLeft) ? root->m_pLeft : nullptr;
			}
			else if (key > root->m_key)
			{
				parent = root;
				root = (root->m_pRight) ? root->m_pRight : nullptr;
			}
			else
			{
				break;
			}
		}

		if (!root)
		{
			ns_Util::Logger::LOG_MSG("Key : [ ", key, " ] not found!\n");
			return;
		}

		if (root->m_pLeft == nullptr && root->m_pRight == nullptr)
		{
			if (!parent)
			{
				m_pRoot = nullptr;
			}
			else
			{
				if (parent->m_pLeft == root)
				{
					parent->m_pLeft = nullptr;
				}
				else
				{
					parent->m_pRight = nullptr;
				}
			}
			delete root;
			--m_size;
		}
		else if (root->m_pLeft == nullptr)
		{
			if (!parent)
			{
				m_pRoot = root->m_pRight;
			}
			else
			{
				if (parent->m_pLeft == root)
				{
					parent->m_pLeft = root->m_pRight;
				}
				else
				{
					parent->m_pRight = root->m_pRight;
				}
			}
			delete root;
			--m_size;
		}
		else if (root->m_pRight == nullptr)
		{
			if (!parent)
			{
				m_pRoot = root->m_pLeft;
			}
			else
			{
				if (parent->m_pLeft == root)
				{
					parent->m_pLeft = root->m_pLeft;
				}
				else
				{
					parent->m_pRight = root->m_pLeft;
				}
			}
			delete root;
			--m_size;
		}
		else
		{
			Node* minValNode = root->m_pRight;
			while (minValNode && minValNode->m_pLeft)
			{
				minValNode = minValNode->m_pLeft;
			}

			root->m_key = minValNode->m_key;

			erase2(root->m_pRight, minValNode->m_key);
		}
	}

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