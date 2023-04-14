#pragma once

#include <memory>

template<typename T>
class MySharedPtr
{
public:
	using dataType		= T;
	using dataPtr		= dataType *;
	using refType		= size_t;
	using refPtr		= refType *;

	~MySharedPtr();

	explicit MySharedPtr() = default;
	explicit MySharedPtr(const dataType& data);
	explicit MySharedPtr(dataPtr *ptr = nullptr);
	explicit MySharedPtr(const MySharedPtr &obj);
	explicit MySharedPtr(MySharedPtr &&obj) noexcept;

	MySharedPtr& operator=(const MySharedPtr& obj);
	MySharedPtr& operator=(MySharedPtr&& obj) noexcept;

	refType refCount() const;

	const dataPtr get() const;
	dataPtr get();

	dataType& operator*();
	const dataType& operator*() const;

	dataPtr operator->();
	const dataPtr operator->() const;

	private:
		void clear();

	private:
		dataPtr			m_dataPtr{};
		refPtr			m_refPtr{};
};

template<typename T>
MySharedPtr<T>::~MySharedPtr()
{
	clear();
}

template<typename T>
void MySharedPtr<T>::clear()
{
	*m_refPtr--;
	if (*m_refPtr == 0)
	{
		delete m_dataPtr;
		m_dataPtr = nullptr;

		delete m_refPtr;
		m_refPtr = nullptr;
	}
}

template<typename T>
MySharedPtr<T>::MySharedPtr(const dataType &data)
{
	m_refPtr = new refType{};
	*m_refPtr++;
	m_dataPtr = new dataType{ data };
}

template<typename T>
MySharedPtr<T>::MySharedPtr(dataPtr *ptr)
{
	m_refPtr = new refPtr{};
	if (ptr)
	{
		*m_refPtr++;
		m_dataPtr = ptr;
	}
}

template<typename T>
MySharedPtr<T>::MySharedPtr(const MySharedPtr<T>& obj)
{
	m_refPtr = new refType{};
	*m_refPtr = *(obj.m_refPtr);
	m_dataPtr = new dataType{ *(obj.m_dataPtr) };
}

template<typename T>
MySharedPtr<T>::MySharedPtr(MySharedPtr<T>&& obj) noexcept
{
	m_refPtr = obj.m_refPtr;
	m_dataPtr = obj.m_dataPtr;

	obj.m_dataPtr = obj.m_refPtr = nullptr;
}

template<typename T>
MySharedPtr<T>& MySharedPtr<T>::operator=(const MySharedPtr<T>& obj)
{
	if (&obj != this)
	{
		clear();
		m_refPtr = obj.m_refPtr;
		m_dataPtr = obj.m_dataPtr;
		*m_refPtr++;
	}
	return *this;
}

template<typename T>
MySharedPtr<T>& MySharedPtr<T>::operator=(MySharedPtr<T>&& obj) noexcept
{
	if (&obj != this)
	{
		m_refPtr = obj.m_refPtr;
		m_dataPtr = obj.m_dataPtr;
		obj.m_dataPtr = obj.m_refPtr = nullptr;
	}
	return *this;
}

template<typename T>
typename MySharedPtr<T>::refType MySharedPtr<T>::refCount() const
{
	return *m_refPtr;
}

template<typename T>
typename const MySharedPtr<T>::dataPtr MySharedPtr<T>::get() const
{
	return m_dataPtr;
}

template<typename T>
typename MySharedPtr<T>::dataPtr MySharedPtr<T>::get()
{
	return m_dataPtr;
}

template<typename T>
typename MySharedPtr<T>::dataType& MySharedPtr<T>::operator*()
{
	return *m_dataPtr;
}

template<typename T>
typename const MySharedPtr<T>::dataType& MySharedPtr<T>::operator*() const
{
	return *m_dataPtr;
}

template<typename T>
typename MySharedPtr<T>::dataPtr MySharedPtr<T>::operator->()
{
	return m_dataPtr;
}

template<typename T>
typename const MySharedPtr<T>::dataPtr MySharedPtr<T>::operator->() const
{
	return m_dataPtr;
}