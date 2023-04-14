#ifndef __JUMP_GAME_55_H__
#define __JUMP_GAME_55_H__

#include <iostream>
#include <vector>

#include "helper.h"

namespace nsCP
{
class Solution55
{
public:
	void test()
	{
		printf("Test : Solution55   -> Jump Game : START\n");
		std::vector<std::vector<int> > input = {
			{2,3,1,1,4},
			{3,2,1,0,4}
		};

		std::vector<bool> output = { true, false };

		for (int i = 0; i < input.size(); ++i)
		{
			if (canJump(input[i]) == output[i])
			{
				std::cout << "Passed : " << std::boolalpha << output[i] << '\n';
			}
			else
			{
				for (int j = 0; j < input[i].size(); ++j)
				{
					std::cout << input[i][j] << ", ";
				}
				std::cout << "\tExpected: " << std::boolalpha << output[i] << ", Output = " << std::boolalpha << !output[i] << '\n';
			}
		}
		printf("Test : Solution55   -> Jump Game : END\n\n");
	}

private:
	bool canJump(std::vector<int>& nums)
	{
		memo.resize(nums.size());

		for (auto& x : memo)
		{
			x = U;
		}

		memo[nums.size() - 1] = G;

		for (int pos = static_cast<int>(nums.size() - 2); pos >= 0; --pos)
		{
			int max = std::min(pos + nums[pos], static_cast<int>(nums.size() - 1));
			for (int i = pos + 1; i <= max; ++i)
			{
				if (memo[i] == G)
				{
					memo[pos] = G;
					break;
				}
			}
		}

		return memo[0] == G;
	}

	std::vector<int> memo;
	const int		B = 0;
	const int		G = 1;
	const int		U = 2;
};
}
#endif //#ifndef __JUMP_GAME_55_H__
