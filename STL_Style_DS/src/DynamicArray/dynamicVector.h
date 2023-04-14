#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <iterator>

#include "Common/logger.h"
#include "Common/helper.h"
#include "Common/testClass.h"
#include "Common/allocator_traits.h"

namespace nsCpp_DS {
template<typename T, typename Alloc>
class DynamicVector;

template <typename _Container>
struct IterTemplate
{
	using value_type      = typename _Container::value_type;
    using size_type       = typename _Container::size_type;
    using difference_type = typename _Container::difference_type;
    using pointer         = typename _Container::pointer;
    using reference       = typename _Container::reference;
};

template <typename IterVal>
class DynamicVector_Const_Iterator
{
	template <typename T, typename Alloc>
	friend class DynamicVector;

	using this_type			= DynamicVector_Const_Iterator<IterVal>;

public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type		= typename IterVal::value_type;
	using difference_type	= typename IterVal::difference_type;
	using pointer			= const typename IterVal::pointer;
	using reference			= const typename IterVal::reference;

public:
	~DynamicVector_Const_Iterator() = default;
	INLINE_OR_CONSTEXPR DynamicVector_Const_Iterator() noexcept = default;
	INLINE_OR_CONSTEXPR DynamicVector_Const_Iterator(const this_type & other) noexcept : m_ptr(other.m_ptr) { }

	NODISCARD_CONSTEXPR DynamicVector_Const_Iterator& operator=(const DynamicVector_Const_Iterator& other) noexcept = default;

	NODISCARD_CONSTEXPR reference operator*() const noexcept { return *m_ptr; }
	NODISCARD_CONSTEXPR pointer operator->() const
	{
		if constexpr (std::is_pointer_v<m_ptr>)
		{
			return m_ptr;
		}
		return m_ptr.operator->();
	}

	INLINE_OR_CONSTEXPR this_type& operator++() noexcept { ++m_ptr; return *this; }
	INLINE_OR_CONSTEXPR this_type operator++(int) noexcept { this_type tmp = *this; ++(*this); return tmp; }

	INLINE_OR_CONSTEXPR this_type& operator--() noexcept { --m_ptr; return *this; }
	INLINE_OR_CONSTEXPR this_type operator--(int) noexcept { this_type tmp = *this; --(*this); return tmp; }

	NODISCARD_CONSTEXPR this_type operator+(const difference_type offset) const noexcept { return this_type tmp(*this); tmp += offset; return tmp; }
	INLINE_OR_CONSTEXPR this_type& operator+=(const difference_type offset) noexcept { m_ptr += offset; return *this; }

	NODISCARD_CONSTEXPR this_type operator-(const difference_type offset) const noexcept { this_type tmp(*this); tmp -= offset; return tmp; }
	INLINE_OR_CONSTEXPR this_type& operator-=(const difference_type offset) noexcept { return *this += -offset; }

	NODISCARD_CONSTEXPR difference_type operator-(const this_type& other) const noexcept { return m_ptr - other.m_ptr; }

	NODISCARD_CONSTEXPR reference operator[](const difference_type offset) const noexcept { return *(*m_ptr + offset); }

	NODISCARD_CONSTEXPR bool operator==(const this_type& rhs) const noexcept { return m_ptr == rhs.m_ptr; }
	NODISCARD_CONSTEXPR bool operator!=(const this_type& rhs) const noexcept { return m_ptr != rhs.m_ptr; }
	NODISCARD_CONSTEXPR bool operator<(const this_type& rhs) const noexcept { return m_ptr < rhs.m_ptr; }
	NODISCARD_CONSTEXPR bool operator>(const this_type& rhs) const noexcept { return m_ptr > rhs.m_ptr; }
	NODISCARD_CONSTEXPR bool operator<=(const this_type& rhs) const noexcept { return m_ptr <= rhs.m_ptr; }
	NODISCARD_CONSTEXPR bool operator>=(const this_type& rhs) const noexcept { return m_ptr >= rhs.m_ptr; }

	NODISCARD_CONSTEXPR friend this_type operator+(const difference_type offset, const this_type& other) { return other += offset; }

protected:
	INLINE_OR_CONSTEXPR explicit DynamicVector_Const_Iterator(pointer p) noexcept : m_ptr(p) { }

protected:
	typename IterVal::pointer			m_ptr{};
};

template <typename IterVal>
class DynamicVector_Iterator : public DynamicVector_Const_Iterator<IterVal>
{
	template <typename T, typename Alloc>
	friend class DynamicVector;

	using Base				= DynamicVector_Const_Iterator<IterVal>;
	using this_type			= DynamicVector_Iterator<IterVal>;

public:
	using Base::iterator_category;
	using Base::value_type;
	using Base::difference_type;
	using pointer			= typename IterVal::pointer;
	using reference			= typename IterVal::reference;

public:
	~DynamicVector_Iterator() = default;
	INLINE_OR_CONSTEXPR DynamicVector_Iterator() noexcept = default;
	INLINE_OR_CONSTEXPR DynamicVector_Iterator(const this_type& rhs) noexcept : Base(rhs) { }

	NODISCARD_CONSTEXPR DynamicVector_Iterator& operator=(const DynamicVector_Iterator& other) noexcept = default;

	NODISCARD_CONSTEXPR reference operator*() const noexcept { return const_cast<reference>(Base::operator*()); }
	NODISCARD_CONSTEXPR pointer operator->() const noexcept { return const_cast<pointer>(Base::operator->()); }

