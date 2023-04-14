#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TRE__H__

/*
* Abbreviations :
*				N = current Node in question
*				P = N's Parent
*				G = N's Grand Parent
*				S = N's sibling
*/

#include <iostream>
#include <cassert>
#include <queue>

namespace ns_RBT
{

static const bool RED = true;
static const bool BLACK = !RED;
using COLOR = bool;

#define LEAF nullptr

template<typename T>
struct Node
{
	T		m_key{};
	COLOR	m_color{RED};
	Node	*m_pLeft{};
	Node	*m_pRight{};
	Node	*m_pParent{};

	Node(T key, COLOR color = RED)
		: m_key(key)
		, m_color(color)
	{}

	inline bool isRed() const { return m_color == RED; }
	inline bool isBlack() const { return m_color == BLACK; }

	inline void Print()
	{
		char color = isBlack() ? 'B' : 'R';
		if (m_pParent && m_pParent != LEAF)
		{
			std::cout << m_key << "[" << color << ", " << m_pParent->m_key << "]";
		}
		else
		{
			std::cout << m_key << "[" << color << ", ROOT]";
		}
	}
};

template<typename T>
class RBTree
{
public:
	RBTree() = default;
	~RBTree() { cleanUp(); };

	inline size_t size() const { return m_size; };

	void insert(T value);
	void remove(T value);

	bool search(T value) const;

	void inorder() const;
	void preorder() const;
	void postorder() const;
	void levelorder() const;

protected:
	void rotateLeft(Node<T> *n);
	void rotateRight(Node<T> *n);

	// helper APIs
	// 1. insert
	Node<T>* insertRecusrive(Node<T> *root, Node<T> *n);
	void insertRepair(Node<T> *n);

	// 2. search
	bool searchHelper(Node<T> *n, T value) const;

	// 3. deletion
	Node<T>* findNodeToRemove(Node<T> *n, T value) const;
	Node<T>* finMinInRight(Node<T> *n) const;
	Node<T>* finMaxInLeft(Node<T> *n) const;
	void removeOneChild(Node<T> *n);
	void replaceNode(Node<T> *n, Node<T> *c);

	void removeCase1(Node<T> *n);
	void removeCase2(Node<T> *n);
	void removeCase3(Node<T> *n);
	void removeCase4(Node<T> *n);
	void removeCase5(Node<T> *n);
	void removeCase6(Node<T> *n);

	// 3. traversal
	void inorderHelper(Node<T> *n) const;
	void preorderHelper(Node<T> *n) const;
	void postorderHelper(Node<T> *n) const;
	void levelorderHelper(Node<T> *n) const;

	// General helper API
	inline bool isLeftChild(Node<T> *n) const;
	inline bool isRightChild(Node<T> *n) const;

	inline Node<T>* parent(Node<T> *n) const;
	inline Node<T>* grandParent(Node<T> *n) const;
	inline Node<T>* sibling(Node<T> *n) const;
	inline Node<T>* uncle(Node<T> *n) const;

	inline bool isRed(Node<T> *n) const;
	inline bool isBlack(Node<T> *n) const;

	inline Node<T>* createNode(T value, COLOR color = RED);

	void cleanUp();

