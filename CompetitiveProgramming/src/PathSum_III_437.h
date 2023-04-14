#ifndef __PATH_SUM_III_437_H__
#define __PATH_SUM_III_437_H__

#include <vector>
#include <map>
#include <iostream>
#include <queue>

#include "helper.h"

namespace nsCP
{
#define null INT_MIN
class Solution437
{
public:
    void test()
    {
        printf("Test : Solution437 -> Path Sum III : START\n");
        std::vector<std::pair<std::vector<int>, int> > input;
        input.emplace_back(std::make_pair(std::vector<int>{ 5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1 }, 22));
        input.emplace_back(std::make_pair(std::vector<int>{ 10, 5, -3, 3, 2, null, 11, 3, -2, null, 1 }, 8));

        std::vector<int> output = { 3, 3 };

        for (size_t i = 0; i < input.size(); ++i)
        {
            TreeNode<int>* root = nsCP::createTree(input[i].first, null);
            int sum = pathSum(root, input[i].second);
            if (sum == output[i])
            {
                printf("Passed! Result : %d\n", sum);
            }
            else
            {
                printf("Failed! Expected : %d, Got = %d\n", output[i], sum);
            }
        }
        printf("Test : Solution437 -> Path Sum III : END\n\n");
    }
private:
    template<typename T>
    void recurse(TreeNode<T>* root, T currSum, T targetSum, std::map<T, T>& memo)
    {
        if (!root)
            return;

        T newSum = currSum + root->val;

        m_ans += memo[newSum - targetSum];

        memo[newSum]++;
        recurse(root->lc, newSum, targetSum, memo);
        recurse(root->rc, newSum, targetSum, memo);
        memo[newSum]--;
    }

    template<typename T>
    int pathSum(TreeNode<T>* root, T targetSum) {
        std::map<T, T> memo;
        memo[0] = 1;
        m_ans = 0;
        recurse(root, 0, targetSum, memo);
        return m_ans;
    }

private:
    int             m_ans{};
};
}
#endif //__PATH_SUM_III_437_H__


/*
* // find subarray with a given sum
void subArraySum(int arr[], int n, int sum)
{
	int currentWindowSum = 0;
	int start = 0;

	for (int i = 0; i < n; ++i)
	{
		currentWindowSum += arr[i];
		if (currentWindowSum == sum)
		{
			printf("Subarray found : start = %d, end = %d\n", start, i);
			return;
		}
		else if (currentWindowSum > sum)
		{
			while (start < i && currentWindowSum > sum)
				currentWindowSum -= arr[start++];
		}
	}
	printf("Not found\n");
}

void testSubArraySum()
{
    int arr[] = { 15, 2, 4, 8, 9, 5, 10, 23 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 23;
    subArraySum(arr, n, sum);
}

*/
