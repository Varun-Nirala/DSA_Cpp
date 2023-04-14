#ifndef __GRID_H__
#define __GRID_H__

#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <cassert>

namespace ns_Util {

#define gcBLANK 0

template<typename T>
class Grid
{
public:
	using sizeType = size_t;
	Grid() = delete;

	Grid(const Grid<T>& other) { copyFrom(other); }
	Grid(Grid<T>&&other);
	Grid<T>& operator=(const Grid<T> &other);
	Grid<T>& operator=(Grid<T> &&other);

	Grid(sizeType row, sizeType col, T defaultValue = gcBLANK) { init(row, col, defaultValue); }
	Grid(const std::initializer_list<std::initializer_list<T>> mat) { init(mat); }

	~Grid() { clear(); }

	inline bool resize(sizeType row, sizeType col, T defaultValue = gcBLANK)
	{
		clear();
		init(row, col, defaultValue);
	}

	inline sizeType rows() const { return m_rows; }
	inline sizeType cols() const { return m_cols; }

	inline T& at(sizeType row, sizeType col);
	inline const T& at(sizeType row, sizeType col) const;

	inline T* operator[](sizeType row);
	inline const T* operator[](sizeType row) const;
	
	inline Grid<T>* clone();

private:
	inline void init(sizeType row, sizeType col, T defaultValue);
	inline void init(const std::initializer_list<std::initializer_list<T>> &mat);
	inline void clear();

	void copyFrom(const Grid<T> &other);

	inline void allocate(T defaultValue = gcBLANK);
	inline void deAllocate();


private:
	T				**m_grid{};
	sizeType		m_cols{};
	sizeType		m_rows{};
};

template<typename T>
Grid<T>::Grid(Grid<T> &&other)
{
	clear();
	m_rows = std::exchange(other.m_rows, 0);
	m_cols = std::exchange(other.m_cols, 0);
	m_grid = std::exchange(other.m_grid, nullptr);
}

template<typename T>
Grid<T>& Grid<T>::operator=(const Grid<T>&other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Grid<T>& Grid<T>::operator=(Grid<T>&&other)
{
	if (this != &other)
	{
		clear();
		m_rows = std::exchange(other.m_rows, 0);
		m_cols = std::exchange(other.m_cols, 0);
		m_grid = std::exchange(other.m_grid, nullptr);
	}
	return *this;
}

template<typename T>
T& Grid<T>::at(sizeType row, sizeType col)
{
	assert(!(row >= m_rows));
	assert(!(col >= m_cols));
	return m_grid[row][col];
}

template<typename T>
const T& Grid<T>::at(sizeType row, sizeType col) const
{
	assert(!(row >= m_rows));
	assert(!(col >= m_cols));
	return m_grid[row][col];
}

template<typename T>
inline T* Grid<T>::operator[](sizeType row)
{
	return m_grid[row];
}

template<typename T>
inline const T* Grid<T>::operator[](sizeType row) const
{
	return m_grid[row];
}

template<typename T>
Grid<T>* Grid<T>::clone()
{
	return new Grid<T>(*this);
}

template<typename T>
void Grid<T>::init(sizeType row, sizeType col, T defaultValue)
{
	m_cols = col;
	m_rows = row;
	allocate(defaultValue);
}

template<typename T>
void Grid<T>::init(const std::initializer_list<std::initializer_list<T>>& mat)
{
	m_rows = mat.size();
	m_cols = mat.begin()->size();
	allocate();

	sizeType i = 0;
	sizeType j = 0;
	for (auto list : mat)
	{
		for (auto x : list)
		{
			m_grid[i][j++] = x;
		}
		i++;
		j = 0;
	}
}

template<typename T>
void Grid<T>::clear()
{
	deAllocate();
	m_cols = m_rows = 0;
}

template<typename T>
void Grid<T>::copyFrom(const Grid<T>& other)
{
	clear();
	m_rows = other.m_rows;
	m_cols = other.m_cols;
	allocate();

	for (sizeType i = 0; i < m_rows; ++i)
	{
		for (sizeType j = 0; j < m_cols; ++j)
		{
			m_grid[i][j] = other.m_grid[i][j];
		}
	}
}

template<typename T>
void Grid<T>::allocate(T defaultValue)
{
	size_t header = m_rows * sizeof(T*);
	size_t data = m_rows * m_cols * sizeof(T);

	m_grid = (T **)(new T[header + data]{ defaultValue });
	if (m_grid)
	{
		T* buf = (T*)(m_grid + m_rows);
		for (size_t i = 0; i < m_rows; ++i)
		{
			m_grid[i] = buf + i * m_cols;
		}
	}
}

template<typename T>
void Grid<T>::deAllocate()
{
	delete[] m_grid;
	m_grid = nullptr;
	m_cols = m_rows = 0;
}
}	//namespace ns_Util	
#endif //#define __GRID_H__