	INLINE_OR_CONSTEXPR this_type& operator++() noexcept { Base::operator++(); return *this; }
	INLINE_OR_CONSTEXPR this_type operator++(int) noexcept { this_type tmp{ *this }; Base::operator++(); return tmp; }

	INLINE_OR_CONSTEXPR this_type& operator--() noexcept { Base::operator--(); return *this; }
	INLINE_OR_CONSTEXPR this_type operator--(int) noexcept { this_type tmp{ *this }; Base::operator--(); return tmp; }

	NODISCARD_CONSTEXPR this_type operator+(const difference_type offset) const noexcept { this_type tmp{ *this }; tmp += offset; return tmp; }
	INLINE_OR_CONSTEXPR this_type& operator+=(const difference_type offset) noexcept { Base::operator+=(offset); return *this; }

	NODISCARD_CONSTEXPR this_type operator-(const difference_type offset) const noexcept { this_type tmp{ *this }; tmp -= offset; return tmp; }
	INLINE_OR_CONSTEXPR this_type& operator-=(const difference_type offset) noexcept { Base::operator-=(offset); return *this; }

	NODISCARD_CONSTEXPR difference_type operator-(const this_type& other) const noexcept { return Base::operator-(other); }

	NODISCARD_CONSTEXPR reference operator[](const difference_type offset) noexcept { return const_cast<reference>(Base::operator[](offset)); }

	NODISCARD_CONSTEXPR  friend this_type operator+(const difference_type offset, const this_type& other) { return other += offset; }
protected:
	INLINE_OR_CONSTEXPR explicit DynamicVector_Iterator(pointer p) noexcept : Base(p) { }
};

template<typename Iter>
class Reverse_DynamicVector_Iterator
{
	template <typename T, typename Alloc>
	friend class DynamicVector;

	using this_type			= Reverse_DynamicVector_Iterator<Iter>;
public:
	using iterator_category = typename ns_Util::Iter_cat_t<Iter>;
	using value_type		= typename std::iterator_traits<Iter>::value_type;
	using difference_type	= typename std::iterator_traits<Iter>::difference_type;
	using pointer			= typename std::iterator_traits<Iter>::pointer;
	using reference			= typename std::iterator_traits<Iter>::reference;

public:
	~Reverse_DynamicVector_Iterator() = default;
	INLINE_OR_CONSTEXPR Reverse_DynamicVector_Iterator() noexcept = default;

	INLINE_OR_CONSTEXPR Reverse_DynamicVector_Iterator(const Reverse_DynamicVector_Iterator &other) noexcept : m_iterator(other.m_iterator) { }

	INLINE_OR_CONSTEXPR Reverse_DynamicVector_Iterator& operator=(const Reverse_DynamicVector_Iterator& other) noexcept = default;

	NODISCARD_CONSTEXPR reference operator*() const noexcept { Iter tmp(m_iterator); return *--tmp; }
	NODISCARD_CONSTEXPR pointer operator->() const noexcept
	{
		Iter tmp(m_iterator);
		--tmp;
		if constexpr (std::is_pointer_v<Iter>)
		{
			return tmp;
		}
		return tmp.operator->();
	}

	INLINE_OR_CONSTEXPR this_type& operator++() noexcept { --m_iterator; return *this; }
	INLINE_OR_CONSTEXPR this_type operator++(int) noexcept { this_type tmp{ *this }; --m_iterator; return tmp; }

	INLINE_OR_CONSTEXPR this_type& operator--() noexcept { ++m_iterator; return *this; }
	INLINE_OR_CONSTEXPR this_type operator--(int) noexcept { this_type tmp{ *this }; ++m_iterator; return tmp; }

	NODISCARD_CONSTEXPR this_type operator+(const difference_type offset) const noexcept { return this_type(m_iterator - offset); }
	INLINE_OR_CONSTEXPR this_type& operator+=(const difference_type offset) noexcept { m_iterator -= offset; return *this; }

	NODISCARD_CONSTEXPR this_type operator-(const difference_type offset) const noexcept { return this_type(m_iterator + offset); }
	INLINE_OR_CONSTEXPR this_type& operator-=(const difference_type offset) noexcept { m_iterator += offset; return *this; }

	NODISCARD_CONSTEXPR reference operator[](const difference_type offset) noexcept { return m_iterator[static_cast<difference_type>(-offset - 1)]; }

	NODISCARD_CONSTEXPR bool operator==(const this_type& rhs) const noexcept { return m_iterator == rhs.m_iterator; }
	NODISCARD_CONSTEXPR bool operator!=(const this_type& rhs) const noexcept { return m_iterator != rhs.m_iterator; }
	NODISCARD_CONSTEXPR bool operator<(const this_type& rhs) const noexcept { return m_iterator > rhs.m_iterator; }
	NODISCARD_CONSTEXPR bool operator>(const this_type& rhs) const noexcept { return m_iterator > rhs.m_iterator; }
	NODISCARD_CONSTEXPR bool operator<=(const this_type& rhs) const noexcept { return m_iterator >= rhs.m_iterator; }
	NODISCARD_CONSTEXPR bool operator>=(const this_type& rhs) const noexcept { return m_iterator <= rhs.m_iterator; }

