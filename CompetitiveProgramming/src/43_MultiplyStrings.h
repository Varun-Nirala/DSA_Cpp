#ifndef __43_MULTIPLY_STRINGS_H__
#define __43_MULTIPLY_STRINGS_H__

#include <vector>
#include <iostream>
#include "helper.h"

namespace nsCP
{
class Solution43
{
public:
    void test()
    {
        printf("Test : Solution43   -> Multiply Strings : START\n");
        std::vector<Data> vec;
        vec.emplace_back(Data{"8", "9", "72"});
        vec.emplace_back(Data{ "123456789", "12345", "1524074060205" });
        vec.emplace_back(Data{ "123456789", "0", "0" });

        int failed = 0;
        for (size_t i = 0; i < vec.size(); ++i)
        {
            vec[i].print();
            std::string str = multiply(vec[i]._num1, vec[i]._num2);
            std::cout << "Got Output : " << str << '\n';
            if (str != vec[i]._mult)
            {
                failed++;
            }
        }
        print("String multiplication :", vec.size(), failed);
        printf("Test : Solution43   -> Multiply Strings : END\n\n");
    }
private:
    struct Data
    {
        std::string _num1;
        std::string _num2;
        std::string _mult;

        Data(std::string n1, std::string n2, std::string mul)
            :_num1(n1)
            , _num2(n2)
            , _mult(mul)
        {}

        void print()
        {
            std::cout << _num1 << " x " << _num2 << " = " << _mult << '\n';
        }
    };

    void add(std::string& ans, const std::string& temp)
    {
        if (ans.empty())
        {
            ans = temp;
            return;
        }

        int res = 0;
        int carry = 0;
        int i = 0;
        int j = 0;
        for (i = 0; i < ans.size() && j < temp.size(); i++, ++j)
        {
            res = as_int(ans[i]) + as_int(temp[i]) + carry;
            carry = res / 10;
            res = res % 10;
            ans[i] = as_char(res);
        }

        while (i < ans.size())
        {
            res = as_int(ans[i]) + carry;
            carry = res / 10;
            res = res % 10;
            ans[i] = as_char(res);
            i++;
        }

        while (j < temp.size())
        {
            res = as_int(temp[j]) + carry;
            carry = res / 10;
            res = res % 10;
            ans.push_back(as_char(res));
            j++;
        }

        if (carry)
        {
            ans.push_back(as_char(carry));
        }
    }
public:
    std::string multiply(std::string num1, std::string num2)
    {
        if (num1.size() == 1)
        {
            if (num1[0] == '0')
                return "0";

            if (num1[0] == '1')
                return num2;
        }

        if (num2.size() == 1)
        {
            if (num2[0] == '0')
                return "0";
            if (num2[0] == '1')
                return num1;
        }

        std::string& bigger = (num1.size() >= num2.size()) ? num1 : num2;
        std::string& smaller = (num1.size() < num2.size()) ? num1 : num2;

        std::string ans;
        std::string temp;
        int res = 0, carry = 0;
        int numOfZerosToAppend = 0;
        for (int i = static_cast<int>(smaller.size() - 1); i >= 0; --i)
        {
            for (int j = static_cast<int>(bigger.size() - 1); j >= 0; --j)
            {
                res = as_int(smaller[i]) * as_int(bigger[j]) + carry;
                carry = res / 10;
                res = res % 10;
                temp.push_back(as_char(res));
            }
            if (carry)
            {
                temp.push_back(as_char(carry));
                carry = 0;
            }
            add(ans, temp);
            temp.clear();
            temp.insert(0, ++numOfZerosToAppend, '0');
        }

        if (carry)
        {
            add(ans, std::string(1, as_char(carry)));
        }
        std::reverse(ans.begin(), ans.end());

        return ans;
    }
};
}
#endif //#ifndef __43_MULTIPLY_STRINGS_H__
