#ifndef __51_N_QUEENS_H__
#define __51_N_QUEENS_H__

#include <iostream>
#include <vector>
#include <string>

#include "helper.h"

namespace nsCP
{
class Solution51
{
public:
	void test()
	{
        printf("Test : Solution51   -> N Queens : START\n");
        std::vector<int> vec{ 4, 5, 9 };

        for (size_t i = 0; i < vec.size(); ++i)
        {
            std::vector<std::vector<std::string>> ans = solveNQueens(5);
            print(ans, "N-Queens for n = " + std::to_string(vec[i]));
        }
        printf("Test : Solution51   -> N Queens : END\n\n");
	}

private:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
        m_ans.clear();
        if (n == 1)
        {
            m_ans = std::vector<std::vector<std::string>>{ {"Q"} };
            return m_ans;
        }

        std::vector<std::string> vec(n, std::string(n, '.'));
        solve(vec, 0);
        return m_ans;
    }

    void solve(std::vector<std::string>& vec, int row)
    {
        if (row == vec.size())
        {
            m_ans.push_back(vec);
            return;
        }

        for (int col = 0; col < vec.size(); ++col)
        {
            if (isValid(vec, row, col))
            {
                vec[row][col] = 'Q';
                solve(vec, row + 1);
                vec[row][col] = '.';
            }
        }
    }

    inline bool notInRow(std::vector<std::string>& vec, size_t row)
    {
        for (size_t i = 0; i < vec[row].size(); ++i)
        {
            if (vec[row][i] == 'Q')
                return false;
        }
        return true;
    }

    inline bool notInCol(std::vector<std::string>& vec, size_t col)
    {
        for (size_t i = 0; i < vec.size(); ++i)
        {
            if (vec[i][col] == 'Q')
                return false;
        }
        return true;
    }

    inline bool notInDiag(std::vector<std::string>& vec, size_t row, size_t col)
    {
        int r = 0, c = 0;
        // top left
        r = static_cast<int>(row - 1);
        c = static_cast<int>(col - 1);
        while (r >= 0 && c >= 0)
        {
            if (vec[r--][c--] == 'Q')
                return false;
        }
        // top right
        r = static_cast<int>(row - 1);
        c = static_cast<int>(col + 1);
        while (r >= 0 && c < vec[0].size())
        {
            if (vec[r--][c++] == 'Q')
                return false;
        }
        // bottom left
        r = static_cast<int>(row + 1);
        c = static_cast<int>(col - 1);
        while (r < vec.size() && c >= 0)
        {
            if (vec[r++][c--] == 'Q')
                return false;
        }
        // bottom right
        r = static_cast<int>(row + 1);
        c = static_cast<int>(col + 1);
        while (r < vec.size() && c < vec[0].size())
        {
            if (vec[r++][c++] == 'Q')
                return false;
        }

        return true;
    }

    inline bool isValid(std::vector<std::string>& vec, size_t row, size_t col)
    {
        return notInRow(vec, row) && notInCol(vec, col) && notInDiag(vec, row, col);
    }
private:
    std::vector<std::vector<std::string>>       m_ans;
};
}
#endif //#ifndef __51_N_QUEENS_H__