	NODISCARD_CONSTEXPR friend difference_type operator-(const this_type& lhs, const this_type& rhs) { return rhs.m_iterator - lhs.m_iterator; }
	NODISCARD_CONSTEXPR friend this_type operator+(const difference_type offset, const this_type& other) { return other + offset; }
	
protected:
	INLINE_OR_CONSTEXPR explicit Reverse_DynamicVector_Iterator(Iter rhs) noexcept : m_iterator(std::move(rhs)) { }
protected:
	Iter	m_iterator{};
};

/*
template <class _BidIt1, class _BidIt2>
_NODISCARD _CONSTEXPR17 auto operator-(const reverse_iterator<_BidIt1>& _Left, const reverse_iterator<_BidIt2>& _Right)
-> decltype(_Right._Get_current() - _Left._Get_current()) {
	return _Right._Get_current() - _Left._Get_current();
}

template <class _BidIt>
_NODISCARD _CONSTEXPR17 reverse_iterator<_BidIt> operator+(
	typename reverse_iterator<_BidIt>::difference_type _Off, const reverse_iterator<_BidIt>& _Right) {
	return _Right + _Off;
}
*/

template<typename T, typename Alloc = ns_Util::CustomAllocator<T>>
//template<typename T, typename Alloc = std::allocator<T>>
class DynamicVector
{
	using this_type					= DynamicVector<T>;

	using AllocType					= ns_Util::Rebind_alloc_t<Alloc, T>;
	using AllocType_traits			= ns_Util::CustomAllocator_traits<AllocType>;
	//using AllocType				= std::_Rebind_alloc_t<Alloc, T>;
	//using AllocType_traits		= std::allocator_traits<AllocType>;

public:
	static_assert(!_ENFORCE_MATCHING_ALLOCATORS || std::is_same_v<T, typename Alloc::value_type>,
		_MISMATCHED_ALLOCATOR_MESSAGE("vector<T, Allocator>", "T"));

public:
	using value_type				= T;
	using allocator_type			= Alloc;
	using pointer					= typename AllocType_traits::pointer;
	using const_pointer				= typename AllocType_traits::const_pointer;
	using reference					= T&;
	using const_reference			= const T&;
	using size_type					= typename AllocType_traits::size_type;
	using difference_type			= typename AllocType_traits::difference_type;

private:
	using IterType = IterTemplate<DynamicVector<T, Alloc>>;

	using iterator					= DynamicVector_Iterator<IterType>;
	using const_iterator			= DynamicVector_Const_Iterator<IterType>;
	using reverse_iterator			= Reverse_DynamicVector_Iterator<iterator>;
	using const_reverse_iterator	= Reverse_DynamicVector_Iterator<const_iterator>;

	static const size_type npos		= (size_type)-1;
	static const size_type kMaxSize = (size_type)-2;

public:
	~DynamicVector() noexcept;

	INLINE_OR_CONSTEXPR DynamicVector() noexcept(std::is_nothrow_default_constructible_v<AllocType>) = default;

	INLINE_OR_CONSTEXPR explicit DynamicVector(const Alloc& allocator) noexcept;
	INLINE_OR_CONSTEXPR explicit DynamicVector(const size_type count, const Alloc& allocator = Alloc());
	
	INLINE_OR_CONSTEXPR DynamicVector(const size_type count, const value_type& value, const Alloc& allocator = Alloc());
	
	template <typename InputIterator, std::enable_if_t<ns_Util::Is_iterator_v<InputIterator>, int> = 0>
	INLINE_OR_CONSTEXPR DynamicVector(InputIterator first, InputIterator last, const Alloc& allocator = Alloc());

	INLINE_OR_CONSTEXPR DynamicVector(const std::initializer_list<value_type> iList, const Alloc& allocator = Alloc());

	INLINE_OR_CONSTEXPR DynamicVector(const this_type &other);
	INLINE_OR_CONSTEXPR DynamicVector(const this_type &other, const Alloc &allocator);
	INLINE_OR_CONSTEXPR DynamicVector(this_type &&other) noexcept;
	INLINE_OR_CONSTEXPR DynamicVector(this_type &&other, const Alloc& allocator) noexcept;

	INLINE_OR_CONSTEXPR this_type& operator=(const std::initializer_list<value_type> iList);
	INLINE_OR_CONSTEXPR this_type& operator=(const this_type &other);
	INLINE_OR_CONSTEXPR this_type& operator=(this_type &&other) noexcept;

	INLINE_OR_CONSTEXPR void				assign(const size_type count, const value_type& value);
	
	template<typename InputIterator>
	INLINE_OR_CONSTEXPR void				assign(InputIterator first, InputIterator last);
	
	INLINE_OR_CONSTEXPR void				assign(std::initializer_list<value_type> ilist);

	// Element access
	NODISCARD_CONSTEXPR reference			at(const size_type pos);
	NODISCARD_CONSTEXPR const_reference		at(const size_type pos) const;

	NODISCARD_CONSTEXPR reference			operator[](const size_type pos);
	NODISCARD_CONSTEXPR const_reference		operator[](const size_type pos) const;

	NODISCARD_CONSTEXPR reference			front();
	NODISCARD_CONSTEXPR const_reference		front() const;

	NODISCARD_CONSTEXPR reference			back();
	NODISCARD_CONSTEXPR const_reference		back() const;

	NODISCARD_CONSTEXPR pointer				data();
	NODISCARD_CONSTEXPR const_pointer		data() const;

	// Iterators
	NODISCARD_CONSTEXPR iterator								begin() noexcept;
	NODISCARD_CONSTEXPR const_iterator							begin() const noexcept;

	NODISCARD_CONSTEXPR iterator								end() noexcept;
	NODISCARD_CONSTEXPR const_iterator							end() const noexcept;

	NODISCARD_CONSTEXPR reverse_iterator						rbegin() noexcept;
	NODISCARD_CONSTEXPR const_reverse_iterator					rbegin() const noexcept;

