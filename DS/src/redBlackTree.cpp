#include "redBlackTree.h"
#include <assert.h>

const char COLOR_BLACK = 'B';
const char COLOR_RED = 'R';

RedBlacktree::RedBlacktree()
	: m_pRoot(NULL)
{}

bool RedBlacktree::add(dataType &data)
{
	Node *newNode = createNewNode(data);
	addLikeBinary(newNode);

	rebalanceAfterAdd(newNode);
	return true;
}

bool RedBlacktree::remove(dataType &data)
{
	return true;
}

//Private Members
bool RedBlacktree::rebalanceAfterAdd(Node *node)
{
	//Different cases of in balance in RedBlack After the insertion

	// PROPERTIES NEEDED TO BE SATISFIED ALL THE TIME
	//	Property 1 (every node is either red or black) and Property 3 (all leaves are black) always holds.
	//	Property 2 (the root is black) is checked and corrected with CASE 1.
	//	Property 4 (red nodes have only black children) is threatened only by adding a red node, repainting a node from black to red, or a rotation.
	//	Property 5 (all paths from any given node to its leaves have the same number of black nodes) is threatened only by adding a black node, repainting a node, or a rotation.

	// Node is N, Parent is P, Uncle is U
	// CASE 1 :: N is the root.

	// CASE 2 :: P is of BLACK color.	(NO CHANGES REQURIED)

	// CASE 3 :: P is RED(so it is not root) and U is also RED. 

	// CASE 4 :: P is RED and U is Black.
	return true;
}

bool RedBlacktree::addLikeBinary(Node *node)
{
	if (!m_pRoot)
		return false;

	Node *p = NULL, *n = m_pRoot;

	while (!isLeaf(n))
	{
		if (n->m_iData <= node->m_iData)
		{
			p = n;
			n = n->m_pLeft;
		}
		else
		{
			p = n;
			n = n->m_pRight;
		}
	}

	n = node;
	n->m_pParent = p;
	return true;
}

void RedBlacktree::rotateRight(Node *node)
{
	Node *newRoot = node->m_pLeft;

	if (isLeaf(newRoot))
	{
		assert(!"Can't Rotate right, something wrong with tree");
		return;
	}

	node->m_pLeft = newRoot->m_pRight;
	newRoot->m_pRight = node;

	newRoot->m_pParent = node->m_pParent;
	node->m_pParent = newRoot;

	node->m_pLeft->m_pParent = node;
}

void RedBlacktree::rotateLeft(Node *node)
{
	Node *newRoot = node->m_pRight;
	if (isLeaf(newRoot))
	{
		assert(!"Can't Rotate left, something wrong with tree");
		return;
	}

	node->m_pRight = newRoot->m_pLeft;
	newRoot->m_pLeft = node;

	newRoot->m_pParent = node->m_pParent;
	node->m_pParent = newRoot;

	node->m_pRight->m_pParent = node;
}

Node* RedBlacktree::getParent(const Node *node)
{
	if (!node)
		return NULL;

	Node *n = node->m_pParent;
	return n;
}

Node* RedBlacktree::getGrandParent(const Node *node)
{
	if (!node)
		return NULL;

	Node *p = getParent(node);
	if (!p)
	{
		// LOG
		return NULL;
	}
	return getParent(p);
}

Node* RedBlacktree::getSibling(const Node *node)
{
	Node *p = getParent(node);
	if (!p)
	{
		//LOG
		return NULL;
	}

	if (p->m_pLeft == node)
	{
		return p->m_pRight;
	}
	else
	{
		return p->m_pLeft;
	}
}

Node* RedBlacktree::getUncle(const Node *node)
{
	if (!getGrandParent(node))
	{
		//LOG
		return NULL;
	}
	else
	{
		return getSibling(getParent(node));
	}
}

bool RedBlacktree::isBlack(const Node *node)
{
	return node->m_cColor == COLOR_BLACK;
}

bool RedBlacktree::isRed(const Node *node)
{
	return !(isBlack(node));
}

bool RedBlacktree::isLeaf(const Node *node) const
{
	return node == m_pcLEAF;
}

Node* RedBlacktree::createNewNode(const dataType &data, const char &color)
{
	Node *newNode = new Node(data, color);
	if (!newNode)
	{
		assert(!"Node Creation error");
		//LOG_ERROR
	}

	newNode->m_pLeft = newNode->m_pRight = m_pcLEAF;
	return newNode;
}