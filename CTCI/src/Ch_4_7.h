#pragma once

/*
	Build Order :	You are given a list of projects and a list of dependencies (which is a list of pairs of projects, where the second
					project is dependent on the first project). All of project's dependencies must be built before the project is. Find
					a build order that will allow the projects to be built. If there is no valid build order, return an error.

					Example :
						Input : 
							Projects			: a, b, c, d, e, f
							Dependencies		: (a, d), (f, b), (b, d), (f, a), (d, c)
						Ouput : f, e, a, b, d, c
*/

#include <iostream>
#include <vector>
#include <stack>

#include "ds_graph.h"

using namespace std;

class Solution_4_7
{
	bool doDFS(nsGraph::Node *node, stack<nsGraph::Node *> &order)
	{
		if (node->state == nsGraph::VISITING)
		{
			return false;	//Cycle detected
		}

		if (node->state == nsGraph::UNVISITED)
		{
			node->state = nsGraph::VISITING;
			vector<nsGraph::WeightedNode> adjacent = node->getAdjacent();
			for (nsGraph::WeightedNode &w : adjacent)
			{
				if (!doDFS(w.pNode, order))
				{
					return false;
				}
			}
			node->state = nsGraph::VISITED;
			order.push(node);
		}

		return true;
	}

public:
	vector<nsGraph::Node *> buildOrder(nsGraph::Graph &g)
	{
		vector<nsGraph::Node *> ans;
		stack<nsGraph::Node *> order;
		bool hasOrder = true;

		g.resetState();

		vector<nsGraph::Node *> &nodes = g.getAllNodes();

		for (nsGraph::Node *node : nodes)
		{
			if (node->state == nsGraph::UNVISITED)
			{
				if (!doDFS(node, order))
				{
					hasOrder = false;
				}
			}
		}

		if (!hasOrder)
		{
			return ans;
		}

		ans.resize(order.size());
		int i = 0;
		while (!order.empty())
		{
			ans[i++] = order.top();
			order.pop();
		}
		return ans;
	}
};

void test_Ch_4_7()
{
	vector<char> projects = { 'a' , 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	vector<pair<char, char>> dependencies = {
		{'d', 'g'},

		{'f', 'c'},
		{'f', 'b'},
		{'f', 'a'},
		{'c', 'a'},
		{'b', 'a'},

		{'a', 'e'},
		{'b', 'h'},
	};

	nsGraph::Graph graph;

	for (auto &x : projects)
	{
		graph.addNode(x);
	}

	for (auto &x : dependencies)
	{
		graph.addEdge(x.first, x.second);
	}

	/*nsGraph::Graph graph({
		{'f', 'c', 0 },
		{'f', 'b', 0 },
		{'f', 'a', 0 },

		{'c', 'a', 0 },

		{'b', 'a', 0 },

		{'b', 'e', 0 },

		{'a', 'e', 0 },

		{'d', 'g', 0 },
		});*/

	graph.print();

	Solution_4_7 sol;

	vector<nsGraph::Node*> order = sol.buildOrder(graph);

	if (order.empty())
	{
		cout << "Can't build\n";
	}
	else
	{
		cout << "Build Oder : ";
		for (int i = 0; i < order.size(); ++i)
		{
			cout << order[i]->name << "->";
		}
		cout << endl;
	}
}