	NODISCARD_CONSTEXPR reverse_iterator						rend() noexcept;
	NODISCARD_CONSTEXPR const_reverse_iterator					rend() const noexcept;

	NODISCARD_CONSTEXPR const_iterator							cbegin() const noexcept;
	NODISCARD_CONSTEXPR const_iterator							cend() const noexcept;

	NODISCARD_CONSTEXPR const_reverse_iterator					crbegin() const noexcept;
	NODISCARD_CONSTEXPR const_reverse_iterator					crend() const noexcept;

	// Capacity
	NODISCARD_CONSTEXPR bool				empty() const noexcept;
	NODISCARD_CONSTEXPR size_type			size() const noexcept;
	NODISCARD_CONSTEXPR size_type			max_size() const noexcept;
	INLINE_OR_CONSTEXPR void				reserve(const size_type newCapacity);
	NODISCARD_CONSTEXPR size_type			capacity() const noexcept;
	INLINE_OR_CONSTEXPR void				shrink_to_fit();

	// Modifiers
	INLINE_OR_CONSTEXPR void				clear();

	INLINE_OR_CONSTEXPR iterator			insert(const_iterator pos, const value_type& value);
	INLINE_OR_CONSTEXPR iterator			insert(const_iterator pos, value_type&& value);
	INLINE_OR_CONSTEXPR iterator			insert(const_iterator pos, const size_type count, const value_type& value);

	template<typename InputIterator>
	INLINE_OR_CONSTEXPR iterator			insert(iterator pos, InputIterator first, InputIterator last);
	
	template<typename InputIterator>
	INLINE_OR_CONSTEXPR iterator			insert(const_iterator pos, InputIterator first, InputIterator last);
	
	INLINE_OR_CONSTEXPR iterator			insert(const_iterator pos, std::initializer_list<value_type> ilist);

	template<typename... Args>
	INLINE_OR_CONSTEXPR iterator			emplace(const_iterator pos, Args&&... args);

	INLINE_OR_CONSTEXPR iterator			erase(iterator pos);
	INLINE_OR_CONSTEXPR iterator			erase(const_iterator pos);
	INLINE_OR_CONSTEXPR iterator			erase(iterator first, iterator last);
	INLINE_OR_CONSTEXPR iterator			erase(const_iterator first, const_iterator last);

	INLINE_OR_CONSTEXPR void				push_back(const value_type& value);
	INLINE_OR_CONSTEXPR void				push_back(value_type&& value);

	template<typename... Args>
	INLINE_OR_CONSTEXPR reference			emplace_back(Args&&... args);

	INLINE_OR_CONSTEXPR void				pop_back();

	INLINE_OR_CONSTEXPR void				resize(const size_type newSize, const value_type value = value_type());
	INLINE_OR_CONSTEXPR void				resize(const size_type newSize, const value_type& value);

	INLINE_OR_CONSTEXPR void				swap(this_type& other) noexcept;
private:
	INLINE_OR_CONSTEXPR void				InsertAt(const size_type pos, value_type &&value);
	INLINE_OR_CONSTEXPR void				InsertAt(const size_type pos, const size_type count, const value_type &value);

	template<typename InputIterator>
	INLINE_OR_CONSTEXPR void				InsertAt(const size_type pos, InputIterator first, InputIterator last);

	INLINE_OR_CONSTEXPR iterator			RemoveAt(const_iterator pos);
	INLINE_OR_CONSTEXPR iterator			RemoveAt(const_iterator first, const_iterator last);
	NODISCARD_CONSTEXPR pointer				DoAllocate(const size_type newSize);
	INLINE_OR_CONSTEXPR void				DoDestroy(pointer startMarker, pointer endMarker);
	INLINE_OR_CONSTEXPR void				DoDestroy(pointer pos);
	INLINE_OR_CONSTEXPR void				DoConstruct(pointer pos, const value_type& value);
	INLINE_OR_CONSTEXPR void				DoConstruct(pointer first, size_type count, const value_type& value);
	INLINE_OR_CONSTEXPR void				DoFree(pointer startMarker, pointer endMarker);
	INLINE_OR_CONSTEXPR size_type			CalculateNewCapacity(const size_type newSize);
	INLINE_OR_CONSTEXPR void				Reallocate(const size_type newSize, const value_type &value);
	INLINE_OR_CONSTEXPR void				Reallocate(const size_type newSize);
	INLINE_OR_CONSTEXPR void				Reallocate(const size_type newSize, const size_type leaveEmptyPos, const size_type leaveEmptyCount);
	INLINE_OR_CONSTEXPR void				ReallocateExactly(const size_type newSize);
	INLINE_OR_CONSTEXPR void				CopyOrMove(iterator Infirst, iterator Inlast, pointer outFirst, const size_type leaveEmptyPos, const size_type leaveEmptyCount);
	INLINE_OR_CONSTEXPR void				CopyOrMove(iterator Infirst, iterator Inlast, iterator outFirst, const size_type leaveEmptyPos, const size_type leaveEmptyCount);

	NODISCARD_CONSTEXPR bool				ValidateIterator(const_iterator it, bool includeEndIterator) const;

