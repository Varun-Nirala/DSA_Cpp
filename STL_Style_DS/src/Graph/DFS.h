#pragma once

#include "Graph.h"
#include <stack>

void DFS(const Graph &graph, int startNode)
{
	std::vector<int> vParent(graph.getNumberOfVertices());
	fill(vParent.begin(), vParent.end(), INT_MAX);

	vParent[startNode] = -1;	// -1 means startNode

	std::stack<int> nodes;
	nodes.push(startNode);

	while (!nodes.empty())
	{
		int currNode = nodes.top();
		nodes.pop();

		const std::list<Edge *> adj = graph.getAdjacent(currNode);
		for (const auto &edge : adj)
		{
			if (vParent[edge->v] == INT_MAX)
			{
				vParent[edge->v] = currNode;
				nodes.push(edge->v);
			}
		}
	}

	// done with processing now print the data
	for (int i = 0; i < vParent.size(); ++i)
	{
		if (i != startNode)
		{
			std::vector<int> path;
			int currNode = i;
			path.push_back(currNode);
			while (vParent[currNode] != startNode)
			{
				if (vParent[currNode] == INT_MAX)
				{
					std::cout << "Can't reach FROM " << i << " TO " << startNode << "\n";
					path.clear();
					break;
				}
				path.push_back(vParent[currNode]);
				currNode = vParent[currNode];
			}

			if (!path.empty())
			{
				std::cout << "Start = " << startNode << " , Target = " << i << "\n";
				std::cout << "\tPath => " << startNode;
				for (int i = path.size() - 1; i >= 0; --i)
				{
					std::cout << "--->" << path[i];
				}
				std::cout << "\n\n";
			}
		}
	}
}

void testDFS()
{
	int numOfVertices = 9;
	bool isUndriected = true;

	Graph graph(numOfVertices, isUndriected);

	// src, dst, weight
	graph.addEdge(1, 0, 4);

	graph.addEdge(2, 1, 8);

	graph.addEdge(3, 2, 7);

	graph.addEdge(4, 3, 9);

	graph.addEdge(5, 2, 4);
	graph.addEdge(5, 3, 14);
	graph.addEdge(5, 4, 10);

	graph.addEdge(6, 5, 2);

	graph.addEdge(7, 0, 8);
	graph.addEdge(7, 1, 11);
	graph.addEdge(7, 6, 1);

	graph.addEdge(8, 2, 2);
	graph.addEdge(8, 6, 6);
	graph.addEdge(8, 7, 7);

	graph.print();

	std::cout << "\n*****************************************\n";
	std::cout << "               Calling DFS";
	std::cout << "\n*****************************************\n";
	DFS(graph, 8);
}