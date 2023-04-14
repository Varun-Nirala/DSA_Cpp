#ifndef __SINGLE_LIST_H__
#define __SINGLE_LIST_H__

#include <initializer_list>
#include <functional>
#include <memory>
#include <cassert>

#include "Common/logger.h"
#include "Common/helper.h"

namespace nsCpp_DS {
template<typename T>
class SingleList;

template<typename SListNode>
class Const_SL_Iterator;

template<typename SListNode>
class SL_Iterator;

template<typename _value_type, typename _pointer_type>
struct _SingleListNode
{
    using _NodePtr = typename std::pointer_traits<_pointer_type>::template rebind<_SingleListNode>;

    using value_type        = _value_type;
    using pointer_type      = _pointer_type;
    using node_pointer_type = _NodePtr;
    using iterator          = SL_Iterator<_SingleListNode<value_type, pointer_type>>;
    using const_iterator    = Const_SL_Iterator<_SingleListNode<value_type, pointer_type>>;

    node_pointer_type       m_next{};
    value_type              m_value{};

    ~_SingleListNode() = default;

    _SingleListNode() = default;
    explicit _SingleListNode(const value_type& val)
        : m_value(val)
    {}

    explicit _SingleListNode(value_type&&val)
        : m_value(std::move(val))
    {}

    _SingleListNode(const value_type& val, node_pointer_type next)
        : m_value(val)
        , m_next(next)
    {}

    _SingleListNode(value_type&& val, node_pointer_type next)
        : m_value(std::move(val))
        , m_next(next)
    {}

    _SingleListNode(const _SingleListNode&) = delete;
    _SingleListNode& operator=(const _SingleListNode&) = delete;

    _SingleListNode(_SingleListNode&&) noexcept = default;
    _SingleListNode& operator=(_SingleListNode&&) noexcept = default;

    static _SingleListNode* createNode(const value_type& val) { return new _SingleListNode(val); }
    static _SingleListNode* createNode(value_type&& val) { return new _SingleListNode(std::move(val)); }
    static _SingleListNode* createNode(const value_type& val, node_pointer_type next) { return new _SingleListNode(val, next); }
    static _SingleListNode* createNode(value_type&& val, node_pointer_type next) { return new _SingleListNode(std::move(val), next); }

};

template<typename SlNode>
class Const_SL_Iterator 
{
    friend class SingleList<typename SlNode::value_type>;
public:
    using Node              = SlNode;
    using NodePtr           = typename SlNode::node_pointer_type;
	using iterator_category = std::forward_iterator_tag;
	using value_type		= typename SlNode::value_type;
    using reference         = value_type&;
    using this_type         = Const_SL_Iterator<SlNode>;

public:
    Const_SL_Iterator() = default;
    Const_SL_Iterator(const this_type &rhs) : m_ptr(rhs.m_ptr) { }

	const reference operator*() const { return m_ptr->m_value; }
	const NodePtr operator->() const { return m_ptr; }

	this_type& operator++() { m_ptr = m_ptr->m_next; return *this; }
    this_type operator++(int) { NodePtr tmp{ m_ptr }; m_ptr = m_ptr->m_next; return this_type(tmp); }

	bool operator==(const this_type& rhs) const { return m_ptr == rhs.m_ptr; }
    bool operator!=(const this_type& rhs) const { return m_ptr != rhs.m_ptr; }

protected:
    Const_SL_Iterator(NodePtr p) : m_ptr(p) { }
    inline NodePtr getPointer() { return m_ptr; }
protected:
    NodePtr         m_ptr{};
};

template<typename SlNode>
class SL_Iterator : public Const_SL_Iterator<SlNode>
{
    friend class SingleList<typename SlNode::value_type>;
    using Base = Const_SL_Iterator<SlNode>;
public:
    using Base::Node;
    using Base::NodePtr;
    using Base::iterator_category;
    using Base::value_type;
    using Base::reference;

    using this_type = SL_Iterator<SlNode>;

public:
    SL_Iterator() = default;
    SL_Iterator(const this_type & rhs) : m_ptr(rhs.m_ptr) { }

    reference operator*() const { return m_ptr->m_value; }
    NodePtr operator->() const { return m_ptr; }

