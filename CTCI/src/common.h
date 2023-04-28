#pragma once

#include <iostream>
#include <vector>
#include <string>

template<typename vectorT>
inline void PrintArray(const vectorT &vec, const std::string& str)
{
	std::cout << str;
	for (auto x : vec)
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;
}