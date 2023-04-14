#pragma once

#include <memory>

#define PRINT_DEBUG_LOG

template<typename _dataType>
class LinkList;

template<typename _dataType>
std::ostream& operator<<(std::ostream &out, const LinkList<_dataType> &ll);

template<typename _dataType>
class LinkList
{
	typedef struct Node
	{
		std::shared_ptr<Node>		m_pNext;
		std::shared_ptr<Node>		m_pPrev;
		_dataType					m_data;

		Node(const _dataType &val)
			:m_data{ val }
		{
#ifdef PRINT_DEBUG_LOG
			std::cout << "Ctor called = " << m_data << "\n";
#endif
		}

		Node(_dataType &&val)
			:m_data{ std::move(val) }
		{
#ifdef PRINT_DEBUG_LOG
			std::cout << "Ctor called = " << m_data << "\n";
#endif
		}

		~Node()
		{
#ifdef PRINT_DEBUG_LOG
			std::cout << "Dtor called = " << m_data << "\n";
#endif
		}
	}Node;

public:
	LinkList();
	~LinkList();

	LinkList(std::initializer_list<_dataType> inList);

	LinkList(const LinkList &other);
	LinkList& operator=(const LinkList &other);

	LinkList(LinkList &&other);
	LinkList& operator=(LinkList &&other);

	std::size_t size() const;
	bool empty() const;

	void push_back(const _dataType &val);
	void push_back(_dataType &&val);

	void push_front(const _dataType &val);
	void push_front(_dataType &&val);

	bool insert(std::size_t pos, const _dataType &val);
	bool insert(std::size_t pos, _dataType &&val);

	bool eraseVal(const _dataType &val);
	bool eraseAt(std::size_t pos);

	void pop_back();
	void pop_front();

	_dataType& front();
	const _dataType& front() const;

	_dataType& back();
	const _dataType& back() const;

	void clear();

	bool find(const _dataType &val) const;

	friend std::ostream& operator<< <>(std::ostream &out, const LinkList<_dataType> &ll);

protected:
	void remove(std::shared_ptr<Node> node);

	std::ostream& print(std::ostream &out) const;

private:
	std::shared_ptr<Node>			m_pHead;
	std::shared_ptr<Node>			m_pTail;
	std::size_t						m_nSize;
};

template<typename _dataType>
LinkList<_dataType>::LinkList()
	:m_nSize{}
{
}

template<typename _dataType>
LinkList<_dataType>::~LinkList()
{
	clear();
}

template<typename _dataType>
LinkList<_dataType>::LinkList(std::initializer_list<_dataType> inList)
	:m_nSize{}
{
	for (auto &val : inList)
	{
		push_back(val);
	}
}

template<typename _dataType>
LinkList<_dataType>::LinkList(const LinkList<_dataType> &other)
	:m_nSize{}
{
	std::shared_ptr<Node> p = other.m_pHead;
	while (m_nSize != other.m_nSize)
	{
		push_back(p->m_data);
		p = p->m_pNext;
		m_nSize++;
	}
}

template<typename _dataType>
LinkList<_dataType>& LinkList<_dataType>::operator=(const LinkList<_dataType> &other)
{
	if (this != &other)
	{
		clear();
		std::shared_ptr<Node> p = other.m_pHead;
		while (m_nSize != other.m_nSize)
		{
			push_back(p->m_data);
			p = p->m_pNext;
			m_nSize++;
		}
	}
	return *this;
}

template<typename _dataType>
LinkList<_dataType>::LinkList(LinkList<_dataType> &&other)
	:m_nSize{}
{
	m_pHead = std::move(other.m_pHead);
	m_pTail = std::move(other.m_pTail);
	m_nSize = other.m_nSize;
	other.m_nSize = 0;
}

template<typename _dataType>
LinkList<_dataType>& LinkList<_dataType>::operator=(LinkList<_dataType> &&other)
{
	if (this != &other)
	{
		clear();
		m_pHead = std::move(other.m_pHead);
		m_pTail = std::move(other.m_pTail);
		m_nSize = other.m_nSize;
		other.m_nSize = 0;
	}
	return *this;
}

template<typename _dataType>
std::size_t LinkList<_dataType>::size() const
{
	return m_nSize;
}

template<typename _dataType>
bool LinkList<_dataType>::empty() const
{
	return m_nSize == 0;
}

template<typename _dataType>
void LinkList<_dataType>::push_back(const _dataType &val)
{
	if (!m_pHead)
	{
		m_pHead.reset(new Node(val));
		m_pTail = m_pHead;
		m_nSize++;
	}
	else
	{
		m_pTail->m_pNext.reset(new Node(val));
		m_pTail->m_pNext->m_pPrev = m_pTail;
		m_pTail = m_pTail->m_pNext;

		m_nSize++;
	}
}

template<typename _dataType>
void LinkList<_dataType>::push_back(_dataType &&val)
{
	if (!m_pHead)
	{
		m_pHead.reset(new Node(std::move(val)));
		m_pTail = m_pHead;
		m_nSize++;
	}
	else
	{
		m_pTail->m_pNext.reset(new Node(std::move(val)));
		m_pTail->m_pNext->m_pPrev = m_pTail;
		m_pTail = m_pTail->m_pNext;

		m_nSize++;
	}
}

template<typename _dataType>
void LinkList<_dataType>::push_front(const _dataType &val)
{
	if (!m_pHead)
	{
		m_pHead.reset(new Node(val));
		m_pTail = m_pHead;
		m_nSize++;
	}
	else
	{
		m_pHead->m_pPrev.reset(new Node(val));
		m_pHead->m_pPrev->m_pNext = m_pHead;
		m_pHead = m_pHead->m_pPrev;

		m_nSize++;
	}
}

