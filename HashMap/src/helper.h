#pragma once
#include <string>

namespace HashMap
{
	template <typename T>
	class equal_to
	{
	public:
		bool operator() (const T& lhs, const T&rhs)
		{
			return lhs == rhs;
		}
	};


	// Calculate a hash by treating the key as a sequence
	// of bytes and summing the ascii values of the bytes
	template <typename T>
	class hash
	{
		public:
			size_t operator() (const T& key) const
			{
				size_t bytes = sizeof(key);
				size_t res = 0;

				for (size_t i = 0; i < bytes; ++i)
				{
					unsigned char b = *((unsigned char *)&key + i);
					res += b;
				}
				return res;
			}
	};

	// A hash specialization for strings
	template <>
	class hash<std::string>
	{
		public:
			size_t operator() (const std::string& key) const
			{
				size_t bytes = key.size();
				size_t res = 0;

				for (size_t i = 0; i < bytes; ++i)
				{
					res += (unsigned char)key[i];
				}
				return res;
			}
	};
}
