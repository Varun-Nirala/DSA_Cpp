#pragma once

#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

#include "helper.h"
#include "hash_map.h"

namespace HashMap
{
	/************************************************************/
	/* template<typename HashMap> class const_hash_map_iterator */
	/************************************************************/
	// Dereferencing or incrementing an iterator constructed with the default
	// ctor is undefined, so it doesn't matter what values we give here.
	template<typename HashMap>
	const_hash_map_iterator<HashMap>::const_hash_map_iterator()
		: mBucketIndex(0)
		, mListIterator(list_iterator_type())
		, mHashMap(NULL)
	{}

	template<typename HashMap>
	const_hash_map_iterator<HashMap>::const_hash_map_iterator(size_type bucket, list_iterator_type listIt, const HashMap *inHashMap)
		: mBucketIndex(bucket)
		, mListIterator(listIt)
		, mHashMap(inHashMap)
	{}

	// Return the actual element
	template<typename HashMap>
	const typename const_hash_map_iterator<HashMap>::value_type& const_hash_map_iterator<HashMap>::operator*() const
	{
		return *mListIterator;
	}

	// Return the iterator, so the compiler can apply -> to it to access
	// the actual desired field.
	template<typename HashMap>
	const typename const_hash_map_iterator<HashMap>::value_type* const_hash_map_iterator<HashMap>::operator->() const
	{
		return &(*mListIterator);
	}

	// Defer the details to the increment() helper
	template<typename HashMap>
	const_hash_map_iterator<HashMap>& const_hash_map_iterator<HashMap>::operator++()
	{
		increment();
		return *this;
	}

	// Defer the details to the increment() helper
	template<typename HashMap>
	const_hash_map_iterator<HashMap> const_hash_map_iterator<HashMap>::operator++(int)
	{
		const_hash_map_iterator<HashMap> oldThis = *this;
		increment();
		return oldThis;
	}

	// Defer the details to the decrement() helper
	template<typename HashMap>
	const_hash_map_iterator<HashMap>& const_hash_map_iterator<HashMap>::operator--()
	{
		decrement();
		return *this;
	}

	// Defer the details to the decrement() helper
	template<typename HashMap>
	const_hash_map_iterator<HashMap> const_hash_map_iterator<HashMap>::operator--(int)
	{
		const_hash_map_iterator<HashMap> oldThis = *this;
		decrement();
		return oldThis;
	}

	template<typename HashMap>
	bool const_hash_map_iterator<HashMap>::operator==(const const_hash_map_iterator &rhs) const
	{
		// All fields, including the hash_map to which iterators refer must be equal
		return ((mHashMap == rhs.mHashMap) && (mBucketIndex == rhs.mBucketIndex) && (mListIterator == rhs.mListIterator));
	}

	template<typename HashMap>
	bool const_hash_map_iterator<HashMap>::operator!=(const const_hash_map_iterator &rhs) const
	{
		return !(*this == rhs);
	}

	/*** PRIVATE METHODS ***/

	// Behavior is undefined if mListIterator already refers to the the past-the-end
	// element, or is otherwise invalid
	template<typename HashMap>
	void const_hash_map_iterator<HashMap>::increment()
	{
		// mListIterator is an iterator into a single bucket. Increment it.
		++mListIterator;

		// If we're at the end of the current bucket,
		// find the next bucket with elements
		auto &buckets = mHashMap->mBuckets;

		if (mListIterator == buckets[mBucketIndex].end())
		{
			for (size_type i = mBucketIndex + 1; i < buckets.size(); ++i)
			{
				if (!buckets[i].empty())
				{
					// We found a non-empty bucket.
					// Make mListIterator refer to the first element in it.
					mListIterator = buckets[i].begin();
					mBucketIndex = i;
					return;
				}
			}

			// No More non-empty buckets, Assign mListIterator to refer to the end
			// iterator of the last list
			mBucketIndex = buckets.size() - 1;
			mListIterator = buckets[mBucketIndex].end();
		}
	}

	template<typename HashMap>
	void const_hash_map_iterator<HashMap>::decrement()
	{
		// mListIterator is an iterator into a single bucket.
		// If it's at the beginning of the current bucket, don't decrement it.
		// Instead, try to find a non-empy bucket before the current one
		auto &buckets = mHashMap->mBuckets;
		if (mListIterator == buckets[mBucketIndex].begin())
		{
			for (size_type i = mBucketIndex - 1; i >= 0; --i)
			{
				if (!buckets[mBucketIndex].empty())
				{
					mListIterator = buckets[i].end();
					--mListIterator;
					mBucketIndex = i;
					return;
				}
			}

			// No more non-empty buckets. This is an invalid decrement.
			// Assign mListIterator to refer to the end iterator of the last list
			mBucketIndex = buckets.size() - 1;
			mListIterator = buckets[mBucketIndex].end();
		}
		else
		{
			// We're not at the beginning of the bucket, so just move down
			--mListIterator;
		}
	}
	/************************************************************/
	/* template<typename HashMap> class const_hash_map_iterator */
	/************************************************************/




