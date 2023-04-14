#ifndef __DISJOINT_SET_H__
#define __DISJOINT_SET_H__

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#include "Common/logger.h"
#include "Common/helper.h"

namespace nsCpp_DS {

// struct __SetNode START
struct __SetNode
{
	using VertexType	= int;
	using SizeType		= size_t;

	VertexType		m_vertex;
	VertexType		m_parent;
	SizeType		m_size;				// Number of descendent (including his own size which is 1)

	__SetNode(VertexType inVertex, VertexType inParent, SizeType inSize)
		: m_vertex(inVertex)
		, m_parent(inParent)
		, m_size(inSize)
	{}

	friend std::ostream& operator <<(std::ostream& out, const __SetNode& node);
	friend std::ostream& operator <<(std::ostream& out, const __SetNode* node);
private:
	void print(void* address) const;
};

void __SetNode::print(void* address) const
{
	if (address)
	{
		ns_Util::Logger::LOG_MSG("Node [", address, "] : ");
	}
	else
	{
		ns_Util::Logger::LOG_MSG("Node : ");
	}
	ns_Util::Logger::LOG_MSG("Vertex = ", m_vertex, ", Parent = ", m_parent, ", Size = ", m_size);
}

std::ostream& operator <<(std::ostream& out, const __SetNode& node)
{
	node.print(nullptr);
	return out;
}

std::ostream& operator <<(std::ostream& out, const __SetNode* node)
{
	node->print((void*)node);
	return out;
}
// struct __SetNode END

class DisJointSet
{
public:
	using NodeType		= __SetNode;
	using VertexType	= typename NodeType::VertexType;
	using SizeType		= typename NodeType::SizeType;

public:
	void makeSet(VertexType vertex, SizeType size = 1);

	VertexType find(VertexType vertex) const;

	void makeUnion(VertexType vertex_x, VertexType vertex_y);

	void clear() { m_vNodes.clear(); }

	friend std::ostream& operator <<(std::ostream& out, const DisJointSet& disJointSet);
private:
	NodeType* search(VertexType vertex) const;
	void print() const;

private:
	std::vector<NodeType>	m_vNodes;
};

void DisJointSet::makeSet(VertexType vertex, SizeType size)
{
	if (!search(vertex))
	{
		m_vNodes.push_back(NodeType(vertex, vertex, size));		// Make it point to itself
	}
	else
	{
		ns_Util::Logger::LOG_MSG("Vertex = ", vertex, ", Already present.\n");
	}
}

DisJointSet::VertexType DisJointSet::find(VertexType vertex) const	// return which set it belongs to, and also update intermediates to directly point to parent
{
	NodeType* nodePtr = search(vertex);

	if (!nodePtr)
	{
		ns_Util::Logger::LOG_MSG("Vertex = ", vertex, ", NOT FOUND\n");
		return -1;
	}
	if (nodePtr->m_parent != vertex)			// If it's not root
	{
		nodePtr->m_parent = find(nodePtr->m_parent);
	}
	return nodePtr->m_parent;
}

void DisJointSet::makeUnion(VertexType vertex_x, VertexType vertex_y)
{
	VertexType parent_x = find(vertex_x);
	VertexType parent_y = find(vertex_y);

	if (parent_x == -1 || parent_y == -1)
	{
		ns_Util::Logger::LOG_MSG("makeUnion() : called with non existing vertices [ ", vertex_x, " , ", vertex_y, " ]\n");
		return;
	}

	if (parent_x != parent_y)
	{
		NodeType* xPtr = search(parent_x);
		NodeType* yPtr = search(parent_y);

		if (xPtr && yPtr)
		{
			if (xPtr->m_size < yPtr->m_size)
			{
				std::swap(xPtr, yPtr);
			}
			xPtr->m_parent = xPtr->m_vertex;
			xPtr->m_size += yPtr->m_size;
		}
	}
}

DisJointSet::NodeType* DisJointSet::search(VertexType vertex) const
{
	std::vector<NodeType>::const_iterator it = std::find_if(m_vNodes.cbegin(), m_vNodes.cend(), [&vertex](const NodeType& node)
		{
			return node.m_vertex == vertex;
		});
	return (it == m_vNodes.end()) ? nullptr : const_cast<NodeType *>(&(*it));
}

void DisJointSet::print() const
{
	for (size_t i = 0, size = m_vNodes.size(); i < size; ++i)
	{
		ns_Util::Logger::LOG_MSG(i + 1, " : ", m_vNodes[i], ", Parent = ", find(m_vNodes[i].m_vertex), '\n');
	}
	ns_Util::Logger::LOG_MSG("\n\n");
}

std::ostream& operator <<(std::ostream& out, const DisJointSet& disJointSet)
{
	disJointSet.print();
	return out;
}

void test_DisJointSet_1()
{
	using VertexType	= typename DisJointSet::VertexType;
	using SizeType		= typename DisJointSet::SizeType;

	const char* testName = "Insertion | makeUnion.";
	ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n\n");

	DisJointSet	disjointset;

	std::vector<VertexType> vec{ 1,2,3,4,5,6,7,8 };

	for (auto& x : vec)
	{
		disjointset.makeSet(x);
	}

	disjointset.makeUnion(1, 8);
	disjointset.makeUnion(5, 6);
	disjointset.makeUnion(2, 1);
	disjointset.makeUnion(5, 2);

	disjointset.makeUnion(3, 4);

	ns_Util::Logger::LOG_MSG(disjointset, '\n');
}

void test_DisJointSet()
{
	LOG_ENTRY;
	test_DisJointSet_1();
	LOG_EXIT;
	ns_Util::Logger::LOG_MSG("#####################################\n\n");
}
}
#endif // #define __DISJOINT_SET_H__