    this_type& operator++() { m_ptr = m_ptr->m_next; return *this; }
    this_type operator++(int) { NodePtr tmp{ m_ptr }; m_ptr = m_ptr->m_next; return this_type(tmp); }

    bool operator==(const this_type& rhs) const { return m_ptr == rhs.m_ptr; }
    bool operator!=(const this_type& rhs) const { return m_ptr != rhs.m_ptr; }

protected:
    SL_Iterator(NodePtr p) : Base(p) { }
};

template<typename T>
class SingleList
{
    using this_type         = SingleList<T>;
    using Node              = _SingleListNode<T, void*>;
    using NodePtr           = Node *;
public:
	using value_type				= T;
	using pointer					= T*;
	using const_pointer				= const T*;
	using reference					= value_type&;
	using const_reference			= const value_type&;
    using iterator				    = typename Node::iterator;
    using const_iterator			= typename Node::const_iterator;
	using size_type					= size_t;
	using difference_type			= ptrdiff_t;

	static const size_type npos		= (size_type)-1;
	static const size_type kMaxSize = (size_type)-2;
public:
    // Member functions
    ~SingleList();

    SingleList() = default;
    explicit SingleList(const size_type count, const value_type &value);
    explicit SingleList(const size_type count);
    
    template<typename InputIterator>
    SingleList(InputIterator first, InputIterator last);

    SingleList(std::initializer_list<T> iList);

    SingleList(const SingleList &other);
    SingleList(SingleList &&other) noexcept;

    SingleList& operator=(const SingleList &other);
    SingleList& operator=(SingleList &&other) noexcept;
    SingleList& operator=(std::initializer_list<T> iList);

    void assign(size_type count, const value_type& value);

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last);

    void assign(std::initializer_list<T> iList);

    // Element access
    reference front();
    const_reference front() const;

    // Iterators
    iterator before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_type max_size() const noexcept;

    // Modifiers
    void clear() noexcept;

    iterator insert_after(const_iterator pos, const value_type& value);
    iterator insert_after(const_iterator pos, value_type &&value);
    iterator insert_after(const_iterator pos, size_type count, const value_type& value);

    template<typename InputIterator>
    iterator insert_after(const_iterator pos, InputIterator first, InputIterator last);

    iterator insert_after(const_iterator pos, std::initializer_list<T> iList);

    template<typename ...Args>
    iterator emplace_after(const_iterator pos, Args&&... args);

    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);

    void push_front(const value_type &value);
    void push_front(value_type &&value);

    template<typename ...Args>
    reference emplace_front(Args&&... args);

    void pop_front();

    void resize(size_type count);
    void resize(size_type count, const value_type& value);

    void swap(this_type &other);

    // Operations
    void merge(this_type& other);
    void merge(this_type&& other);

    template<typename Compare>
    void merge(this_type& other, Compare comp);

    template<typename Compare>
    void merge(this_type&& other, Compare comp);

    void splice_after(const_iterator pos, this_type& other);
    void splice_after(const_iterator pos, this_type&& other);
    void splice_after(const_iterator pos, this_type& other, const_iterator it);
    void splice_after(const_iterator pos, this_type&& other, const_iterator it);
    void splice_after(const_iterator pos, this_type& other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, this_type&& other, const_iterator first, const_iterator last);

    size_type remove(const value_type& value);

    template<typename UnaryPredicate>
    size_type remove_if(UnaryPredicate p);

    void reverse() noexcept;

    size_type unique();

    template<typename BinaryPredicate>
    size_type unique(BinaryPredicate p);

    void sort();
    template<typename Compare>
    void sort(Compare comp);
private:
    void clear(NodePtr& list);
    void removeNode(NodePtr node) noexcept;
    iterator findPosition(const_iterator pos) const;
    void createOrReuse(NodePtr& ptr, const value_type& value);
    void createOrReuse(NodePtr& ptr, value_type&& value);

private:
    Node            m_preHead{};
};

template<typename T>
inline SingleList<T>::~SingleList()
{
    clear();
}

template<typename T>
inline SingleList<T>::SingleList(const size_type count, const value_type& value)
{
    assign(count, value);
}

template<typename T>
inline SingleList<T>::SingleList(const size_type count)
{
    assign(count, value_type{});
}

template<typename T>
template<typename InputIterator>
inline SingleList<T>::SingleList(InputIterator first, InputIterator last)
{
    assign(first, last);
}