	/******************************************************/
	/* template<typename HashMap> class hash_map_iterator */
	/******************************************************/
	template<typename HashMap>
	hash_map_iterator<HashMap>::hash_map_iterator()
		: const_hash_map_iterator<HashMap>()
	{
	}

	template<typename HashMap>
	hash_map_iterator<HashMap>::hash_map_iterator(size_type bucket, list_iterator_type listIt, HashMap *inHashMap)
		: const_hash_map_iterator<HashMap>(bucket, listIt, inHashMap)
	{
	}

	// Return the actual element
	template<typename HashMap>
	typename hash_map_iterator<HashMap>::value_type& hash_map_iterator<HashMap>::operator*()
	{
		return const_cast<value_type&>(*(this->mListIterator));
	}

	// Return the iterator, so the compiler can apply -> to it to access
	// the actual desired field
	template<typename HashMap>
	typename hash_map_iterator<HashMap>::value_type* hash_map_iterator<HashMap>::operator->()
	{
		return const_cast<value_type *>(&(*(this->mListIterator)));
	}

	// Defer the details to the incerement() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator++()
	{
		this->increment();
		return *this;
	}

	// Defer the details to the incerement() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator++(int)
	{
		const_hash_map_iterator<HashMap> oldThis = *this;
		this->increment();
		return oldThis;
	}

	// Defer the details to the decrement() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator--()
	{
		this->decrement();
		return *this;
	}

	// Defer the details to the decrement() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator--(int)
	{
		const_hash_map_iterator<HashMap> oldThis = *this;
		this->decrement();
		return oldThis;
	}

	/******************************************************/
	/* template<typename HashMap> class hash_map_iterator */
	/******************************************************/


	/******************************************************************************************************************/
	/* template<typename Key, typename T, typename Compare = equal_to<Key>, typename Hash = hash<Key>> class hash_map */
	/******************************************************************************************************************/
	template <typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>::~hash_map() noexcept
	{
		clear();
		mSize = 0;
	}

	// Constructor
	template <typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>::hash_map(
		const Compare &comp /*= Compare()*/,
		size_type numBuckets /*= DEFUALT_BUCKET_SIZE*/,
		const Hash &hash /*= Hash()*/)
		: mSize(0)
		, mComp(comp)
		, mHash(hash)
	{
		if (numBuckets == 0)
		{
			throw std::invalid_argument("Number of buckets must be positive");
		}
		mBuckets.resize(numBuckets);
	}