	private:
	Node<T>				*m_pRoot{};
	size_t				m_size{};
};

// Public API START
template<typename T>
void RBTree<T>::insert(T value)
{
	Node<T> *n = createNode(value);
	// 1. Insert it like normal BST
	m_pRoot = insertRecusrive(m_pRoot, n);

	// 2. Repair the tree
	insertRepair(n);

	m_size++;
}

template<typename T>
bool RBTree<T>::search(T value) const
{
	if (searchHelper(m_pRoot, value))
	{
		std::cout << "Key Found." << std::endl;
		return true;
	}
	std::cout << "Key Not Found." << std::endl;
	return false;
}

template<typename T>
void RBTree<T>::remove(T value)
{
	// n is the node to be deleted
	Node<T> *n = findNodeToRemove(m_pRoot, value);

	if (!n && n == LEAF)
	{
		std::cout << "Key Not Found" << std::endl;
		return;
	}

	if (n->m_pRight != LEAF && n->m_pLeft != LEAF)
	{
		//Node<T> *u = finMinInRight(n->m_pRight);
		Node<T> *u = finMaxInLeft(n->m_pLeft);
		n->m_key = u->m_key;
		n = u;
	}

	// now we are sure that n has at most one non-leaf child
	removeOneChild(n);
}

template<typename T>
void RBTree<T>::inorder() const
{
	std::cout << "Inorder Traversal :\n";
	inorderHelper(m_pRoot);
	std::cout << "\n";
}

template<typename T>
void RBTree<T>::preorder() const
{
	std::cout << "Preorder Traversal :\n";
	preorderHelper(m_pRoot);
	std::cout << "\n";
}

template<typename T>
void RBTree<T>::postorder() const
{
	std::cout << "Postorder Traversal :\n";
	postorderHelper(m_pRoot);
	std::cout << "\n";
}

template<typename T>
void RBTree<T>::levelorder() const
{
	std::cout << "Levelorder Traversal :\n";
	levelorderHelper(m_pRoot);
	std::cout << "\n";
}
// Public API END

// Protected API START
template<typename T>
void RBTree<T>::rotateLeft(Node<T> *n)
{
	Node<T>	*p = parent(n);
	Node<T> *nnew = n->m_pRight;

	assert(nnew != LEAF);	// this should not be leaf(NIL) as it cannot become internal node

	n->m_pRight = nnew->m_pLeft;
	nnew->m_pLeft = n;
	n->m_pParent = nnew;

	if (n->m_pRight != LEAF)
	{
		n->m_pRight->m_pParent = n;
	}

	if (p)
	{
		if (n == p->m_pLeft)
		{
			p->m_pLeft = nnew;
		}
		else if (n == p->m_pRight)
		{
			p->m_pRight = nnew;
		}
	}
	else
	{
		m_pRoot = nnew;
	}
	nnew->m_pParent = p;
}

template<typename T>
void RBTree<T>::rotateRight(Node<T> *n)
{
	Node<T> *p = parent(n);
	Node<T> *nnew = n->m_pLeft;

	assert(nnew != LEAF);	// this should not be leaf(NIL) as it cannot become internal node

	n->m_pLeft = nnew->m_pRight;
	nnew->m_pRight = n;
	n->m_pParent = nnew;

	if (n->m_pLeft != LEAF)
	{
		n->m_pLeft->m_pParent = n;
	}

	if (p)
	{
		if (n == p->m_pLeft)
		{
			p->m_pLeft = nnew;
		}
		else if (n == p->m_pRight)
		{
			p->m_pRight = nnew;
		}
	}
	else
	{
		m_pRoot = nnew;
	}
	nnew->m_pParent = p;
}

template<typename T>
Node<T>* RBTree<T>::insertRecusrive(Node<T> *root, Node<T> *n)
{
	if (root == nullptr || root == LEAF)
	{
		return n;	// return it as ROOT
	}

	if (root && (n->m_key < root->m_key))
	{
		root->m_pLeft = insertRecusrive(root->m_pLeft, n);
		root->m_pLeft->m_pParent = root;
	}
	else if (root && (n->m_key > root->m_key))
	{
		root->m_pRight = insertRecusrive(root->m_pRight, n);
		root->m_pRight->m_pParent = root;
	}

	return root;
}

template<typename T>
void RBTree<T>::insertRepair(Node<T> *n)
{
	// Properties to check
	// Property 1 [Every node is erither RED or BLACK] and Property 3 [All leaves are BLACK] always hold
	
	// Property 2 [The root is BLACK], just change its color.
	// Property 4 [RED node only have BLACK Child] is threatened only by adding a red node, repainting
	//				a node BLACK to RED or a rotation
	// Property 5 [All paths from any given node to its leaves have the same number of BLACK nodes]
	//				is threatened only  by adding a BLACK NODE, repainting a node or a rotation

	if (parent(n) == nullptr)
	{
		// N is root, just repaint it to BLACK to satisfy Property 2.
		// Since this adds one BLACK node to every path at once, Property 5 s not violated
		n->m_color = BLACK;
	}
	else if (isBlack(parent(n)))
	{
		// P is BLACK , so Property 4 is not invalidated
		// Property 5 is not threatened. because N has 2 BLACK leaf.
		// And because N is RED, the paths through each of its children have the same number of 
		// BLACK nodes as N just replaced a leaf and has its 2 NIL BLACK nodes.

		;	// so nothing to do.
	}
	else if (uncle(n) && isRed(uncle(n)))	// it mean P is RED too
	{
		// If both P and U are RED, then repaint both as BLACK and repaint G as RED to maintain
		// Property 5.
		// Since any path through the P or U must pass through the G, the number of BLACK nodes
		// on these paths has not changed. However, the G may now violate Property 2 if it is root
		// or Property 4 if it's P is RED.
		// To fix above violation call insertRepair on G.

		parent(n)->m_color = BLACK;
		uncle(n)->m_color = BLACK;
		grandParent(n)->m_color = RED;
		insertRepair(grandParent(n));
	}
	else    // it mean P is RED and U is BLACK, now we need Rotation and Recoloring
	{
		// In this case our Ultimate goal is to make N as G

		// In this case there are 2 possible arrangements
		// 1. N is on "inside" of the subtree under G.
		//			-> Which mean, N is right child of left child of G OR left child of right child of G.
		
		// 2. N is on "outside" of the subtree under G.
		//			-> Which mean, N is left of left child of G OR right of right child of G.
		
		// If it is in arrangement 1, make it in arrangement 2 by rotation
		// The rotation on P will now switch the role of N and P
		Node<T> *p = parent(n);
		Node<T> *g = grandParent(n);

		if ((g->m_pLeft && g->m_pLeft != LEAF) && (n == g->m_pLeft->m_pRight))
		{
			rotateLeft(p);
			// After rotation, role is switched. So past P is at bottom now, and it is out N now
			n = n->m_pLeft;
		}
		else if ((g->m_pRight && g->m_pRight != LEAF) && (n == g->m_pRight->m_pLeft))
		{
			rotateRight(p);
			// After rotation, role is switched. So past P is at bottom now, and it is out N now
			n = n->m_pRight;
		}

		// Now our subtree is in 2nd arrangement
		// As both P and N were RED, the rotation done above would not affect Property 5.
		// But Property 4 is still violated, so we have to resolve it now
		p = parent(n);
		g = grandParent(n);

		// Now we need to do rotation on G, this will make the P(old N)
		// as parent of both N(old P) and G
		// After that we jus have to repaint N(old P) and G as RED and P(old N) as BLACK
		if (isLeftChild(n))
		{
			rotateRight(g);
		}
		else
		{
			rotateLeft(g);
		}

		p->m_color = BLACK;
		g->m_color = RED;
	}
}

template<typename T>
bool RBTree<T>::searchHelper(Node<T> *n, T value) const
{
	if (n && n != LEAF)
	{
		if (value < n->m_key)
		{
			search(n->m_pLeft, value);
		}
		else if (value > n->m_key)
		{
			search(n->m_pRight, value);
		}
		else
		{
			return true;
		}
	}
	return false;
}

template<typename T>
Node<T>* RBTree<T>::findNodeToRemove(Node<T> *n, T value)  const
{
	if (!n || n == LEAF)
	{
		return nullptr;
	}
	else if (value < n->m_key)
	{
		return findNodeToRemove(n->m_pLeft, value);
	}
	else if (value > n->m_key)
	{
		return findNodeToRemove(n->m_pRight, value);
	}
	// Match found
	return n;
}

template<typename T>
Node<T>* RBTree<T>::finMinInRight(Node<T> *n) const
{
	assert(n != nullptr);
	while (n->m_pLeft != LEAF)
	{
		n = n->m_pLeft;
	}
	return n;
}

template<typename T>
Node<T>* RBTree<T>::finMaxInLeft(Node<T> *n) const
{
	assert(n != nullptr);
	while (n->m_pRight != LEAF)
	{
		n = n->m_pRight;
	}
	return n;
}

template<typename T>
void RBTree<T>::removeOneChild(Node<T> *n)
{
	assert(n != nullptr);

	Node<T> *c = (n->m_pRight == LEAF) ? n->m_pLeft : n->m_pRight;
	if (isBlack(n))
	{
		if (isRed(c))	// SINGLE BLACK case
		{
			c->m_color = BLACK;
		}
		else   // DOUBLE BLACK case
		{
			removeCase1(n);
		}
	}
	// Replace node n with its only non-leaf child
	replaceNode(n, c);

	delete n;
	m_size--;
}

template<typename T>
void RBTree<T>::replaceNode(Node<T> *n, Node<T> *c)
{
	if (c && c != LEAF)
	{
		c->m_pParent = n->m_pParent;
	}
	else
	{
		if (isLeftChild(n))
		{
			n->m_pParent->m_pLeft = c;
		}
		else if (isRightChild(n))
		{
			n->m_pParent->m_pRight = c;
		}
		else
		{
			// This is root
			m_pRoot = c;
		}
	}
}

template<typename T>
void RBTree<T>::removeCase1(Node<T> *n)
{
	// if N is new root, we are done, else call case2
	if (parent(n))
	{
		removeCase2(n);
	}
}

template<typename T>
void RBTree<T>::removeCase2(Node<T> *n)
{
	// Handle's case in which S is RED
	Node<T> *s = sibling(n);

	if (isRed(s))
	{
		Node<T> *p = parent(n);
		// Make P RED ans S BLACK and do rotation
		p->m_color = RED;
		s->m_color = BLACK;
			
		if (isLeftChild(n))
		{
			rotateLeft(p);
		}
		else
		{
			rotateRight(p);
		}
	}
	removeCase3(n);
}

template<typename T>
void RBTree<T>::removeCase3(Node<T> *n)
{
	// S and S's childrens are BLACK
	Node<T> *s = sibling(n);

	if (s && s != LEAF)
	{
		Node<T> *p = parent(n);

		if (isBlack(p) && isBlack(s) && isBlack(s->m_pLeft) && isBlack(s->m_pRight))
		{
			s->m_color = RED;	// now path going through S will have one less BLACK node(same as for paths going through N)
			// Now Path below P have same number of BLACK nodes
			// But all path through P now have one fewer BLACK node than those Paths that do not pass through P
			// Call rebalancing procedure on P
			removeCase1(p);
		}
		else
		{
			removeCase4(n);
		}
	}
}

template<typename T>
void RBTree<T>::removeCase4(Node<T> *n)
{
	// S and S's children are BLACK, but P is RED
	// Simply change the color of S and P
	Node<T> *s = sibling(n);

	if (s && s != LEAF)
	{
		Node<T> *p = parent(n);
		if (isRed(p) && isBlack(s) && isBlack(s->m_pLeft) && isBlack(s->m_pRight))
		{
			s->m_color = RED;
			p->m_color = BLACK;
		}
		else
		{
			removeCase5(n);
		}
	}
}

template<typename T>
void RBTree<T>::removeCase5(Node<T> *n)
{
	// S is BLACK and its child on the side of N is RED and other is BLACK
	Node<T> *s = sibling(n);

	if (s && s != LEAF)
	{
		if (isBlack(s))
		{
			Node<T> *p = parent(n);
			if (isLeftChild(n) && isRed(s->m_pLeft) && isBlack(s->m_pRight))
			{
				// Rotate Right at S and exchange the color of S and S's Left child
				s->m_color = RED;
				s->m_pLeft->m_color = BLACK;
				rotateRight(s);
			}
			else if (isRightChild(n) && isBlack(s->m_pLeft) && isRed(s->m_pRight))
			{
				// Rotate Left at S and exchange the color of S and S's Right child
				s->m_color = RED;
				s->m_pRight->m_color = BLACK;
				rotateLeft(s);
			}
		}
		removeCase6(n);
	}
}

template<typename T>
void RBTree<T>::removeCase6(Node<T> *n)
{
	// S is BLACK and its child on the opposite side of N is RED and other is BLACK
	Node<T> *s = sibling(n);
	if (s && s != LEAF)
	{
		if (isBlack(s))
		{
			Node<T> *p = parent(n);
			// Exchange color of P and S
			// then rotate left or right on P
			s->m_color = p->m_color;
			p->m_color = BLACK;

			if (isLeftChild(n))
			{
				s->m_pRight->m_color = BLACK;
				rotateLeft(p);
			}
			else if (isRightChild(n))
			{
				s->m_pLeft->m_color = BLACK;
				rotateRight(p);
			}
		}
	}
}

template<typename T>
void RBTree<T>::inorderHelper(Node<T> *n) const
{
	if (n && n != LEAF)
	{
		inorderHelper(n->m_pLeft);
		n->Print();
		std::cout << "\n";
		inorderHelper(n->m_pRight);
	}
}

template<typename T>
void RBTree<T>::preorderHelper(Node<T> *n) const
{
	if (n && n != LEAF)
	{
		preorderHelper(n->m_pLeft);
		preorderHelper(n->m_pRight);
		n->Print();
		std::cout << "\n";
	}
}

template<typename T>
void RBTree<T>::postorderHelper(Node<T> *n) const
{
	if (n && n != LEAF)
	{
		n->Print();
		std::cout << "\n";
		postorderHelper(n->m_pLeft);
		postorderHelper(n->m_pRight);
	}
}

template<typename T>
void RBTree<T>::levelorderHelper(Node<T> *n) const
{
	if (n && n != LEAF)
	{
		using std::queue;
		queue<Node<T> *> q1, q2;
		bool bUse_q1 = true;

		q1.push(n);
		while (!q1.empty() || !q2.empty())
		{
			if (bUse_q1)
			{
				while (!q1.empty())
				{
					Node<T> *n = q1.front();
					q1.pop();
					n->Print();
					std::cout << "  ";
					if (n->m_pLeft && n->m_pLeft != LEAF)
					{
						q2.push(n->m_pLeft);
					}
					if (n->m_pRight && n->m_pRight != LEAF)
					{
						q2.push(n->m_pRight);
					}
				}
				bUse_q1 = false;
				std::cout << "\n";
			}
			else
			{
				while (!q2.empty())
				{
					Node<T> *n = q2.front();
					q2.pop();
					n->Print();
					std::cout << "  ";
					if (n->m_pLeft && n->m_pLeft != LEAF)
					{
						q1.push(n->m_pLeft);
					}
					if (n->m_pRight && n->m_pRight != LEAF)
					{
						q1.push(n->m_pRight);
					}
				}
				bUse_q1 = true;
				std::cout << "\n";
			}
		}
	}
	return;
}

template<typename T>
bool RBTree<T>::isLeftChild(Node<T> *n) const
{
	Node<T> *p = parent(n);
	return (p && p->m_pLeft == n);
}

template<typename T>
bool RBTree<T>::isRightChild(Node<T> *n) const
{
	Node<T> *p = parent(n);
	return (p && p->m_pRight == n);
}

template<typename T>
Node<T>* RBTree<T>::parent(Node<T> *n) const
{
	return n ? n->m_pParent : nullptr;
}

template<typename T>
Node<T>* RBTree<T>::grandParent(Node<T> *n) const
{
	return parent(parent(n));
}

template<typename T>
Node<T>* RBTree<T>::sibling(Node<T> *n) const
{
	if (isLeftChild(n))
	{
		return parent(n)->m_pRight;
	}
	else if (isRightChild(n))
	{
		return parent(n)->m_pLeft;
	}
	return nullptr;
}

template<typename T>
Node<T>* RBTree<T>::uncle(Node<T> *n) const
{
	Node<T> *g = grandParent(n);
	return g ? sibling(parent(n)) : nullptr;
}

template<typename T>
bool RBTree<T>::isRed(Node<T> *n) const
{
	if (n && n != LEAF)
	{
		return n->isRed();
	}
	return false;
}

template<typename T>
bool RBTree<T>::isBlack(Node<T> *n) const
{
	if (n && n != LEAF)
	{
		return n->isBlack();
	}
	else if (n == LEAF)
	{
		return true;
	}
	return false;
}

template<typename T>
Node<T>* RBTree<T>::createNode(T value, COLOR color)
{
	return new Node<T>(value, color);
}

template<typename T>
void RBTree<T>::cleanUp()
{
	return;
}
// Protected API END

void testRB_Tree()
{
	ns_RBT::RBTree<int> rbTree;
	std::vector<int> vec{7, 6, 5, 4, 3, 2, 1};
	
	for (auto val : vec)
	{
		rbTree.insert(val);
	}
	rbTree.inorder();
	
	rbTree.levelorder();

	rbTree.remove(6);

	rbTree.inorder();
	rbTree.levelorder();

	rbTree.remove(2);

	rbTree.inorder();
	rbTree.levelorder();
}

}
#endif // #ifndef __RED_BLACK_TREE_H__
