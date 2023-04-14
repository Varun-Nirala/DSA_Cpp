#pragma once

#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

#include "helper.h"

namespace HashMap
{
	/************************************************************/
	/* template<typename HashMap> class const_hash_map_iterator */
	/************************************************************/
	template<typename HashMap>
	class const_hash_map_iterator : public std::iterator<std::bidirectional_iterator_tag, typename HashMap::value_type>
	{
	public:
		using value_type = typename HashMap::value_type;
		using list_iterator_type = typename HashMap::ListType::const_iterator;
		using size_type = typename HashMap::size_type;

		// Bidirectional iterators must supply default ctor
		const_hash_map_iterator();
		const_hash_map_iterator(size_type bucket, list_iterator_type listIt, const HashMap *inHashMap);

		const value_type& operator*() const;

		// Return type must be something to which -> can be applied.
		// Return a pointer to a pair<const Key, T>, to which the compiler will apply -> again
		const value_type* operator->() const;

		const_hash_map_iterator<HashMap>& operator++();
		const_hash_map_iterator<HashMap> operator++(int);

		const_hash_map_iterator<HashMap>& operator--();
		const_hash_map_iterator<HashMap> operator--(int);

		// Don't need to defie a copy constructor or operator= because,
		// the default behavior is what we want.

		// Don't need destructor because the default behavior 
		// (not deleting mHashMap) is what we want.

		// The following are ok as memeber function because we don't
		// support comparisions of different types to this one
		bool operator==(const const_hash_map_iterator<HashMap>& rhs) const;
		bool operator!=(const const_hash_map_iterator<HashMap>& rhs) const;

	protected:
		size_type			mBucketIndex;
		list_iterator_type	mListIterator;
		const HashMap		*mHashMap;

		// Helper methods for operator++ and operator--
		void increment();
		void decrement();
	};
	/************************************************************/
	/* template<typename HashMap> class const_hash_map_iterator */
	/************************************************************/




	/******************************************************/
	/* template<typename HashMap> class hash_map_iterator */
	/******************************************************/
	template<typename HashMap>
	class hash_map_iterator : public const_hash_map_iterator<HashMap>
	{
	public:
		using value_type = typename const_hash_map_iterator<HashMap>::value_type;
		using list_iterator_type = typename HashMap::ListType::iterator;
		using size_type = typename HashMap::size_type;

		// Bidirectional iterators must supply default ctor
		hash_map_iterator();
		hash_map_iterator(size_type bucket, list_iterator_type listIt, HashMap *inHashMap);

		value_type& operator*();

		// Return type must be something to which -> can be applied.
		// Return a pointer to a pair<const Key, T>, to which the compiler will apply -> again
		value_type* operator->();

		hash_map_iterator<HashMap>& operator++();
		hash_map_iterator<HashMap> operator++(int);
		hash_map_iterator<HashMap>& operator--();
		hash_map_iterator<HashMap> operator--(int);
	};
	/******************************************************/
	/* template<typename HashMap> class hash_map_iterator */
	/******************************************************/


	/******************************************************************************************************************/
	/* template<typename Key, typename T, typename Compare = equal_to<Key>, typename Hash = hash<Key>> class hash_map */
	/******************************************************************************************************************/
	template <
		typename Key,
		typename T,
		typename Compare = equal_to<Key>,
		typename Hash = hash<Key>
	>
		class hash_map
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using key_compare = Compare;
		using value_type = std::pair<const Key, T>;
		using reference = std::pair<const Key, T>&;
		using const_reference = const std::pair<const Key, T>&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using hash_map_type = hash_map<Key, T, Compare, Hash>;

		using iterator = hash_map_iterator<hash_map_type>;
		using const_iterator = const_hash_map_iterator<hash_map_type>;

		// Required class definition for the associative continers
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
		public:
			bool operator() (const value_type &lhs, const value_type &rhs) const
			{
				return comp(lhs.first, lhs.first);
			}

		protected:
			Compare comp;
			value_compare(Compare c)
				: comp(c)
			{}
		};

		// The iterator classses need access to all members of the hash_map.
		friend class hash_map_iterator<hash_map_type>;
		friend class const_hash_map_iterator<hash_map_type>;

		virtual ~hash_map() noexcept;

		// Throw invalid_argument if the number of buckets is illegal.
		explicit hash_map(const Compare& comp = Compare(), size_type numBuckets = DEFUALT_BUCKET_SIZE, const Hash& hash = Hash());

		// Throw invalid_argument if the number of buckets is illegal.
		template<typename InputIterator>
		hash_map(InputIterator first, InputIterator last, const Compare& comp = Compare(), size_type numBuckets = DEFUALT_BUCKET_SIZE, const Hash& hash = Hash());

		// Initializer list constructor
		// Throw invalid_argument if the number of buckets is illegal.
		explicit hash_map(std::initializer_list<value_type> il, const Compare& comp = Compare(), size_type numBuckets = DEFUALT_BUCKET_SIZE, const Hash& hash = Hash());

		// Copy constructor
		hash_map(const hash_map_type &rhs);

		// Move constructor
		hash_map(hash_map_type &&rhs) noexcept;

		// Copy Assignment operator
		hash_map_type& operator=(const hash_map_type &rhs);

		// Move Assignment operator
		hash_map_type& operator=(hash_map_type &&rhs) noexcept;

		// Initializer list assignment operator
		// Throw invalid_argument if the number of buckets is illegal.
		hash_map_type& operator=(std::initializer_list<value_type> il);


		// Overloaded operators
		// @TODO bool operator==(const hash_map_type &rhs);
		// @TODO bool operator!=(const hash_map_type &rhs);


		// Iterators methods
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		// Size methods
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		// Element insert methods
		// operator [] finds the element with key k or inserts an element
		// with that key if none exists yet. Returns a reference to the value
		// corresponding to that key
		T& operator[] (const key_type &x);
		std::pair<iterator, bool> insert(const value_type& x);
		iterator insert(iterator position, const value_type& x);
		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last);
		void insert(std::initializer_list<value_type> il);

		// Emplace methods
		std::pair<iterator, bool> emplace(value_type &&x);
		iterator emplace_hint(iterator hint, value_type &&x);

		// Element delete methods
		size_type erase(const key_type &k);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		// Other modifying utilities
		void swap(hash_map_type &hashIn);
		void clear() noexcept;

		// Access methods for STL conformity
		key_compare key_comp() const;
		value_compare value_comp() const;

		// Lookup methods
		iterator find(const key_type& x);
		const_iterator find(const key_type& x) const;
		std::pair<iterator, iterator> equal_range(const key_type &x);
		std::pair<const_iterator, const_iterator> equal_range(const key_type &x) const;
		size_type count(const key_type &x) const;

	private:
		using ListType = std::list<value_type>;
		typename ListType::iterator findElement(const key_type& k, size_t& bucket);
		void CopyFrom(const hash_map_type &rhs);

	private:
		static const size_t DEFUALT_BUCKET_SIZE = 101;

		std::vector<ListType>	mBuckets;
		size_type				mSize;
		Compare					mComp;
		Hash						mHash;
	};
	/******************************************************************************************************************/
	/* template<typename Key, typename T, typename Compare = equal_to<Key>, typename Hash = hash<Key>> class hash_map */
	/******************************************************************************************************************/
}

#include "hash_map.inl"