	// Make a call to insert() to actually insert the elements
	template<typename Key, typename T, typename Compare, typename Hash>
	template<typename InputIterator>
	hash_map<Key, T, Compare, Hash>::hash_map(
		InputIterator first,
		InputIterator last,
		const Compare &comp /*= Compare()*/,
		size_type numBuckets /*= DEFUALT_BUCKET_SIZE*/,
		const Hash &hash /*= Hash()*/)
		: mSize(0)
		, mComp(comp)
		, mHash(hash)
	{
		if (numBuckets == 0)
		{
			throw std::invalid_argument("Number of buckets must be positive");
		}
		mBuckets.resize(numBuckets);
		insert(first, last);
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash> ::hash_map(
		std::initializer_list<value_type> il,
		const Compare &comp /*= Compare()*/,
		size_type numBuckets /*= DEFUALT_BUCKET_SIZE*/,
		const Hash &hash /*= Hash()*/)
		: mSize(0)
		, mComp(comp)
		, mHash(hash)
	{
		if (numBuckets == 0)
		{
			throw std::invalid_argument("Number of buckets must be positive");
		}
		mBuckets.resize(numBuckets);
		insert(il.begin(), il.end());
	}

	// Copy Constructor
	template<typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>::hash_map(const hash_map_type &rhs)
	{
		CopyFrom(rhs);
	}

	// Move Constructor
	template<typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>::hash_map(hash_map_type &&rhs) noexcept
		: mSize(std::move(rhs.mSize))
		, mComp(std::move(rhs.mComp))
		, mHash(std::move(rhs.mHash))
		, mBuckets(std::move(rhs.mBuckets))
	{
	}

	// Copy Assignment Operator
	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::hash_map_type&
		hash_map<Key, T, Compare, Hash>::operator=(const hash_map_type &rhs)
	{
		if (this != &rhs)
		{
			clear();
			CopyFrom(rhs);
		}
		return *this;
	}

	// Move Assignment Operator
	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::hash_map_type &
		hash_map<Key, T, Compare, Hash>::operator=(hash_map_type &&rhs) noexcept
	{
		if (this != &rhs)
		{
			clear();
			mSize = std::move(rhs.mSize);
			mComp = std::move(rhs.mComp);
			mHash = std::move(rhs.mHash);
			mBuckets = std::move(rhs.mBuckets);
		}
		return *this;
	}

	// Initializer list assignment operator
	template<typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>& hash_map<Key, T, Compare, Hash>::operator=(std::initializer_list<value_type> il)
	{
		clear();
		insert(il.begin(), il.end());
		return *this;
	}

	// Iterators methods
	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::begin()
	{
		if (mSize == 0)
		{
			// Special case: there are no element, so return the end iterator
			return end();
		}

		// We Know there is at least one element. Find the first element.
		for (size_type i = 0; i < mBuckets.size(); ++i)
		{
			if (!mBuckets[i].empty())
			{
				return hash_map_iterator<hash_map_type>(i, mBuckets[i].begin(), this);
			}
		}
		// Should never reach here, but if we do, return the end iterator.
		return end();
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::end()
	{
		// The end iterator is the end iterator of the list of the last bucket.
		size_type bucket = mBuckets.size() - 1;
		return hash_map_iterator<hash_map_type>(bucket, mBuckets[bucket].end(), this);
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator
		hash_map<Key, T, Compare, Hash>::begin() const
	{
		return const_cast<hash_map_type*>(this)->begin();
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator
		hash_map<Key, T, Compare, Hash>::end() const
	{
		return const_cast<hash_map_type*>(this)->end();
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator
		hash_map<Key, T, Compare, Hash>::cbegin() const
	{
		return begin();
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator
		hash_map<Key, T, Compare, Hash>::cend() const
	{
		return end();
	}

	// Size methods
	template<typename Key, typename T, typename Compare, typename Hash>
	bool hash_map<Key, T, Compare, Hash>::empty() const
	{
		return mSize == 0;
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::size_type
		hash_map<Key, T, Compare, Hash>::size() const
	{
		return mSize;
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::size_type
		hash_map<Key, T, Compare, Hash>::max_size() const
	{
		// In the worst case, all the elements hash to the same list,
		// so the max_size is the max_size of a single list.
		// This code assumes that all the lists have the same max_size.
		return mBuckets[0].max_size();
	}


	// Element insert methods
	template <typename Key, typename T, typename Compare, typename Hash>
	T& hash_map<Key, T, Compare, Hash>::operator[] (const key_type& x)
	{
		// Attempt to insert a new key/value pair of x and a new value.
		// Regardless of whether the insert succeeds of fails, insert()
		// returns a pair of an iterator/bool. 
		// The iterator refers to a key/value pair, the second element of
		// which is the value we want to return
		return ((insert(std::make_pair(x, T()))).first)->second;
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	std::pair<typename hash_map<Key, T, Compare, Hash>::iterator, bool>
		hash_map<Key, T, Compare, Hash>::insert(const value_type &x)
	{
		size_type bucket;

		// Try to find the element
		typename ListType::iterator it = findElement(x.first, bucket);
		bool inserted = false;
		if (it == mBuckets[bucket].end())
		{
			// We didn't find the element, so insert a new one
			it = mBuckets[bucket].insert(mBuckets[bucket].end(), x);
			inserted = true;
			mSize++;
		}

		return std::make_pair(hash_map_iterator<hash_map_type>(bucket, it, this), inserted);
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::insert(iterator /*position*/, const value_type &x)
	{
		// Just ignore the position
		return insert(x);
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	template<typename InputIterator>
	void hash_map<Key, T, Compare, Hash>::insert(InputIterator first, InputIterator last)
	{
		// Copy each element in the range by using an insert_iterator adapter.
		// Give begin() as a dummy position --- insert ignores it anyway
		std::copy(first, last, std::insert_iterator<hash_map_type>(*this, begin()));
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::insert(std::initializer_list<value_type> il)
	{
		insert(il.begin(), il.end());
	}


	// Emplace methods
	template<typename Key, typename T, typename Compare, typename Hash>
	std::pair<typename hash_map<Key, T, Compare, Hash>::iterator, bool>
		hash_map<Key, T, Compare, Hash>::emplace(value_type &&x)
	{
		size_type bucket;

		// Try to find the element
		typename ListType::iterator it = findElement(x.first, bucket);
		bool inserted = false;
		if (it == mBuckets[bucket].end())
		{
			// We didn't find the element, so emplace a new one
			it = mBuckets[bucket].emplace(mBuckets[bucket].end(), x);
			inserted = true;
			mSize++;
		}

		return std::make_pair(hash_map_iterator<hash_map_type>(bucket, it, this), inserted);
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::emplace_hint(iterator /*hint*/, value_type &&x)
	{
		// Just ignore the hint
		return emplace(std::forward<value_type>(x)).first;
	}


	// Element delete methods
	// Returns the number of element removed
	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::size_type
		hash_map<Key, T, Compare, Hash>::erase(const key_type& k)
	{
		size_type bucket;
		// First, try to find the element
		typename ListType::iterator it = findElement(k, bucket);

		if (it != mBuckets[bucket].end())
		{
			mBuckets[bucket].erase(it);
			mSize--;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::erase(iterator position)
	{
		iterator next = position;
		++next;
		// Erase the element from its bucket
		mBuckets[position.mBucketIndex].erase(position.mListIterator);
		mSize--;
		return next;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::erase(iterator first, iterator last)
	{
		// Erase all elements in the range
		for (iterator next = first; next != last; ++next)
		{
			next = erase(next);
		}

		return last;
	}


	// Other modifying utilities
	template<typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::swap(hash_map_type& hashIn)
	{
		std::swap(*this, hashIn);
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::clear() noexcept
	{
		for (auto &bucket : mBuckets)
		{
			bucket.clear();
		}
		mSize = 0;
	}



	// Access methods for STL conformity
	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::key_compare 
		hash_map<Key, T, Compare, Hash>::key_comp() const
	{
		return mComp;
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::value_compare
		hash_map<Key, T, Compare, Hash>::value_comp() const
	{
		return value_compare(mComp);
	}



	// Lookup methods
	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::find(const key_type& k)
	{
		size_type bucket;

		// Use findElement() helper
		typename ListType::iterator it = findElement(k, bucket);
		if (it == mBuckets[bucket].end())
		{
			// Element not found -- return the end iterator
			return end();
		}
		// Element found -- convert the bucket/iterator to a hash_map_iterator
		return hash_map_iterator<hash_map_type>(bucket, it, this);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator
		hash_map<Key, T, Compare, Hash>::find(const key_type& k) const
	{
		size_type bucket;

		// Use findElement() helper
		typename ListType::iterator it = const_cast<hash_map_type *>(this)->findElement(k, bucket);
		if (it == mBuckets[bucket].end())
		{
			// Element not found -- return the end iterator
			return end();
		}
		// Element found -- convert the bucket/iterator to a const_hash_map_iterator
		return const_hash_map_iterator<hash_map_type>(bucket, it, this);
	}

	// as hash_map can't have duplicate key, it always return a pair of identical iterators
	template<typename Key, typename T, typename Compare, typename Hash>
	std::pair<typename hash_map<typename Key, typename T, typename Compare, typename Hash>::iterator,
			  typename hash_map<typename Key, typename T, typename Compare, typename Hash>::iterator>
		hash_map<Key, T, Compare, Hash>::equal_range(const key_type &x)
	{
		iterator it = find(x);
		return std::make_pair(it, it);
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	std::pair<typename hash_map<typename Key, typename T, typename Compare, typename Hash>::const_iterator,
		typename hash_map<typename Key, typename T, typename Compare, typename Hash>::const_iterator>
		hash_map<Key, T, Compare, Hash>::equal_range(const key_type &x) const
	{
		const_iterator it = find(x);
		return std::make_pair(it, it);
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::size_type
		hash_map<Key, T, Compare, Hash>::count(const key_type &x) const
	{
		// There are either 1 or 0 element matching key x.
		// If we can find a match, return 1, otherwise return 0.
		return find(x) == end() ? 0 : 1;
	}

	/*** PRIVATE METHODS ***/
	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::ListType::iterator
		hash_map<Key, T, Compare, Hash>::findElement(const key_type& k, size_t& bucket)
	{
		// Hash the key to get the bucket
		bucket = mHash(k) % mBuckets.size();

		// Look for the key to get the bucket
		for (auto it = mBuckets[bucket].begin(); it != mBuckets[bucket].end(); ++it)
		{
			if (mComp(it->first, k))
			{
				return it;
			}
		}
		return mBuckets[bucket].end();
	}

	template<typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::CopyFrom(const hash_map_type &rhs)
	{
		mComp = rhs.mComp;
		mHash = rhs.mHash;
		mBuckets.resize(rhs.mBuckets.size());

		for (auto& bucket : rhs.mBuckets) {
			for (auto& element : bucket) {
				insert(element);
			}
		}
	}
	/******************************************************************************************************************/
	/* template<typename Key, typename T, typename Compare = equal_to<Key>, typename Hash = hash<Key>> class hash_map */
	/******************************************************************************************************************/
}