template<typename T>
inline SingleList<T>::SingleList(std::initializer_list<value_type> iList)
{
    assign(iList.begin(), iList.end());
}

template<typename T>
inline SingleList<T>::SingleList(const SingleList<value_type>& other)
{
    assign(other.begin(), other.end());
}

template<typename T>
inline SingleList<T>::SingleList(SingleList<value_type>&& other) noexcept
{
    m_preHead = std::exchange(other.m_preHead, Node{});
}

template<typename T>
inline SingleList<T>& SingleList<T>::operator=(const SingleList<value_type>& other)
{
    if (this != &other)
    {
        assign(other.begin(), other.end());
    }
    return *this;
}

template<typename T>
inline SingleList<T>& SingleList<T>::operator=(SingleList<value_type>&& other) noexcept
{
    if (this != &other)
    {
        clear();
        m_preHead = std::exchange(other.m_preHead, Node{});
    }
    return *this;
}

template<typename T>
inline SingleList<T>& SingleList<T>::operator=(std::initializer_list<value_type> iList)
{
    if (this != &other)
    {
        assign(iList.begin(), iList.end());
    }
    return *this;
}

template<typename T>
inline void SingleList<T>::assign(size_type count, const value_type& value)
{
    if (count == 0)
    {
        return;
    }
    NodePtr p{ &m_preHead };
    while (count--)
    {
        createOrReuse(p, value);
    }
    clear(p->m_next);
}

template<typename T>
template<typename InputIterator>
inline void SingleList<T>::assign(InputIterator first, InputIterator last)
{
    NodePtr p{ &m_preHead };
    for (;first != last; ++first)
    {
        createOrReuse(p, *first);
    }
    clear(p->m_next);
}

template<typename T>
inline void SingleList<T>::assign(std::initializer_list<value_type> iList)
{
    assign(iList.begin(), iList.end());
}

// Element access
template<typename T>
inline typename SingleList<T>::reference SingleList<T>::front()
{
    return m_preHead.m_next->m_value;
}

template<typename T>
inline typename SingleList<T>::const_reference SingleList<T>::front() const
{
    return m_preHead.m_next->m_value;
}

// Iterators
template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::before_begin() noexcept
{
    return iterator(&m_preHead);
}

template<typename T>
inline typename SingleList<T>::const_iterator SingleList<T>::before_begin() const noexcept
{
    return const_iterator(&m_preHead);
}

