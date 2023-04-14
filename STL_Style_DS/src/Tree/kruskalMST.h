#pragma once

#include "DisJointSet.h"
#include "Graph.h"
#include <queue>

std::vector<Edge> KruskalMST(const Graph &graph)
{
	std::vector<Edge>	mst;

	auto cmp = [](const Edge *e1, const Edge *e2) {
		return e1->w > e2->w;
	};
	std::priority_queue<const Edge *, std::vector<const Edge *>, decltype(cmp)> que(cmp);

	DisJointSet disjointSet;
	int v = graph.getNumberOfVertices();
	for (int i = 0; i < v; ++i)
	{
		disjointSet.makeSet(i);
	}

	const std::vector<std::list<Edge *>> vAdj = graph.getAllEdges();
	for (const auto &list : vAdj)
	{
		for (const auto &edge : list)
		{
			que.push(edge);
		}
	}

	while (!que.empty())
	{
		const Edge *edge = que.top();
		que.pop();

		int u = disjointSet.find(edge->src);
		int v = disjointSet.find(edge->dst);

		if (u != v)
		{
			mst.push_back(Edge(*edge));
			disjointSet.makeUnion(u, v);
		}
	}
	return mst;
}

void printMstData(const std::vector<Edge> &mst)
{
	std::cout << "\nAs per Kruskal following are the edges in the MST : \n";
	int sum = 0;
	for (auto &x : mst)
	{
		sum += x.w;
		std::cout << x.src << " --> " << x.dst << " (" << x.w << ")\n";
	}
	std::cout << "Minimum cost of spanning tree : " << sum << "\n";
}

void testKruskal_1()
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


	printMstData(KruskalMST(graph));
}

void testKruskal_2()
{
	int numOfVertices = 4;
	bool isUndriected = true;

	Graph graph(numOfVertices, isUndriected);

	// src, dst, weight
	graph.addEdge(0, 1, 10);

	graph.addEdge(0, 2, 6);

	graph.addEdge(0, 3, 5);

	graph.addEdge(1, 3, 15);

	graph.addEdge(2, 3, 4);

	graph.print();

	printMstData(KruskalMST(graph));
}