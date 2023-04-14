#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

#include <initializer_list>
#include <functional>
#include <memory>
#include <cassert>

#include "Common/logger.h"
#include "Common/helper.h"

namespace nsCpp_DS {
template<typename T>
class DoubleList;

template<typename DListNode>
class Const_DL_Iterator;

template<typename DListNode>
class DL_Iterator;

template<typename DListNode>
class Const_DL_Reverse_Iterator;

template<typename DListNode>
class DL_Reverse_Iterator;

template<typename _value_type, typename _pointer_type>
struct _DoubleListNode
{
    using _NodePtr = typename std::pointer_traits<_pointer_type>::template rebind<_DoubleListNode>;

    using value_type                = _value_type;
    using pointer_type              = _pointer_type;
    using node_pointer_type         = _NodePtr;
    using iterator                  = DL_Iterator<_DoubleListNode<value_type, pointer_type>>;
    using const_iterator            = Const_DL_Iterator<_DoubleListNode<value_type, pointer_type>>;
    using reverse_iterator          = DL_Reverse_Iterator<_DoubleListNode<value_type, pointer_type>>;
    using const_reverse_iterator    = Const_DL_Reverse_Iterator<_DoubleListNode<value_type, pointer_type>>;

    node_pointer_type       m_prev{};
    node_pointer_type       m_next{};
    value_type              m_value{};

    ~_DoubleListNode() = default;

    _DoubleListNode() = default;
    explicit _DoubleListNode(const value_type& val)
        : m_value(val)
    {}

    explicit _DoubleListNode(value_type&&val)
        : m_value(std::move(val))
    {}

    _DoubleListNode(const value_type& val, node_pointer_type prev, node_pointer_type next)
        : m_value(val)
        , m_prev(prev)
        , m_next(next)
    {}

    _DoubleListNode(value_type&& val, node_pointer_type prev, node_pointer_type next)
        : m_value(std::move(val))
        , m_prev(prev)
        , m_next(next)
    {}

    _DoubleListNode(const _DoubleListNode&) = delete;
    _DoubleListNode& operator=(const _DoubleListNode&) = delete;

    _DoubleListNode(_DoubleListNode&&) noexcept = default;
    _DoubleListNode& operator=(_DoubleListNode&&) noexcept = default;

    static _DoubleListNode* createNode(const value_type& val) { return new _DoubleListNode(val); }
    static _DoubleListNode* createNode(value_type&& val) { return new _DoubleListNode(std::move(val)); }
    static _DoubleListNode* createNode(const value_type& val, node_pointer_type prev, node_pointer_type next) { return new _DoubleListNode(val, prev, next); }
    static _DoubleListNode* createNode(value_type&& val, node_pointer_type prev, node_pointer_type next) { return new _DoubleListNode(std::move(val), prev, next); }
};

template<typename DlNode>
class Const_DL_Iterator 
{
    friend class DoubleList<typename DlNode::value_type>;
public:
    using Node              = DlNode;
    using NodePtr           = typename DlNode::node_pointer_type;
	using iterator_category = std::forward_iterator_tag;
	using value_type		= typename DlNode::value_type;
    using reference         = value_type&;
    using this_type         = Const_DL_Iterator<DlNode>;

public:
    Const_DL_Iterator() = default;
    Const_DL_Iterator(const this_type &rhs) : m_ptr(rhs.m_ptr) { }

	const reference operator*() const { return m_ptr->m_value; }
	const NodePtr operator->() const { return m_ptr; }

	this_type& operator++() { m_ptr = m_ptr->m_next; return *this; }
    this_type operator++(int) { NodePtr tmp{ m_ptr }; m_ptr = m_ptr->m_next; return this_type(tmp); }

	bool operator==(const this_type& rhs) const { return m_ptr == rhs.m_ptr; }
    bool operator!=(const this_type& rhs) const { return m_ptr != rhs.m_ptr; }

protected:
    Const_DL_Iterator(NodePtr p) : m_ptr(p) { }
    inline NodePtr getPointer() { return m_ptr; }
protected:
    NodePtr         m_ptr{};
};

template<typename DlNode>
class DL_Iterator : public Const_DL_Iterator<DlNode>
{
    friend class DoubleList<typename DlNode::value_type>;
    using Base = Const_DL_Iterator<DlNode>;
public:
    using Base::Node;
    using Base::NodePtr;
    using Base::iterator_category;
    using Base::value_type;
    using Base::reference;

