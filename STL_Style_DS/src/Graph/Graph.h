#ifndef __GRAPH_1_H__
#define __GRAPH_1_H__

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
#include <map>

namespace ns_Graph1
{
template<typename T>
class Node
{
public:
	using value_type		= T;
	using pair_type			= typename std::pair<Node<T>* /* Node which can be reached */, int /* Weight associated with it */>;
	using vec_type			= typename std::vector<pair_type>;
	using iter_type			= typename vec_type::iterator;
	using const_iter_type	= typename vec_type::const_iterator;

public:
	explicit Node(const T& data)
		: m_data(data)
	{}

	~Node() { clear(); }

	bool addEdge(Node<T>* dst, int weight = 0);

	inline bool isConnected(const Node<T>& dst) const { return !(search(dst) == m_neighbourNodes.end()); }
	inline bool isConnected(const T& dst) const { return !(search(dst) == m_neighbourNodes.end()); }

	inline int getWeight(const Node<T>& dst) const { return search(dst)->second; }
	inline int getWeight(const T& dst) const { return search(dst)->second; }

	const T& getData() const { return m_data; }

	inline bool removeEdge(const T& dst);

	inline vec_type& getAllNode() { return m_neighbourNodes; }

private:
	inline void clear();

	inline iter_type search(const Node<T>* dst);
	inline iter_type search(const T& dst);

	inline const_iter_type search(const Node<T>* dst) const;
	inline const_iter_type search(const T& dst) const;

private:
	vec_type	m_neighbourNodes{};
	T			m_data{};
};

template<typename T>
bool Node<T>::addEdge(Node<T>* dst, int weight)
{
	iter_type it = search(dst);

	if (it != m_neighbourNodes.end())
	{
		// if already present just update the weight
		it->second = weight;
	}
	else
	{
		m_neighbourNodes.push_back(make_pair(dst, weight));
	}
	return true;
}

template<typename T>
bool Node<T>::removeEdge(const T& dst)
{
	iter_type it = search(dst);
	if (it != m_neighbourNodes.end())
	{
		m_neighbourNodes.erase(it);
		return true;
	}
	return false;
}

template<typename T>
void Node<T>::clear()
{
	for (auto pp : m_neighbourNodes)
	{
		delete pp.first;
	}
	m_neighbourNodes.clear();
}

template<typename T>
typename Node<T>::iter_type Node<T>::search(const Node<T>* dst)
{
	return std::find_if(m_neighbourNodes.begin(), m_neighbourNodes.end(),
		[&](pair_type& pp) -> bool
		{
			return pp.first == dst;
		});
}

template<typename T>
typename Node<T>::iter_type Node<T>::search(const T& dst)
{
	return std::find_if(m_neighbourNodes.begin(), m_neighbourNodes.end(),
		[&](pair_type& pp) -> bool
		{
			return pp.first->m_data == dst;
		});
}

template<typename T>
typename Node<T>::const_iter_type Node<T>::search(const Node<T>* dst) const
{
	return std::find_if(m_neighbourNodes.begin(), m_neighbourNodes.end(),
		[&](const pair_type& pp) -> bool
		{
			return pp.first == dst;
		});
}

template<typename T>
typename Node<T>::const_iter_type Node<T>::search(const T& dst) const
{
	return std::find_if(m_neighbourNodes.begin(), m_neighbourNodes.end(),
		[&](const pair_type& pp) -> bool
		{
			return pp.first->m_data == dst;
		});
}

template <typename T>
class Graph
{
public:
	using value_type			= T;
	using vec_type				= typename std::vector<Node<T> *>;
	using iter_type				= typename vec_type::iterator;

public:
	// It should always succeed, it will either create new edge or update the existing with new weight
	bool addEdge(const T& src, const T& dst, int weight = 0);

	// Provide weight to delete only that path
	bool removeEdge(const T& src, const T& dst);

	// return true if dst is directly connected to src 
	bool isConnected(const T& src, const T& dst);