template<typename _dataType>
void LinkList<_dataType>::push_front(_dataType &&val)
{
	if (!m_pHead)
	{
		m_pHead.reset(new Node(std::move(val)));
		m_pTail = m_pHead;
		m_nSize++;
	}
	else
	{
		m_pHead->m_pPrev.reset(new Node(std::move(val)));
		m_pHead->m_pPrev->m_pNext = m_pHead;
		m_pHead = m_pHead->m_pPrev;

		m_nSize++;
	}
}

template<typename _dataType>
bool LinkList<_dataType>::insert(std::size_t pos, const _dataType &val)
{
	if (pos < 0 || pos > m_nSize)
	{
		return false;
	}

	if (pos == 0)
	{
		push_front(val);
	}
	else if (pos == m_nSize)
	{
		push_back(val);
	}
	else
	{
		std::shared_ptr<Node> p = m_pHead;
		for (std::size_t i = 0; i < pos - 1; ++i)
		{
			p = p->m_pNext;
		}
		std::shared_ptr<Node> next = p->m_pNext;
		p->m_pNext.reset(new Node(val));
		p->m_pNext->m_pPrev = p;
		p->m_pNext->m_pNext = next;
		next->m_pPrev = p->m_pNext;

		m_nSize++;
	}
	return true;
}

template<typename _dataType>
bool LinkList<_dataType>::insert(std::size_t pos, _dataType &&val)
{
	if (pos < 0 || pos > m_nSize)
	{
		return false;
	}
	if (pos == 0)
	{
		push_front(std::move(val));
	}
	else if (pos == m_nSize)
	{
		push_back(std::move(val));
	}
	else
	{
		std::shared_ptr<Node> p = m_pHead;
		for (std::size_t i = 0; i < pos - 1; ++i)
		{
			p = p->m_pNext;
		}
		std::shared_ptr<Node> next = p->m_pNext;
		p->m_pNext.reset(new Node(val));
		p->m_pNext->m_pPrev = p;
		p->m_pNext->m_pNext = next;
		next->m_pPrev = p->m_pNext;

		m_nSize++;
	}
	return true;
}

template<typename _dataType>
bool LinkList<_dataType>::eraseVal(const _dataType &val)
{
	if (m_nSize == 0)
	{
		return false;
	}
	
	std::shared_ptr<Node> p = m_pHead;
	for (size_t i = 0; i < m_nSize; ++i)
	{
		if (p->m_data == val)
		{
			remove(p);
			return true;
		}
		p = p->m_pNext;
	}
	return false;
}

template<typename _dataType>
bool LinkList<_dataType>::eraseAt(std::size_t pos)
{
	if (m_nSize == 0 || pos < 0 || pos >= m_nSize)
	{
		return false;
	}

	std::shared_ptr<Node> p = m_pHead;
	for (size_t i = 0; i < pos; ++i)
	{
		p = p->m_pNext;
	}
	remove(p);
	return true;
}

template<typename _dataType>
void LinkList<_dataType>::pop_back()
{
	if (m_pTail && m_nSize > 1)
	{
		m_pTail = m_pTail->m_pPrev;
		m_pTail->m_pNext.reset();

		m_nSize--;
	}
	else if (m_nSize == 1)
	{
		m_pHead.reset();
		m_pTail.reset();
		m_nSize--;
	}
}

template<typename _dataType>
void LinkList<_dataType>::pop_front()
{
	if (m_pHead && m_nSize > 1)
	{
		m_pHead = m_pHead->m_pNext;
		m_pHead->m_pPrev.reset();

		m_nSize--;
	}
	else if (m_nSize == 1)
	{
		m_pHead.reset();
		m_pTail.reset();
		m_nSize--;
	}
}

template<typename _dataType>
_dataType& LinkList<_dataType>::front()
{
	return m_pHead->m_data;
}

template<typename _dataType>
const _dataType& LinkList<_dataType>::front() const
{
	return m_pHead->m_data;
}

template<typename _dataType>
_dataType& LinkList<_dataType>::back()
{
	return m_pTail->m_data;
}

template<typename _dataType>
const _dataType& LinkList<_dataType>::back() const
{
	return m_pTail->m_data;
}

template<typename _dataType>
void LinkList<_dataType>::clear()
{
	while (!empty())
	{
		pop_back();
	}
}

template<typename _dataType>
bool LinkList<_dataType>::find(const _dataType &val) const
{
	std::shared_ptr<Node> p = m_pHead;
	for (size_t i = 0; i < m_nSize; ++i)
	{
		if (p->m_data == val)
		{
			return true;
		}
		p = p->m_pNext;
	}
	return false;
}

template<typename _dataType>
void LinkList<_dataType>::remove(std::shared_ptr<Node> node)
{
	if (node)
	{
		if (node == m_pHead)
		{
			pop_front();
		}
		else if (node == m_pTail)
		{
			pop_back();
		}
		else
		{
			node->m_pPrev->m_pNext = node->m_pNext;
			node->m_pNext->m_pPrev = node->m_pPrev;
			m_nSize--;
		}
	}
}

template<typename _dataType>
std::ostream& LinkList<_dataType>::print(std::ostream &out) const
{
	out << "\nStart of PRINT\n";
	out << "\tSize of List = " << m_nSize << "\n";
	if (m_nSize != 0)
	{
		std::shared_ptr<Node> p = m_pHead;
		std::size_t i = 0;
		while (i++ != m_nSize)
		{
			out << "\t[" << i << "] = " << p->m_data << "\n";
			p = p->m_pNext;
		}
		out << "End of PRINT\n";
	}
	return out;
}

template<typename _dataType>
std::ostream& operator<<(std::ostream &out, const LinkList<_dataType> &ll)
{
	return ll.print(out);
}