    using this_type = DL_Iterator<DlNode>;

public:
    DL_Iterator() = default;
    DL_Iterator(const this_type & rhs) : m_ptr(rhs.m_ptr) { }

    reference operator*() const { return m_ptr->m_value; }
    NodePtr operator->() const { return m_ptr; }

    this_type& operator++() { m_ptr = m_ptr->m_next; return *this; }
    this_type operator++(int) { NodePtr tmp{ m_ptr }; m_ptr = m_ptr->m_next; return this_type(tmp); }

    bool operator==(const this_type& rhs) const { return m_ptr == rhs.m_ptr; }
    bool operator!=(const this_type& rhs) const { return m_ptr != rhs.m_ptr; }

protected:
    DL_Iterator(NodePtr p) : Base(p) { }
};

template<typename DlNode>
class Const_DL_Reverse_Iterator 
{
    friend class DoubleList<typename DlNode::value_type>;
public:
    using Node              = DlNode;
    using NodePtr           = typename DlNode::node_pointer_type;
	using iterator_category = std::forward_iterator_tag;
	using value_type		= typename DlNode::value_type;
    using reference         = value_type&;
    using this_type         = Const_DL_Reverse_Iterator<DlNode>;

public:
    Const_DL_Reverse_Iterator() = default;
    Const_DL_Reverse_Iterator(const this_type &rhs) : m_ptr(rhs.m_ptr) { }

	const reference operator*() const { return m_ptr->m_value; }
	const NodePtr operator->() const { return m_ptr; }

	this_type& operator++() { m_ptr = m_ptr->m_prev; return *this; }
    this_type operator++(int) { NodePtr tmp{ m_ptr }; m_ptr = m_ptr->m_prev; return this_type(tmp); }

	bool operator==(const this_type& rhs) const { return m_ptr == rhs.m_ptr; }
    bool operator!=(const this_type& rhs) const { return m_ptr != rhs.m_ptr; }

protected:
    Const_DL_Reverse_Iterator(NodePtr p) : m_ptr(p) { }
    inline NodePtr getPointer() { return m_ptr; }
protected:
    NodePtr         m_ptr{};
};

template<typename DlNode>
class DL_Reverse_Iterator : public Const_DL_Reverse_Iterator<DlNode>
{
    friend class DoubleList<typename DlNode::value_type>;
    using Base = Const_DL_Reverse_Iterator<DlNode>;
public:
    using Base::Node;
    using Base::NodePtr;
    using Base::iterator_category;
    using Base::value_type;
    using Base::reference;

    using this_type = DL_Reverse_Iterator<DlNode>;

public:
    DL_Reverse_Iterator() = default;
    DL_Reverse_Iterator(const this_type & rhs) : m_ptr(rhs.m_ptr) { }

    reference operator*() const { return m_ptr->m_value; }
    NodePtr operator->() const { return m_ptr; }

    this_type& operator++() { m_ptr = m_ptr->m_prev; return *this; }
    this_type operator++(int) { NodePtr tmp{ m_ptr }; m_ptr = m_ptr->m_prev; return this_type(tmp); }

    bool operator==(const this_type& rhs) const { return m_ptr == rhs.m_ptr; }
    bool operator!=(const this_type& rhs) const { return m_ptr != rhs.m_ptr; }

protected:
    DL_Reverse_Iterator(NodePtr p) : Base(p) { }
};

template<typename T>
class DoubleList
{
    using this_type         = DoubleList<T>;
    using Node              = _DoubleListNode<T, void*>;
    using NodePtr           = Node *;
public:
	using value_type				= T;
	using pointer					= T*;
	using const_pointer				= const T*;
	using reference					= value_type&;
	using const_reference			= const value_type&;
    using iterator				    = typename Node::iterator;
    using const_iterator			= typename Node::const_iterator;
    using reverse_iterator	        = typename Node::reverse_iterator;
    using const_reverse_iterator    = typename Node::const_reverse_iterator;
	using size_type					= size_t;
	using difference_type			= ptrdiff_t;