	template<typename InputIterator>
	NODISCARD_CONSTEXPR size_type			ElementCount(InputIterator first, InputIterator last) const;
	INLINE_OR_CONSTEXPR void				Tidy() noexcept;	// Free all storage
private:
	NO_RETURN static void					LengthError();
	NO_RETURN static void					RangeError();

private:
	pointer						m_first{};
	pointer						m_size{};		// For size
	pointer						m_end{};		// For capacity
	AllocType					m_allocator{};
};

template<typename T, typename Alloc>
DynamicVector<T, Alloc>::~DynamicVector() noexcept
{
	Tidy();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(const Alloc& allocator) noexcept
	: m_allocator(allocator)
{
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(const size_type count, const Alloc& allocator)
	:DynamicVector(allocator)
{
	m_first = DoAllocate(count);
	std::fill_n(m_first, count, value_type{});
	m_size = m_end = m_first + count;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(const size_type count, const value_type& value, const Alloc& allocator)
	:DynamicVector(count, allocator)
{
	assign(n, value);
}

template<typename T, typename Alloc>
template <typename InputIterator, std::enable_if_t<ns_Util::Is_iterator_v<InputIterator>, int>>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(InputIterator first, InputIterator last, const Alloc& allocator)
	:DynamicVector(allocator)
{
	assign(first, last);
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(const std::initializer_list<value_type> iList, const Alloc& allocator)
	: DynamicVector(iList.begin(), iList.end(), allocator)
{
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(const this_type& other)
	:DynamicVector(other, Alloc())
{
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(const this_type& other, const Alloc& allocator)
	:DynamicVector(other.capacity())
{
	std::copy(other.begin(), other.end(), begin());
	m_size = m_first + other.size();
	m_end = m_first + other.capacity();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(this_type&& other) noexcept
	: DynamicVector(std::move(other), Alloc())
{
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR DynamicVector<T, Alloc>::DynamicVector(this_type&& other, const Alloc& allocator) noexcept
{
	m_first = std::exchange(other.m_first, nullptr);
	m_size = std::exchange(other.m_size, nullptr);
	m_end = std::exchange(other.m_end, nullptr);
	m_allocator = allocator;
	return *this;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::this_type& DynamicVector<T, Alloc>::operator=(const std::initializer_list<value_type> iList)
{
	if (this != &other)
	{
		DoDestroy(m_first, m_end);
		assign(iList);
	}
	return *this;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::this_type& DynamicVector<T, Alloc>::operator=(const this_type& other)
{
	if (this != &other)
	{
		assign(other.begin(), other.end());
	}
	return *this;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::this_type& DynamicVector<T, Alloc>::operator=(this_type&& other) noexcept
{
	if (this != &other)
	{
		Tidy();
		m_first = std::exchange(other.m_first, nullptr);
		m_size = std::exchange(other.m_last, nullptr);
		m_end = std::exchange(other.m_end, nullptr);
		m_allocator = std::exchange(other.m_allocator, {});
	}
	return *this;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::assign(const size_type count, const value_type& value)
{
	if (count > capacity())
	{
		Reallocate(count, value);
		return;
	}
	else
	{
		DoDestroy(m_first, m_size);
	}
	std::fill_n(m_first, count, value);
	m_size = m_first + count;
}

template<typename T, typename Alloc>
template<typename InputIterator>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::assign(InputIterator first, InputIterator last)
{
	const size_type count = ElementCount(first, last);
	if (count > capacity())
	{
		Reallocate(count);
	}
	else
	{
		DoDestroy(m_first, m_size);
	}

	for (iterator it = begin(); first != last; ++it, ++first)
	{
		*it = std::move(*first);
	}
	m_size = m_first + count;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::assign(const std::initializer_list<value_type> ilist)
{
	if (ilist.size() > capacity())
	{
		Reallocate(ilist.size());
	}
	else
	{
		DoDestroy(m_first, m_size);
	}
	std::copy(ilist.begin(), ilist.end(), m_First);
	m_size = m_first + ilist.size();
}

// Element access
template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::reference DynamicVector<T, Alloc>::at(const size_type pos)
{
	if (size() <= pos)
	{
		RangeError();
	}
	return m_first[pos];
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_reference DynamicVector<T, Alloc>::at(const size_type pos) const
{
	if (size() <= pos)
	{
		RangeError();
	}
	return m_first[pos];
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::reference DynamicVector<T, Alloc>::operator[](const size_type pos)
{
	return m_first[pos];
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_reference DynamicVector<T, Alloc>::operator[](const size_type pos) const
{
	return m_first[pos];
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::reference DynamicVector<T, Alloc>::front()
{
	return m_first[0];
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_reference DynamicVector<T, Alloc>::front() const
{
	return m_first[0];
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::reference DynamicVector<T, Alloc>::back()
{
	return m_size[-1];
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_reference DynamicVector<T, Alloc>::back() const
{
	return m_size[-1];
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::pointer DynamicVector<T, Alloc>::data()
{
	return m_first;
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_pointer DynamicVector<T, Alloc>::data() const
{
	return m_first;
}

// Iterators
template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::begin() noexcept
{
	return iterator(m_first);
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_iterator DynamicVector<T, Alloc>::begin() const noexcept
{
	return const_iterator(m_first);
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::end() noexcept
{
	return iterator(m_size);
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_iterator DynamicVector<T, Alloc>::end() const noexcept
{
	return const_iterator(m_size);
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::reverse_iterator DynamicVector<T, Alloc>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_reverse_iterator DynamicVector<T, Alloc>::rbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::reverse_iterator DynamicVector<T, Alloc>::rend() noexcept
{
	return reverse_iterator(begin());
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_reverse_iterator DynamicVector<T, Alloc>::rend() const noexcept
{
	return const_reverse_iterator(begin());
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_iterator DynamicVector<T, Alloc>::cbegin() const noexcept
{
	return begin();
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_iterator DynamicVector<T, Alloc>::cend() const noexcept
{
	return end();
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_reverse_iterator DynamicVector<T, Alloc>::crbegin() const noexcept
{
	return rbegin();
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::const_reverse_iterator DynamicVector<T, Alloc>::crend() const noexcept
{
	return rend();
}

// Capacity
template<typename T, typename Alloc>
NODISCARD_CONSTEXPR bool DynamicVector<T, Alloc>::empty() const noexcept
{
	return cbegin() == cend();
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::size_type DynamicVector<T, Alloc>::size() const noexcept
{
	return ElementCount(cbegin(), cend());
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::size_type DynamicVector<T, Alloc>::max_size() const noexcept
{
	return std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), AllocType_traits::max_size(m_allocator));
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::reserve(const size_type newCapacity)
{
	if (newCapacity > capacity())
	{
		if (newCapacity > max_size())
		{
			LengthError();
			return;
		}
		ReallocateExactly(newCapacity);
	}
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::size_type DynamicVector<T, Alloc>::capacity() const noexcept
{
	return ElementCount(cbegin(), const_iterator(m_end));
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::shrink_to_fit()
{
	if (( size()/ (double)capacity()) < 0.75)
	{
		const size_type size = size();
		pointer newFirst = DoAllocate(size);
		CopyOrMove(begin(), newFirst, size);
		Tidy();
		m_first = newFirst;
		m_end = m_size = first + size;
	}
}

// Modifiers
template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::clear()
{
	DoDestroy(m_first, m_end);
	m_size = m_first;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::insert(const_iterator pos, const value_type& value)
{
	if (ValidateIterator(pos, true))
	{
		const size_type index = ElementCount(cbegin(), pos);
		InsertAt(index, static_cast<size_type>(1), value);
		return begin() + index;
	}
	return end();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::insert(const_iterator pos, value_type&& value)
{
	if (ValidateIterator(pos, true))
	{
		const size_type index = ElementCount(cbegin(), pos);
		InsertAt(index, std::move(value));
		return begin() + index;
	}
	return end();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::insert(const_iterator pos, const size_type count, const value_type& value)
{
	if (ValidateIterator(pos, true))
	{
		const size_type index = ElementCount(cbegin(), pos);
		InsertAt(index, count, value);
		return begin() + index;
	}
	return end();
}

template<typename T, typename Alloc>
template<typename InputIterator>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::insert(iterator pos, InputIterator first, InputIterator last)
{
	return insert(const_iterator(pos.m_ptr), first, last);
}

template<typename T, typename Alloc>
template<typename InputIterator>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::insert(const_iterator pos, InputIterator first, InputIterator last)
{
	if (ValidateIterator(pos, true))
	{
		const size_type index = ElementCount(cbegin(), pos);
		InsertAt(index, first, last);
		return begin() + index;
	}
	return end();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::insert(const_iterator pos, std::initializer_list<value_type> ilist)
{
	if (ValidateIterator(pos, true))
	{
		const size_type index = ElementCount(cbegin(), pos);
		InsertAt(index, ilist.begin(), ilist.end());
		return begin() + index;
	}
	return end();
}

template<typename T, typename Alloc>
template<typename... Args>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::emplace(const_iterator pos, Args&&... args)
{
	return insert(pos, std::move(value_type(std::forward<Args>(args)...)));
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::erase(iterator pos)
{
	return ValidateIterator(pos, false) ? RemoveAt(pos) : end();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::erase(const_iterator pos)
{
	return ValidateIterator(pos, false) ? RemoveAt(pos) : end();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::erase(iterator first, iterator last)
{
	return (ValidateIterator(first, false) && ValidateIterator(last, true)) ? RemoveAt(first, last) : end();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::erase(const_iterator first, const_iterator last)
{
	return (ValidateIterator(first, false) && ValidateIterator(last, true)) ? RemoveAt(first, last) : end();
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::push_back(const value_type& value)
{
	insert(end(), value);
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::push_back(value_type&& value)
{
	insert(end(), std::move(value));
}

template<typename T, typename Alloc>
template<typename... Args>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::reference DynamicVector<T, Alloc>::emplace_back(Args&&... args)
{
	return *emplace(end(), std::forward<Args>(args)...);
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::pop_back()
{
	--m_size;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::resize(const size_type newSize, const value_type value)
{
	if (newSize > capacity())
	{
		Reallocate(newSize, value);
	}
	else
	{
		DoDestroy(m_first, m_size);
		std::fill_n(begin(), newSize, value);
	}
	m_size = m_first + newSize;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::resize(const size_type newSize, const value_type& value)
{
	resize(newSize, value);
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::swap(this_type& other) noexcept
{
	std::swap(m_first, other.m_first);
	std::swap(m_size, other.m_size);
	std::swap(m_end, other.m_end);
	std::swap(m_allocator, other.m_allocator);
}

// Protected Members
template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::InsertAt(const size_type pos, value_type&& value)
{
	const size_type newSize = size() + 1;
	if (newSize >= capacity())
	{
		Reallocate(newSize, pos, 1);
	}
	else
	{
		CopyOrMove(begin(), end(), begin(), pos, 1);
	}
	DoConstruct((m_first + pos), std::move(value));
	m_size = m_first + newSize;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::InsertAt(const size_type pos, const size_type count, const value_type &value)
{
	const size_type newSize = size() + count;
	if (newSize >= capacity())
	{
		Reallocate(newSize, pos, count);
	}
	else
	{
		CopyOrMove(begin(), end(), begin(), pos, count);
	}
	for (size_type i = 0; i < count; ++i)
	{
		DoConstruct((m_first + i + pos), value);
	}
	m_size = m_first + newSize;
}

template<typename T, typename Alloc>
template<typename InputIterator>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::InsertAt(const size_type pos, InputIterator first, InputIterator last)
{
	const size_type count = ElementCount(first, last);
	const size_type newSize = size() + count;
	if (newSize >= capacity())
	{
		Reallocate(newSize, pos, count);
		for (size_type i = 0; first != last; ++i, ++first)
		{
			DoConstruct((m_first + i + pos), *first);
		}
	}
	else
	{
		CopyOrMove(begin(), begin(), pos, 0);
		for (size_type i = pos; first != last; ++i, ++first)
		{
			DoConstruct((m_first + i), *first);
		}
	}
	
	m_size = m_first + newSize;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::RemoveAt(const_iterator pos)
{
	// Return value
	//Iterator following the last removed element.
	//If pos refers to the last element, then the end() iterator is returned.
	//If last == end() prior to removal, then the updated end() iterator is returned.
	//If[first, last) is an empty range, then last is returned.
	iterator ret = end();
	if (empty() || pos == end())
	{
		ret = end();
	}
	else 
	{
		if (pos + 1 == end())
		{
			ret = end();
		}
		else
		{
			DoDestroy(pos);
			CopyOrMove(pos + 1, end(),  pos, size(), 0);
			ret = pos + 1;
		}
		--m_size;
	}
	return ret;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR typename DynamicVector<T, Alloc>::iterator DynamicVector<T, Alloc>::RemoveAt(const_iterator first, const_iterator last)
{
	iterator ret = end();
	
	if (last == end())
	{
		if (first == begin())
		{
			clear();
		}
		else
		{
			m_Last = first;
		}
		ret = end();
	}
	else if (first == begin())
	{
		const size_type removeCount = ElementCount(first, last);
		const size_type pos = ElementCount(cbegin(), first);
		DoDestroy(first, last);
		CopyOrMove(last, end(), begin() + pos, 0);
		ret = begin() + pos;
		m_size -= count;
	}
	else
	{
		const size_type removeCount = ElementCount(first, last);
		const size_type pos = ElementCount(cbegin(), first);
		DoDestroy(first, last);
		CopyOrMove(last, end(), begin() + pos, size(), 0);
		ret = begin() + pos;
		m_size -= count;
	}
	return ret;
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::pointer DynamicVector<T, Alloc>::DoAllocate(const size_type newSize)
{
	return AllocType_traits::allocate(m_allocator, newSize);
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR void DynamicVector<T, Alloc>::DoConstruct(pointer pos, const value_type& value)
{
	AllocType_traits::construct(m_allocator, ns_Util::Unfancy(pos), value);
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::DoConstruct(pointer first, size_type count, const value_type& value)
{
	while (count--)
	{
		DoConstruct(first + count, value);
	}
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::DoDestroy(pointer startMarker, pointer endMarker)
{
	ns_Util::Destroy_range(startMarker, endMarker, m_allocator);
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::DoDestroy(pointer pos)
{
	AllocType_traits::destroy(m_allocator, ns_Util::Unfancy(pos));
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::DoFree(pointer startMarker, pointer endMarker)
{
	AllocType_traits::deallocate(m_allocator, startMarker, ElementCount(endMarker, startMarker));
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::size_type DynamicVector<T, Alloc>::CalculateNewCapacity(const size_type newSize)
{
	const size_type oldcapacity = capacity();

	if (oldcapacity > kMaxSize - oldcapacity / 2)
	{
		return kMaxSize; // geometric growth would overflow
	}
	const size_type geometric = oldcapacity + oldcapacity / 2;

	if (geometric < newSize)
	{
		return newSize;
	}
	return geometric; // geometric growth is sufficient
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::Reallocate(const size_type newSize, const value_type& value)
{
	if (newSize < capacity())
	{
		DoDestroy(m_first, m_size);
	}
	else
	{
		Tidy();
		const size_type calculatedSize = CalculateNewCapacity(newSize);
		m_first = DoAllocate(calculatedSize);
		m_end = m_first + calculatedSize;
	}
	DoConstruct(m_first, newSize, value);
	m_size = m_first + newSize;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::Reallocate(const size_type newSize)
{
	if (newSize < capacity())
	{
		DoDestroy(m_first + newSize, m_size);
		m_size = m_first + newSize;
		return;
	}
	const size_type calculatedSize = CalculateNewCapacity(newSize);
	pointer newFirst = DoAllocate(calculatedSize);
	CopyOrMove(begin(), end(), newFirst, size(), 0);
	Tidy();
	m_first = newFirst;
	m_size = m_first + newSize;
	m_end = newFirst + calculatedSize;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::Reallocate(const size_type newSize, const size_type leaveEmptyPos, const size_type leaveEmptyCount)
{
	if (leaveEmptyPos == size())
	{
		Reallocate(newSize);
		return;
	}
	pointer newFirst{};
	pointer newEnd{};
	if (newSize < capacity())
	{
		DoDestroy(m_first + newSize, m_size);
		newFirst = m_first;
		newEnd = m_end;
	}
	else
	{
		const size_type calculatedSize = CalculateNewCapacity(newSize);
		newFirst = DoAllocate(calculatedSize);
		newEnd = newFirst + calculatedSize;
	}
	CopyOrMove(begin(), end(), newFirst, leaveEmptyPos, leaveEmptyCount);
	m_first = newFirst;
	m_size = m_first + newSize;
	m_end = newEnd;
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::ReallocateExactly(const size_type newSize)
{
	if (newSize < capacity())
	{
		DoDestroy(m_first + newSize, m_size);
		m_size = m_first + newSize;
	}
	else
	{
		pointer newFirst = DoAllocate(newSize);
		CopyOrMove(begin(), end(), newFirst, size(), 0);
		m_first = newFirst;
		m_end = m_last = newFirst + newSize;
	}
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::CopyOrMove(iterator Infirst, iterator Inlast, pointer outFirst, const size_type leaveEmptyPos, const size_type leaveEmptyCount)
{
	CopyOrMove(Infirst, Inlast, iterator(outFirst), leaveEmptyPos, leaveEmptyCount);
}

template<typename T, typename Alloc>
INLINE_OR_CONSTEXPR void DynamicVector<T, Alloc>::CopyOrMove(iterator Infirst, iterator Inlast, iterator outFirst, const size_type leaveEmptyPos, const size_type leaveEmptyCount)
{
	if constexpr (std::is_move_assignable_v<value_type>)
	{
		std::move(Infirst, Infirst + leaveEmptyPos, outFirst);
		std::move(Infirst + leaveEmptyPos, Inlast, outFirst + leaveEmptyPos + leaveEmptyCount);
	}
	else
	{
		std::copy_n(Infirst, leaveEmptyPos, outFirst);
		std::copy_n(Infirst + leaveEmptyPos, ElementCount(Infirst + leaveEmptyPos, Inlast), (outFirst + (leaveEmptyPos + leaveEmptyCount)));
	}
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR bool DynamicVector<T, Alloc>::ValidateIterator(const_iterator it, bool includeEndIterator) const
{
	if (it >= begin() && it < end())
	{
		return true;
	}
	else if (includeEndIterator && it == end())
	{
		return true;
	}
	return false;
}

template<typename T, typename Alloc>
template<typename InputIterator>
NODISCARD_CONSTEXPR typename DynamicVector<T, Alloc>::size_type DynamicVector<T, Alloc>::ElementCount(InputIterator first, InputIterator last) const
{
	return static_cast<size_type>(std::distance(first, last));
}

template<typename T, typename Alloc>
NODISCARD_CONSTEXPR void DynamicVector<T, Alloc>::Tidy() noexcept	// free all storage
{
	DoDestroy(m_first, m_end);
	DoFree(m_first, m_end);
	m_end = m_size = m_first = nullptr;
}

template<typename T, typename Alloc>
NO_RETURN void DynamicVector<T, Alloc>::LengthError()
{
	throw std::length_error("vector too long");
}

template<typename T, typename Alloc>
NO_RETURN void DynamicVector<T, Alloc>::RangeError()
{
	throw std::out_of_range("invalid vector subscript");
}



void test_DV_1()
{
	const char* testName = "Dynamic Vector.";
	ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n\n");

	DynamicVector<int> vec(10);
	
	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i] = (i + 1) * 10;
	}
	ns_Util::printVector(vec);

	ns_Util::Logger::LOG_MSG("Front : ", vec.front(), '\n');
	ns_Util::Logger::LOG_MSG("Back  : ", vec.back(), '\n');
	ns_Util::Logger::LOG_MSG("At[", 5, "] : ", vec.at(5), '\n');

	int temp = 1;
	vec.push_back(temp);
	ns_Util::printVector(vec);
	temp = 2;
	vec.push_back(temp);
	ns_Util::printVector(vec);

	temp = *(vec.begin());
	vec.emplace_back(temp);
	ns_Util::printVector(vec);

	temp = *(vec.begin() + 1);
	vec.emplace_back(temp);
	ns_Util::printVector(vec);

	temp = *(vec.begin() + 2);
	vec.emplace_back(temp);
	ns_Util::printVector(vec);

	temp = *(vec.begin() + 3);
	vec.emplace_back(temp);
	ns_Util::printVector(vec);

	temp = *(vec.begin() + 4);
	vec.emplace_back(temp);
	ns_Util::printVector(vec);

	vec.pop_back();

	ns_Util::Logger::LOG_MSG("\n\n");
}

void test_DV_2()
{
	const char* testName = "Dynamic Vector.";
	ns_Util::Logger::LOG_MSG("Executing Test 2 : ", testName, "\n\n");

	ns_Util::TestClass<int>::resetCounter();
	DynamicVector<ns_Util::TestClass<int>> vec;
	vec.emplace_back(10, nullptr);
	vec.emplace_back(20, nullptr);
	vec.emplace_back(30, nullptr);
	vec.emplace_back(40, nullptr);
	vec.emplace_back(50, nullptr);

	ns_Util::printVector(vec.rbegin(), vec.rend());
	vec.clear();
	ns_Util::Logger::LOG_MSG("Counter = ", ns_Util::TestClass<int>::getCounter(), '\n');

	ns_Util::Logger::LOG_MSG("\n\n");
}

void test_DV_3()
{
	const char* testName = "Dynamic Vector.";
	ns_Util::Logger::LOG_MSG("Executing Test 3 : ", testName, "\n\n");

	std::vector<ns_Util::TestClass<int>> stl_vec;
	stl_vec.emplace(stl_vec.end(), 10, nullptr);

	DynamicVector<ns_Util::TestClass<int>> dynamic_vec;
	dynamic_vec.emplace(dynamic_vec.end(), 10, nullptr);
	
	ns_Util::Logger::LOG_MSG("\n\n");
}

void test_DynamicVector()
{
	test_DV_1();
	test_DV_2();
	test_DV_3();
	ns_Util::Logger::LOG_MSG("#####################################\n");
}

}	// namespace nsCpp_DS
#endif	// #ifndef __DYNAMIC_VECTOR_H__