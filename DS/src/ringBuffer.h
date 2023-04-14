#pragma once

#include <iostream>
#include <array>
#include <optional>

template <size_t Capacity, typename DataTypeA, typename DataTypeB>
class RingBuffer
{
	static_assert(!std::is_pod_v<DataTypeA> || !std::is_pod_v<DataTypeB>);

	struct Data
	{
		bool		m_bTypeA{};
		DataTypeA	m_a{};
		DataTypeB	m_b{};
	};
public:
	size_t capacity() const { return m_buff.size(); }
	// number of elements in buffer
	size_t size() const { return m_numberOfElement; }

	bool isFull() const { return m_numberOfElement == m_buff.size(); }
	bool isEmpty() const { return m_numberOfElement == 0; }

	bool push(const DataTypeA& data)
	{
		if (isFull()) return false;

		m_end = (m_end + 1) % m_buff.size();

		m_buff[m_end].m_a = data;
		m_buff[m_end].m_bTypeA = true;
		m_numberOfElement++;
		return true;
	}

	bool push(const DataTypeB& data)
	{
		if (isFull()) return false;

		m_end = (m_end + 1) % m_buff.size();

		m_buff[m_end].m_b = data;
		m_buff[m_end].m_bTypeA = false;
		m_numberOfElement++;
		return true;
	}

	bool pop()
	{
		if (isEmpty()) return false;

		m_end--;
		if (m_end < 0)
		{
			m_end = m_buff.size() - 1;
		}
		m_numberOfElement--;
		return true;
	}

	template <typename T>
	std::optional<const T*> front()
	{
		static_assert(!std::is_same_v<T, DataTypeA> || !std::is_same_v<T, DataTypeB>);

		if constexpr (std::is_same_v<T, DataTypeA>)
		{
			if (m_buff[m_start].m_bTypeA == true)
			{
				return m_buff[m_start].m_a;
			}
			else
			{
				return std::nullopt;
			}
		}
		else if constexpr (std::is_same_v<T, DataTypeB>)
		{
			if (m_buff[m_start].m_bTypeA == false)
			{
				return m_buff[m_start].m_b;
			}
			else
			{
				return std::nullopt;
			}
		}

		return std::nullopt;
	}

private:
	std::array<Data, Capacity>		m_buff;
	size_t							m_numberOfElement{};
	int64_t							m_start{};
	int64_t							m_end{};
};

struct Point2D
{
	Point2D(int a = 0, int b = 0)
	{
		x = a;
		y = b;
		//std::cout << "Point 2D ctor.\n";
	}

	~Point2D()
	{
		//std::cout << "Point 2D dtor.\n";
	}
	int	x{};
	int y{};
};

struct Point3D
{
	Point3D(int a = 0, int b = 0, int c = 0)
	{
		x = a;
		y = b;
		z = c;
		//std::cout << "Point 3D ctor.\n";
	}

	~Point3D()
	{
		//std::cout << "Point 3D dtor.\n";
	}
	int	x{};
	int y{};
	int z{};
};

void testRingBuffer()
{
	RingBuffer<10, Point2D, Point3D> ringBuff;

	std::cout << "Is Empty : " << ringBuff.isEmpty() << std::endl;
	std::cout << "Is Full  : " << ringBuff.isFull() << std::endl;
	std::cout << "Capacity : " << ringBuff.capacity() << std::endl;
	std::cout << "Size     : " << ringBuff.size() << std::endl;

	ringBuff.push(Point2D(1, 2));
	ringBuff.push(Point3D(11, 22, 33));

	std::cout << "Is Empty : " << ringBuff.isEmpty() << std::endl;
	std::cout << "Is Full  : " << ringBuff.isFull() << std::endl;
	std::cout << "Capacity : " << ringBuff.capacity() << std::endl;
	std::cout << "Size     : " << ringBuff.size() << std::endl;

	std::optional<const Point2D*> p = ringBuff.front<const Point2D>();

	return 0;
}