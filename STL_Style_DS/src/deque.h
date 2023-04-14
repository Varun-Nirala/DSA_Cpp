#pragma once

#include "DoublyLinkList.h"

void TestDeque();

template<typename T, typename container = DoublyLinkList<T>>
class Deque
{
public:
	size_t size() const { return m_container.size(); }
	bool empty() const { return m_container.empty(); }

	const T& front() const { return m_container.front(); }
	T& front() { return m_container.front(); }

	const T& back() const { return m_container.back(); }
	T& back() { return m_container.back(); }

	void push_front(const T &val) { m_container.push_front(val); }
	void push_back(const T &val) { m_container.push_back(val); }

	void pop_front() { m_container.pop_back(); }
	void pop_back() { m_container.pop_back(); }
private:
	container m_container;
};

void TestDeque()
{
	using std::cout;
	using std::cin;
	using std::endl;

	cout << "STARTED TESTING : " << __FUNCTION__ << endl;

	Deque<int> deque;

	if (deque.empty())
	{
		cout << "Empty : size = " << deque.size() << endl;
	}

	for (int i = 0; i < 5; ++i)
	{
		if (i % 2)
		{
			cout << "Pushed in front = " << 10 * (i + 1) << endl;
			deque.push_front(10 * (i + 1));
		}
		else
		{
			cout << "Pushed in back = " << 10 * (i + 1) << endl;
			deque.push_back(10 * (i + 1));
		}
	}

	while (!deque.empty())
	{
		cout << "Poping from back = " << deque.back() << endl;
		deque.pop_back();
	}

	cout << "ENDED TESTING : " << __FUNCTION__ << "\n\n";
}