template<typename T>
inline typename SingleList<T>::const_iterator SingleList<T>::cbefore_begin() const noexcept
{
    return before_begin();
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::begin() noexcept
{
    return iterator(m_preHead.m_next);
}

template<typename T>
inline typename SingleList<T>::const_iterator SingleList<T>::begin() const noexcept
{
    return const_iterator(m_preHead.m_next);
}

template<typename T>
inline typename SingleList<T>::const_iterator SingleList<T>::cbegin() const noexcept
{
    return begin();
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::end() noexcept
{
    return iterator(nullptr);
}

template<typename T>
inline typename SingleList<T>::const_iterator SingleList<T>::end() const noexcept
{
    return const_iterator(nullptr);
}

template<typename T>
inline typename SingleList<T>::const_iterator SingleList<T>::cend() const noexcept
{
    return end();
}

// Capacity
template<typename T>
inline bool SingleList<T>::empty() const noexcept
{
    return return m_preHead.m_next == nullptr;
}

template<typename T>
inline typename SingleList<T>::size_type SingleList<T>::max_size() const noexcept
{
    return kMaxSize;
}

// Modifiers
template<typename T>
inline void SingleList<T>::clear() noexcept
{
    clear(m_preHead.m_next);
    m_preHead.m_next = nullptr;
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::insert_after(const_iterator pos, const value_type& value)
{
    return insert_after(pos, 1, value);
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::insert_after(const_iterator pos, value_type&& value)
{
    iterator it = findPosition(pos);
    if (it != end())
    {
        NodePtr ptr = it->getPointer();
        NodePtr next = ptr->m_next;
        ptr->m_next = nullptr;
        createOrReuse(ptr, std::move(value));
        ptr->m_next = next;
        it = iterator(next);
    }
    return it;
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::insert_after(const_iterator pos, size_type count, const value_type& value)
{
    iterator it = findPosition(pos);
    if (it != end())
    {
        NodePtr ptr = it->getPointer();
        NodePtr next = ptr->m_next;
        ptr->m_next = nullptr;
        while (count--)
        {
            createOrReuse(ptr, std::move(value));
        }
        ptr->m_next = next;
        it = iterator(next);
    }
    return it;
}

template<typename T>
template<typename InputIterator>
inline typename SingleList<T>::iterator SingleList<T>::insert_after(const_iterator pos, InputIterator first, InputIterator last)
{
    iterator it = findPosition(pos);
    if (it != end())
    {
        NodePtr ptr = it->getPointer();
        NodePtr next = ptr->m_next;
        ptr->m_next = nullptr;
        for (;first != last; ++first)
        {
            createOrReuse(ptr, *first);
        }
        ptr->m_next = next;
        it = iterator(next);
    }
    return it;
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::insert_after(const_iterator pos, std::initializer_list<T> iList)
{
    return insert_after(pos, iList.begin(), iList.end());
}

template<typename T>
template<typename ...Args>
inline typename SingleList<T>::iterator SingleList<T>::emplace_after(const_iterator pos, Args&&... args)
{
    return insert_after(before_begin(), std::move(value_type(std::forward<Args>(args)...)));
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::erase_after(const_iterator pos)
{
    iterator it = findPosition(pos);
    if (it != end() && it->m_next)
    {
        NodePtr nodeToDelete = it->m_next;
        it->m_next = nodeToDelete->m_next;
        removeNode(nodeToDelete);
    }
    return ++it;
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::erase_after(const_iterator first, const_iterator last)
{
    iterator ret;
    while (first != last)
    {
        ret = erase_after(first++);
    }
    return ret;
}

template<typename T>
inline void SingleList<T>::push_front(const value_type& value)
{
    insert_after(before_begin(), value);
}

template<typename T>
inline void SingleList<T>::push_front(value_type&& value)
{
    insert_after(before_begin(), std::move(value));
}

template<typename T>
template<typename ...Args>
inline typename SingleList<T>::reference SingleList<T>::emplace_front(Args&&... args)
{
    return emplace_after(before_begin(), std::move(value_type(std::forward<Args>(args)...)));
}

template<typename T>
inline void SingleList<T>::pop_front()
{
    NodePtr nodeToDelete = m_preHead.m_next;
    m_preHead.m_next = nodeToDelete->m_next;
    removeNode(nodeToDelete);
}

template<typename T>
inline void SingleList<T>::resize(const size_type count)
{
    resize(count, value_type{});
}

template<typename T>
inline void SingleList<T>::resize(size_type count, const value_type& value)
{
    assign(count, value);
}


template<typename T>
inline void SingleList<T>::swap(this_type& other)
{
    m_preHead = std::exchange(other.m_preHead, m_preHead);
}

// Operations
template<typename T>
inline void SingleList<T>::merge(this_type& other)
{
    merge(other, std::less<>);
}

template<typename T>
inline void SingleList<T>::merge(this_type&& other)
{
    merge(std::move(other), std::less<>);
}

template<typename T>
template<typename Compare>
inline void SingleList<T>::merge(this_type& other, Compare comp)
{

}

template<typename T>
template<typename Compare>
inline void SingleList<T>::merge(this_type&& other, Compare comp)
{

}

template<typename T>
inline void SingleList<T>::splice_after(const_iterator pos, this_type& other)
{

}

template<typename T>
inline void SingleList<T>::splice_after(const_iterator pos, this_type&& other)
{

}

template<typename T>
inline void SingleList<T>::splice_after(const_iterator pos, this_type& other, const_iterator it)
{

}

template<typename T>
inline void SingleList<T>::splice_after(const_iterator pos, this_type&& other, const_iterator it)
{

}

template<typename T>
inline void SingleList<T>::splice_after(const_iterator pos, this_type& other, const_iterator first, const_iterator last)
{

}

template<typename T>
inline void SingleList<T>::splice_after(const_iterator pos, this_type&& other, const_iterator first, const_iterator last)
{

}

template<typename T>
inline typename SingleList<T>::size_type SingleList<T>::remove(const value_type& value)
{
    return remove_if(std::bind(std::equal_to, _1, value));
}

template<typename T>
template<typename UnaryPredicate>
inline typename SingleList<T>::size_type SingleList<T>::remove_if(UnaryPredicate p)
{
    size_type count = 0;
    bool bStop{ false };
    while (!bStop)
    {
        NodePtr curr{ m_preHead.m_next};
        NodePtr prev{&m_preHead};
        while (curr)
        {
            if (p(curr))
            {
                prev->m_next = curr->m_next;
                removeNode(curr);
                curr = prev;
                count++;
                break;
            }
            prev = curr;
            curr = curr->m_next;
        }
        bStop = !curr;
    }
    return count;
}

template<typename T>
inline void SingleList<T>::reverse() noexcept
{
    NodePtr prev{};
    NodePtr next{};
    NodePtr curr{ m_preHead.m_next};
    
    while (curr)
    {
        next = curr->m_next;
        curr->m_next = prev;
        prev = curr;
        curr = next;
    }
    m_preHead.m_next = prev;
}

template<typename T>
inline typename SingleList<T>::size_type SingleList<T>::unique()
{
    return unique(std::equal_to<>);
}

template<typename T>
template<typename BinaryPredicate>
inline typename SingleList<T>::size_type SingleList<T>::unique(BinaryPredicate p)
{

}

template<typename T>
inline void SingleList<T>::sort()
{
    sort(std::less<>);
}

template<typename T>
template<typename Compare>
inline void SingleList<T>::sort(Compare comp)
{

}

// Private
template<typename T>
inline void SingleList<T>::clear(NodePtr& head)
{
    NodePtr p{};
    while (head)
    {
        p = head->m_next;
        removeNode(head);
        head = p;
    }
    head = nullptr;
}

template<typename T>
inline void SingleList<T>::removeNode(NodePtr node) noexcept
{
    if (std::is_pointer_v<NodePtr>)
    {
        delete node;
        node = nullptr;
    }
    else if constexpr (std::is_same_v<NodePtr, std::unique_ptr<Node>> || std::is_same_v <NodePtr, std::shared_ptr<Node>>)
    {
        node = nullptr;
    }
    else
    {
        assert(!"Unkown Type!!!");
    }
}

template<typename T>
inline typename SingleList<T>::iterator SingleList<T>::findPosition(const_iterator pos) const
{
    iterator res{ end() };
    for (iterator it = begin(); it != res; ++it)
    {
        if (it == pos)
        {
            res = it;
            break;
        }
    }
    return res;
}

template<typename T>
inline void SingleList<T>::createOrReuse(NodePtr& ptr, const value_type& value)
{
    if (ptr->m_next)
    {
        ptr = ptr->m_next;
        ptr->m_value = value;
    }
    else
    {
        ptr->m_next = Node::createNode(value);
        ptr = ptr->m_next;
    }
}

template<typename T>
inline void SingleList<T>::createOrReuse(NodePtr& ptr, value_type&& value)
{
    if (ptr->m_next)
    {
        ptr = ptr->m_next;
        ptr->m_value = std::move(value);
    }
    else
    {
        ptr->m_next = Node::createNode(std::move(value));
        ptr = ptr->m_next;
    }
}

void test_SingleList_1()
{
    const char* testName = "Forward List.";
    ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n\n");

    SingleList<int> sl{ 1, 2, 3, 4, 5, 6 };

    for (SingleList<int>::iterator it = sl.begin(); it != sl.end(); ++it)
    {
        ns_Util::Logger::LOG_MSG(*it, ", ");
    }

    ns_Util::Logger::LOG_MSG("\n\n");
}

void test_SingleList_2()
{
    const char* testName = "Forward List.";
    ns_Util::Logger::LOG_MSG("Executing Test 2 : ", testName, "\n\n");

    ns_Util::Logger::LOG_MSG("\n\n");
}

void test_SingleList_3()
{
    const char* testName = "Forward List.";
    ns_Util::Logger::LOG_MSG("Executing Test 3 : ", testName, "\n\n");

    ns_Util::Logger::LOG_MSG("\n\n");
}

void test_SingleList()
{
    LOG_ENTRY;
    test_SingleList_1();
    test_SingleList_2();
    test_SingleList_3();
    LOG_EXIT;
    ns_Util::Logger::LOG_MSG("#####################################\n");
}
}   // namespace nsCpp_DS
#endif	// __SINGLE_LIST_H__