	// return true if dst is directly connected to src, and fills up the weight ref,
	// otherwise just return false
	bool getWeight(const T& src, const T& dst, int& weight);

	inline bool hasNode(const T& val) const { return !(search(val) == m_allNodes.end()); }
	inline Node<T>* getNode(const T &val) { return (*search(val)); }

	inline size_t size() const { return m_allNodes.size(); }
	inline bool empty() const { return m_allNodes.empty(); }

	// Traversal Algorithms
	void BFS(const T& src);
	void DFS(const T& src);

private:
	inline iter_type search(const T& val);
	inline Node<T>* addNode(const T& data);

private:
	vec_type		m_allNodes;
};

// It should always succeed, it will either create new edge or update the existing with new weight
template<typename T>
bool Graph<T>::addEdge(const T& src, const T& dst, int weight)
{
	Node<T> *srcNode{};
	Node<T> *dstNode{};

	// Search or create srcNode
	iter_type it = search(src);
	if (it == m_allNodes.end())
	{
		srcNode = addNode(src);
	}
	else
	{
		srcNode = *it;
	}

	// Search or create dstNode
	it = search(dst);
	if (it == m_allNodes.end())
	{
		dstNode = addNode(dst);
	}
	else
	{
		dstNode = *it;
	}
	// Now we are sure that both node exists
	return srcNode->addEdge(dstNode, weight);
}

// Provide weight to delete only that path
template<typename T>
bool Graph<T>::removeEdge(const T& src, const T& dst)
{
	iter_type it = search(src);
	if (it != m_allNodes.end())
	{
		return (*it)->removeEdge(dst);
	}
	return false;
}

// return true if dst is directly connected to src 
template<typename T>
bool Graph<T>::isConnected(const T& src, const T& dst)
{
	iter_type it = search(src);
	if (it != m_allNodes.end())
	{
		return (*it)->isConnected(dst);
	}
	return false;
}

// return true if dst is directly connected to src, and fills up the weight ref,
// otherwise just return false
template<typename T>
bool Graph<T>::getWeight(const T& src, const T& dst, int& weight)
{
	iter_type it = search(src);
	if (it != m_allNodes.end())
	{
		weight = (*it)->getWeight(dst);
		return true;
	}
	return false;
}

// Traversal Algorithms
template<typename T>
void Graph<T>::BFS(const T& src)
{
	if (m_allNodes.empty())
		return;

	std::map<T, bool> mVisited;
	for (auto p : m_allNodes)
	{
		mVisited[p->getData()] = false;
	}

	mVisited[src] = true;

	std::list<Node<T>*> nodeQeue;
	nodeQeue.push_back(getNode(src));

	Node<T>* currNode = NULL;
	while (!nodeQeue.empty())
	{
		currNode = nodeQeue.front();
		nodeQeue.pop_front();

		std::cout << currNode->getData() << " ";

		for (const std::pair<Node<T>*, int> nodePair : currNode->getAllNode())
		{
			std::map<T, bool>::iterator it = mVisited.find(nodePair.first->getData());
			if (it != mVisited.end())
			{
				if (!it->second)
				{
					it->second = true;
					nodeQeue.push_back(nodePair.first);
				}
			}
		}
	}
	cout << '\n';
}

template<typename T>
void Graph<T>::DFS(const T& src)
{
	if (m_allNodes.empty())
		return;

	std::map<T, bool> mVisited;
	for (auto p : m_allNodes)
	{
		mVisited[p->getData()] = false;
	}

	std::list<Node<T>*> nodeQeue;
	nodeQeue.push_front(getNode(src));
	Node<T>* currNode = NULL;
	while (!nodeQeue.empty())
	{
		currNode = nodeQeue.front();
		nodeQeue.pop_front();

		if (!mVisited[currNode->getData()])
		{
			std::cout << currNode->getData() << " ";
			mVisited[currNode->getData()] = true;
			for (const std::pair<Node<T>*, int> nodePair : currNode->getAllNode())
			{
				nodeQeue.push_front(nodePair.first);
			}
		}
	}
	cout << '\n';
}

template<typename T>
typename Graph<T>::iter_type Graph<T>::search(const T& val)
{
	return std::find_if(m_allNodes.begin(), m_allNodes.end(), [&](Node<T>* data) {
		return data->getData() == val;
		});
}

template<typename T>
typename Node<T>* Graph<T>::addNode(const T& data)
{
	m_allNodes.emplace_back(new Node<T>(data));
	return m_allNodes.back();
}


// Testing code
template<typename T>
void testAndPrint(ns_Graph1::Graph<T>& graph, const T& src, const T& dst)
{
	int weight = -1;
	if (graph.isConnected(src, dst))
	{
		graph.getWeight(src, dst, weight);
		cout << src << " --- " << weight << " ---> " << dst << '\n';
	}
	else
	{
		cout << src << " --- X ---> " << dst << "       Not Connected" << '\n';
	}
}

struct Data
{
	char	_from{};
	char	_to{};
	int		_cost{};

