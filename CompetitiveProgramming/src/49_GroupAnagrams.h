#ifndef __49_GROUP_ANAGRAMS_H__
#define __49_GROUP_ANAGRAMS_H__

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "helper.h"

namespace nsCP
{
class Solution49
{
public:
    Solution49()
        :m_size(26)
    {
        m_pArr = new int[m_size];
    }

    void test()
    {
        printf("Test : Solution49   -> Group Anagrams : START\n");
        std::vector<std::string> input{ "eat", "tea", "tan", "ate", "nat", "bat" };
        std::vector<std::vector<std::string>> output = groupAnagrams(input);

        print(output, "groupAnagrams returned : ");
        printf("Test : Solution49   -> Group Anagrams : END\n\n");
    }

private:
    bool isAnagram(std::string& str1, std::string& str2)
    {
        if (str1.size() != str2.size())
            return false;

        std::memset(m_pArr, 0, m_size * sizeof(int));

        for (int i = 0; i < str1.size(); ++i)
        {
            m_pArr[str1[i] - 'a']++;
            m_pArr[str2[i] - 'a']--;
        }

        for (int i = 0; i < m_size; ++i)
        {
            if (m_pArr[i] != 0)
                return false;
        }
        return true;
    }

    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
    {
        std::vector<std::vector<std::string>> ans;

        std::vector<bool> visited(strs.size(), false);

        std::vector<std::string> vec;

        for (int i = 0; i < strs.size(); ++i)
        {
            if (visited[i])
                continue;

            visited[i] = true;
            vec.clear();

            vec.push_back(strs[i]);
            std::cout << "Finding anagrams for word : " << strs[i] << " : ";

            for (int j = i + 1; j < strs.size(); ++j)
            {
                if (!visited[j] && isAnagram(strs[i], strs[j]))
                {
                    visited[j] = true;
                    vec.push_back(strs[j]);
                    std::cout << strs[j] << " , ";
                }
            }
            ans.push_back(vec);
        }
        return ans;
    }
private:
    const int       m_size{};
    int             *m_pArr{};
};
}
#endif //#ifndef __49_GROUP_ANAGRAMS_H__