	static const size_type npos		= (size_type)-1;
	static const size_type kMaxSize = (size_type)-2;
public:
    // Member functions
    ~DoubleList();

    DoubleList() = default;
    explicit DoubleList(const size_type count, const value_type &value);
    explicit DoubleList(const size_type count);
    
    template<typename InputIterator>
    DoubleList(InputIterator first, InputIterator last);

    DoubleList(std::initializer_list<T> iList);

    DoubleList(const DoubleList &other);
    DoubleList(DoubleList &&other) noexcept;

    DoubleList& operator=(const DoubleList &other);
    DoubleList& operator=(DoubleList &&other) noexcept;
    DoubleList& operator=(std::initializer_list<T> iList);

    void assign(size_type count, const value_type& value);

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last);

    void assign(std::initializer_list<T> iList);

    // Element access
    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    // Iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    // Modifiers
    void clear() noexcept;

    iterator insert(iterator pos, const value_type& value);
    iterator insert(const_iterator pos, const value_type& value);
    iterator insert(const_iterator pos, value_type &&value);
    iterator insert(iterator pos, size_type count, const value_type& value);

    template<typename InputIterator>
    iterator insert(iterator pos, InputIterator first, InputIterator last);

    template<typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last);

    iterator insert(const_iterator pos, std::initializer_list<T> iList);

    template<typename ...Args>
    iterator emplace(const_iterator pos, Args&&... args);

    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);

    void push_back(const value_type& value);
    void push_back(value_type&& value);

    template<typename ...Args>
    reference emplace_back(Args&&... args);

    void pop_back();

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
    Node            m_postTail{};
    size_type       m_size{};
};

template<typename T>
inline DoubleList<T>::~DoubleList()
{
    clear();
}

template<typename T>
inline DoubleList<T>::DoubleList(const size_type count, const value_type& value)
{
    assign(count, value);
}

template<typename T>
inline DoubleList<T>::DoubleList(const size_type count)
{
    assign(count, value_type{});
}

template<typename T>
template<typename InputIterator>
inline DoubleList<T>::DoubleList(InputIterator first, InputIterator last)
{
    assign(first, last);
}

template<typename T>
inline DoubleList<T>::DoubleList(std::initializer_list<value_type> iList)
{
    assign(iList.begin(), iList.end());
}

template<typename T>
inline DoubleList<T>::DoubleList(const DoubleList<value_type>& other)
{
    assign(other.begin(), other.end());
}

template<typename T>
inline DoubleList<T>::DoubleList(DoubleList<value_type>&& other) noexcept
{
    swap(std::move(other));
}

template<typename T>
inline DoubleList<T>& DoubleList<T>::operator=(const DoubleList<value_type>& other)
{
    if (this != &other)
    {
        assign(other.begin(), other.end());
    }
    return *this;
}

template<typename T>
inline DoubleList<T>& DoubleList<T>::operator=(DoubleList<value_type>&& other) noexcept
{
    if (this != &other)
    {
        clear();
        swap(std::move(other));
    }
    return *this;
}

template<typename T>
inline DoubleList<T>& DoubleList<T>::operator=(std::initializer_list<value_type> iList)
{
    if (this != &other)
    {
        assign(iList.begin(), iList.end());
    }
    return *this;
}

template<typename T>
inline void DoubleList<T>::assign(size_type count, const value_type& value)
{
    if (count == 0)
    {
        return;
    }
    m_size = count;
    NodePtr p{ &m_preHead };
    while (count--)
    {
        createOrReuse(p, value);
    }
    m_postTail.m_prev = p;
    clear(p->m_next);
    p->m_next = &m_postTail;
}

template<typename T>
template<typename InputIterator>
inline void DoubleList<T>::assign(InputIterator first, InputIterator last)
{
    size_type count = 0;
    NodePtr p{ &m_preHead };
    for (; first != last; ++first)
    {
        createOrReuse(p, *first);
        count++;
    }
    m_size = count;
    m_postTail.m_prev = p;
    clear(p->m_next);
    p->m_next = &m_postTail;
}

template<typename T>
inline void DoubleList<T>::assign(std::initializer_list<value_type> iList)
{
    assign(iList.begin(), iList.end());
}