	Data(char f, char t, int c = 0)
		: _from(f)
		, _to(t)
		, _cost(c)
	{}

	inline void print() const { std::cout << _from << "---- [ " << _cost << " ] ----" << _to << '\n'; }
};

void test_1_BasicSanity()
{
	std::cout << "Running Test 1 :: FunctionName " << __FUNCTION__ << '\n';

	std::vector<Data> vec;
	vec.emplace_back(Data{ 'A', 'B', 1 });
	vec.emplace_back(Data{ 'B', 'A', 0 });
	vec.emplace_back(Data{ 'B', 'D', 2 });
	vec.emplace_back(Data{ 'C', 'A', 3 });
	vec.emplace_back(Data{ 'C', 'E', 2 });
	vec.emplace_back(Data{ 'E', 'D', 5 });
	
	ns_Graph1::Graph<char> graph;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		graph.addEdge(vec[i]._from, vec[i]._to, vec[i]._cost);
	}

	for (size_t i = 0; i < vec.size(); ++i)
	{
		testAndPrint<char>(graph, vec[i]._from, vec[i]._to);
	}

	std::cout << "Removing A to B edge from A\n";
	graph.removeEdge('A', 'B');

	testAndPrint<char>(graph, 'A', 'B');
	testAndPrint<char>(graph, 'A', 'E');
}

void test_2_BFS()
{
	std::cout << "\n\nRunning Test 2 :: FunctionName " << __FUNCTION__ << '\n';

	std::vector<Data> vec;
	vec.emplace_back(Data{ '0', '1' });
	vec.emplace_back(Data{ '0', '2' });
	vec.emplace_back(Data{ '1', '2' });
	vec.emplace_back(Data{ '2', '3' });
	vec.emplace_back(Data{ '2', '0' });

	vec.emplace_back(Data{ '3', '3' });

	ns_Graph1::Graph<char> graph;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		graph.addEdge(vec[i]._from, vec[i]._to, vec[i]._cost);
	}

	char src = '2';
	std::cout << "BFS traversal SRC as :: " << src << '\n';
	graph.BFS(src);
}

void test_3_DFS()
{
	std::cout << "\n\nRunning Test 3 :: FunctionName " << __FUNCTION__ << '\n';
	std::vector<Data> vec;
	vec.emplace_back(Data{ '0', '1' });
	vec.emplace_back(Data{ '0', '2' });
	vec.emplace_back(Data{ '1', '2' });
	vec.emplace_back(Data{ '2', '3' });
	vec.emplace_back(Data{ '2', '0' });

	vec.emplace_back(Data{ '3', '3' });

	ns_Graph1::Graph<char> graph;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		graph.addEdge(vec[i]._from, vec[i]._to, vec[i]._cost);
	}
	char src = '2';
	std::cout << "DFS traversal SRC as :: " << src << '\n';
	graph.DFS(src);
}

void test_Graph1()
{
	test_1_BasicSanity();
	test_2_BFS();
	test_3_DFS();
}
}
#endif //#ifndef __GRAPH_1_H__