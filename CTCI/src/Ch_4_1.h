#pragma once

/*
	Route between nodes : Given graph and two nodes, find if there is a route between them or not
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "ds_graph.h"

using namespace std;

class Solution_4_1
{
public:
	bool hasRoute(nsGraph::Graph &g, char nodeA, char nodeB)
	{
		if (nodeA == nodeB)
			return true;

		nsGraph::Node *startNode = g.getNode(nodeA);
		nsGraph::Node *endNode = g.getNode(nodeB);

		if (!startNode || !endNode)
			return false;

		g.resetState();

		queue<nsGraph::Node *> que;
		que.push(startNode);

		startNode->state = nsGraph::VISITING;

		while (!que.empty())
		{
			nsGraph::Node *node = que.front();
			que.pop();

			vector<nsGraph::WeightedNode> vec = node->getAdjacent();
			for (int i = 0; i < vec.size(); ++i)
			{
				if (!vec[i].isVisited())
				{
					if (vec[i].getName() == nodeB)
					{
						return true;
					}
					else
					{
						que.push(vec[i].pNode);
						vec[i].pNode->state = nsGraph::VISITING;
					}
				}
			}
			node->state = nsGraph::VISITED;
		}
		return false;
	}
};

void test_Ch_4_1()
{
	nsGraph::Graph graph({
		{'a', 'b', 0 },
		{'a', 'd', 0 },
		{'b', 'c', 0 },
		{'b', 'e', 0 },
		{'d', 'e', 0 },
		{'e', 'c', 0 }
		});

	graph.print();

	Solution_4_1 sol;
	char first = 'b', last = 'd';
	std::cout << "Can we reach from " << first << " to " << last << " : " << boolalpha << sol.hasRoute(graph, first, last) << endl;
}