// Element access
template<typename T>
inline typename DoubleList<T>::reference DoubleList<T>::front()
{
    return m_preHead.m_next->m_value;
}

template<typename T>
inline typename DoubleList<T>::const_reference DoubleList<T>::front() const
{
    return m_preHead.m_next->m_value;
}

template<typename T>
inline typename DoubleList<T>::reference DoubleList<T>::back()
{
    return m_postTail.m_prev->m_value;
}

template<typename T>
inline typename DoubleList<T>::const_reference DoubleList<T>::back() const
{
    return m_postTail.m_prev->m_value;
}

// Iterators
template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::begin() noexcept
{
    return iterator(m_preHead.m_next);
}

template<typename T>
inline typename DoubleList<T>::const_iterator DoubleList<T>::begin() const noexcept
{
    return const_iterator(m_preHead..m_next);
}

template<typename T>
inline typename DoubleList<T>::const_iterator DoubleList<T>::cbegin() const noexcept
{
    return begin();
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::end() noexcept
{
    return iterator(&m_postTail);
}

template<typename T>
inline typename DoubleList<T>::const_iterator DoubleList<T>::end() const noexcept
{
    return const_iterator(&m_postTail);
}

template<typename T>
inline typename DoubleList<T>::const_iterator DoubleList<T>::cend() const noexcept
{
    return end();
}

template<typename T>
inline typename DoubleList<T>::reverse_iterator DoubleList<T>::rbegin() noexcept
{
    return reverse_iterator(m_postTail.m_prev);
}

template<typename T>
inline typename DoubleList<T>::const_reverse_iterator DoubleList<T>::rbegin() const noexcept
{
    return const_reverse_iterator(m_postTail.m_prev);
}

template<typename T>
inline typename DoubleList<T>::const_reverse_iterator DoubleList<T>::crbegin() const noexcept
{
    return rbegin();
}

template<typename T>
inline typename DoubleList<T>::reverse_iterator DoubleList<T>::rend() noexcept
{
    return reverse_iterator(&m_preHead);
}

template<typename T>
inline typename DoubleList<T>::const_reverse_iterator DoubleList<T>::rend() const noexcept
{
    return const_reverse_iterator(&m_preHead);
}

template<typename T>
inline typename DoubleList<T>::const_reverse_iterator DoubleList<T>::crend() const noexcept
{
    return rend();
}

// Capacity
template<typename T>
inline bool DoubleList<T>::empty() const noexcept
{
    return m_size == 0;
}

template<typename T>
inline typename DoubleList<T>::size_type DoubleList<T>::size() const noexcept
{
    return m_size;
}

template<typename T>
inline typename DoubleList<T>::size_type DoubleList<T>::max_size() const noexcept
{
    return kMaxSize;
}

// Modifiers
template<typename T>
inline void DoubleList<T>::clear() noexcept
{
    m_postTail.m_prev = nullptr;
    clear(m_preHead.m_next);
    m_preHead.m_next = nullptr;
    m_size = 0;
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::insert(iterator pos, const value_type& value)
{
    return insert(pos, 1, value);
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::insert(const_iterator pos, const value_type& value)
{
    return insert(pos, 1, value);
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::insert(const_iterator pos, value_type&& value)
{
    iterator it = findPosition(pos);
    NodePtr next = it->getPointer();
    NodePtr ptr = (--it)->getPointer();
    ptr->m_next = nullptr;
    createOrReuse(ptr, std::move(value));
    ptr->m_next = next;
    next->m_prev = ptr;

    m_size++;
    return iterator(next);
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::insert(iterator pos, size_type count, const value_type& value)
{
    iterator it = findPosition(pos);
    NodePtr next = it->getPointer();
    NodePtr ptr = (--it)->getPointer();
    ptr->m_next = nullptr;
    while (count--)
    {
        createOrReuse(ptr, value);
        m_size++;
    }
    ptr->m_next = next;
    next->m_prev = ptr;
    return iterator(next);
}

template<typename T>
template<typename InputIterator>
inline typename DoubleList<T>::iterator DoubleList<T>::insert(iterator pos, InputIterator first, InputIterator last)
{
    return insert(const_iterator(pos), first, last);
}

template<typename T>
template<typename InputIterator>
inline typename DoubleList<T>::iterator DoubleList<T>::insert(const_iterator pos, InputIterator first, InputIterator last)
{
    iterator it = findPosition(pos);
    NodePtr next = it->getPointer();
    NodePtr ptr = (--it)->getPointer();
    ptr->m_next = nullptr;
    for (; first != last; ++first)
    {
        createOrReuse(ptr, *first);
        m_size++;
    }
    ptr->m_next = next;
    next->m_prev = ptr;
    return iterator(next);
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::insert(const_iterator pos, std::initializer_list<T> iList)
{
    return insert_after(pos, iList.begin(), iList.end());
}

template<typename T>
template<typename ...Args>
inline typename DoubleList<T>::iterator DoubleList<T>::emplace(const_iterator pos, Args&&... args)
{
    return insert_after(before_begin(), std::move(value_type(std::forward<Args>(args)...)));
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::erase(iterator pos)
{
    return erase(const_iterator(pos));
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::erase(const_iterator pos)
{
    iterator it = findPosition(pos);
    if (it != end())
    {
        NodePtr nodeToDelete = it->getPointer();
        it++;
        nodeToDelete->m_prev->m_next = nodeToDelete->m_next;
        nodeToDelete->m_next->prev = nodeToDelete->m_prev;
        removeNode(nodeToDelete);
        m_size--;
    }
    return it;
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::erase(iterator first, iterator last)
{
    return erase(const_iterator(first), const_iterator(last));
}

template<typename T>
inline typename DoubleList<T>::iterator DoubleList<T>::erase(const_iterator first, const_iterator last)
{
    iterator ret;
    while (first != last)
    {
        ret = erase(first++);
    }
    return ret;
}

template<typename T>
inline void DoubleList<T>::push_back(const value_type& value)
{
    insert(end(), value);
}

template<typename T>
inline void DoubleList<T>::push_back(value_type&& value)
{
    insert(end(), std::move(value));
}

template<typename T>
template<typename ...Args>
inline typename DoubleList<T>::reference DoubleList<T>::emplace_back(Args&&... args)
{
    return emplace(end(), std::forward<Args>(args)...);
}

template<typename T>
inline void DoubleList<T>::pop_back()
{
    erase(--end());
}

template<typename T>
inline void DoubleList<T>::push_front(const value_type& value)
{
    insert(begin(), value);
}

template<typename T>
inline void DoubleList<T>::push_front(value_type&& value)
{
    insert(begin(), std::move(value));
}

template<typename T>
template<typename ...Args>
inline typename DoubleList<T>::reference DoubleList<T>::emplace_front(Args&&... args)
{
    return emplace_after(before_begin(), std::move(value_type(std::forward<Args>(args)...)));
}

template<typename T>
inline void DoubleList<T>::pop_front()
{
    NodePtr nodeToDelete = m_PreHead.m_next;
    m_PreHead.m_next = nodeToDelete->m_next;
    removeNode(nodeToDelete);
}

template<typename T>
inline void DoubleList<T>::resize(const size_type count)
{
    resize(count, value_type{});
}

template<typename T>
inline void DoubleList<T>::resize(size_type count, const value_type& value)
{
    assign(count, value);
}


template<typename T>
inline void DoubleList<T>::swap(this_type& other)
{
    m_preHead = std::exchange(other.m_preHead, Node{});
    m_postTail = std::exchange(other.m_postTail, Node{});
    m_size = std::exchange(other.m_size, {});
}

// Operations
template<typename T>
inline void DoubleList<T>::merge(this_type& other)
{
    merge(other, std::less<>);
}

template<typename T>
inline void DoubleList<T>::merge(this_type&& other)
{
    merge(std::move(other), std::less<>);
}

template<typename T>
template<typename Compare>
inline void DoubleList<T>::merge(this_type& other, Compare comp)
{

}

template<typename T>
template<typename Compare>
inline void DoubleList<T>::merge(this_type&& other, Compare comp)
{

}

template<typename T>
inline void DoubleList<T>::splice_after(const_iterator pos, this_type& other)
{

}

template<typename T>
inline void DoubleList<T>::splice_after(const_iterator pos, this_type&& other)
{

}

template<typename T>
inline void DoubleList<T>::splice_after(const_iterator pos, this_type& other, const_iterator it)
{

}

template<typename T>
inline void DoubleList<T>::splice_after(const_iterator pos, this_type&& other, const_iterator it)
{

}

template<typename T>
inline void DoubleList<T>::splice_after(const_iterator pos, this_type& other, const_iterator first, const_iterator last)
{

}

template<typename T>
inline void DoubleList<T>::splice_after(const_iterator pos, this_type&& other, const_iterator first, const_iterator last)
{

}

template<typename T>
inline typename DoubleList<T>::size_type DoubleList<T>::remove(const value_type& value)
{
    return remove_if(std::bind(std::equal_to, _1, value));
}

template<typename T>
template<typename UnaryPredicate>
inline typename DoubleList<T>::size_type DoubleList<T>::remove_if(UnaryPredicate p)
{
    size_type count = 0;
    bool bStop{ false };
    while (!bStop)
    {
        NodePtr curr{m_PreHead.m_next};
        NodePtr prev{&m_PreHead};
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
inline void DoubleList<T>::reverse() noexcept
{
    NodePtr prev{};
    NodePtr next{};
    NodePtr curr{m_PreHead.m_next};
    
    while (curr)
    {
        next = curr->m_next;
        curr->m_next = prev;
        prev = curr;
        curr = next;
    }
    m_PreHead.m_next = prev;
}

template<typename T>
inline typename DoubleList<T>::size_type DoubleList<T>::unique()
{
    unique(std::equal_to<>);
}

template<typename T>
template<typename BinaryPredicate>
inline typename DoubleList<T>::size_type DoubleList<T>::unique(BinaryPredicate p)
{

}

template<typename T>
inline void DoubleList<T>::sort()
{
    sort(std::less<>);
}

template<typename T>
template<typename Compare>
inline void DoubleList<T>::sort(Compare comp)
{

}

// Private
template<typename T>
inline void DoubleList<T>::clear(NodePtr& head)
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
inline void DoubleList<T>::removeNode(NodePtr node) noexcept
{
    if (node == &m_preHead || node == &m_postTail)
    {
        return;
    }
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
inline typename DoubleList<T>::iterator DoubleList<T>::findPosition(const_iterator pos) const
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
inline void DoubleList<T>::createOrReuse(NodePtr& ptr, const value_type& value)
{
    if (ptr->m_next)
    {
        ptr = ptr->m_next;
        ptr->m_value = value;
    }
    else
    {
        ptr->m_next = Node::createNode(value, ptr, nullptr);
        ptr = ptr->m_next;
    }
}

template<typename T>
inline void DoubleList<T>::createOrReuse(NodePtr& ptr, value_type&& value)
{
    if (ptr->m_next)
    {
        ptr = ptr->m_next;
        ptr->m_value = std::move(value);
    }
    else
    {
        ptr->m_next = Node::createNode(std::move(value), ptr, nullptr);
        ptr = ptr->m_next;
    }
}

void test_DoubleList_1()
{
    const char* testName = "Double ended List.";
    ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n\n");

    DoubleList<int> sl{ 1, 2, 3, 4, 5, 6 };

    for (DoubleList<int>::iterator it = sl.begin(); it != sl.end(); ++it)
    {
        ns_Util::Logger::LOG_MSG(*it, ", ");
    }

    ns_Util::Logger::LOG_MSG("\n\n");
}

void test_DoubleList_2()
{
    const char* testName = "Double ended List.";
    ns_Util::Logger::LOG_MSG("Executing Test 2 : ", testName, "\n\n");

    ns_Util::Logger::LOG_MSG("\n\n");
}

void test_DoubleList_3()
{
    const char* testName = "Double ended List.";
    ns_Util::Logger::LOG_MSG("Executing Test 3 : ", testName, "\n\n");

    ns_Util::Logger::LOG_MSG("\n\n");
}

void test_DoubleList()
{
    LOG_ENTRY;
    test_DoubleList_1();
    test_DoubleList_2();
    test_DoubleList_3();
    LOG_EXIT;
    ns_Util::Logger::LOG_MSG("#####################################\n");
}

}   // namespace nsCpp_DS
#endif	// __SINGLE_LIST_H__
