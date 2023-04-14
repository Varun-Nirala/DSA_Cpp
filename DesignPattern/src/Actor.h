#pragma once

#include <utility>

template<typename T>
class Actor final
{
public:
	Actor(T x = {}, T y = {})
		: m_currPosition{ x, y }
		, m_newPosition(m_currPosition)
	{
	}

	void setPosition(T x, T y)
	{
		m_newPosition.first = x;
		m_newPosition.second = y;
	}

	void setPosition(std::pair<T, T> &p)
	{
		m_newPosition = p;
	}

	void move()
	{
		if (m_newPosition != m_currPosition)
		{
			std::cout << "Moving from ";
			print();
			m_currPosition = m_newPosition;
			std::cout << "  ->  ";
			print();
			std::cout << "\n";
		}
	}

	void jump()
	{
		std::cout << "Jumping\n";
	}

	void fire()
	{
		std::cout << "Firing\n";
	}

	void duck()
	{
		std::cout << "Ducking\n";
	}

	T getX() const { return m_currPosition.first; }
	T getY() const { return m_currPosition.second; }

	std::pair<T, T> getPosition() const { return m_currPosition; }

	void print() const
	{
		std::cout << "( " << m_currPosition.first << ", " << m_currPosition.second << " )";
	}

private:
	std::pair<T, T>		m_currPosition;
	std::pair<T, T>		m_newPosition;
};