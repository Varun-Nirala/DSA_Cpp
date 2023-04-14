#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

namespace nsGraph
{
	enum State
	{
		UNVISITED,
		VISITING,
		VISITED
	};

	struct Node;
	typedef struct WeightedNode
	{
		Node		*node = nullptr;
		int		weight = 0;

		~WeightedNode();

		WeightedNode(Node *n, int w);

		char getName();
		bool isVisited();
	}WeightedNode;

	typedef struct Node {
		char								name;
		std::vector<WeightedNode>		edges;
		std::vector<WeightedNode>		inEdges;
		State							state;

		Node(char ch)
			: name(ch)
			, state(UNVISITED)
		{}

		void addEdge(Node *n, int weight)
		{
			edges.emplace_back(WeightedNode(n, weight));
		}

		void addInEdge(Node *n, int weight)
		{
			inEdges.emplace_back(WeightedNode(n, weight));
		}

		std::vector<WeightedNode> &getAdjacent() { return edges; }

		std::vector<WeightedNode> &getInEdges() { return inEdges; }

		WeightedNode* getNode(char ch)
		{
			std::vector<WeightedNode>::iterator it = find_if(edges.begin(), edges.end(),
				[ch](WeightedNode &w) { return w.node->name = ch; });

			return it == edges.end() ? nullptr : &(*it);
		}

		void resetState() { state = UNVISITED; }

		bool isVisited() { return state == VISITED; }
	}Node;

	WeightedNode::~WeightedNode()
	{
		node = nullptr;
	}
	WeightedNode::WeightedNode(Node *n, int w)
		: node(n)
		, weight(w)
	{}
	char WeightedNode::getName() { return node->name; }
	bool WeightedNode::isVisited() { return node->isVisited(); }

	class Graph
	{
	public:
		~Graph()
		{
			for (int i = 0; i < nodes.size(); ++i)
			{
				delete nodes[i];
			}
			nodes.clear();
		}

		Graph(std::vector<std::tuple<char, char, int>> vec = {})
		{
			if (!vec.empty())
			{
				for (int i = 0; i < vec.size(); ++i)
				{
					char a = std::get<0>(vec[i]);
					char b = std::get<1>(vec[i]);
					int w = std::get<2>(vec[i]);

					addEdge(a, b, w);
				}
			}
		}

		void addNode(char val, int weight = 0)
		{
			nodes.emplace_back(new Node(val));
		}

		Node* getNode(char val)
		{
			std::vector<Node *>::iterator	 it = find_if(nodes.begin(), nodes.end(), [val](Node *n) {
				return n->name == val;
			});

			return it == nodes.end() ? nullptr : *it;
		}

		void addEdge(char a, char b, int weight = 0)		// This means a->b , that is only directed edge for b->a call again
		{
			Node *na = getNode(a);
			Node *nb = getNode(b);

			if (!na)
			{
				na = new Node(a);
				nodes.push_back(na);
			}
			if (!nb)
			{
				nb = new Node(b);
				nodes.push_back(nb);
			}

			nb->addInEdge(na, weight);
			na->addEdge(nb, weight);
		}

		std::vector<Node *>& getAllNodes()
		{
			return nodes;
		}

		std::vector<WeightedNode> getAdjacent(char ch)
		{
			Node *node = getNode(ch);
			return node ? node->getAdjacent() : std::vector<WeightedNode>();
		}

		size_t size() { return nodes.size(); }

		void resetState()
		{
			for (int i = 0; i < nodes.size(); ++i)
			{
				nodes[i]->resetState();
			}
		}

		void print()
		{
			for (int i = 0; i < nodes.size(); ++i)
			{
				Node *node = nodes[i];
				std::cout << node->name << "    ";
				for (int j = 0; j < node->edges.size(); ++j)
				{
					std::cout << "->{" << node->edges[j].node->name << "," << node->edges[j].weight << "}";
				}

				if (node->edges.empty())
				{
					std::cout << "->{NULL}";
				}

				std::cout << std::endl;
			}
		}

	private:
		std::vector<Node *>	nodes;
	};
}