#pragma once

/*
	Parens :		Implement an algorithm to print all valid (i.e properly opened closed) combination of n pairs
				of parentheses.
				Example : 
					input : 3
					ouput : ((())), (()()), ()(()), ()()()
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Solution
{
	string insertInside(string x, int i)
	{
		string left = x.substr(0, i + 1);
		string right = x.substr(i + 1);
		return (left + "()" + right);
	}
public:
	set<string> generateParens(int remaining)
	{
		set<string> ss;

		if (remaining == 0)
		{
			ss.insert("");
		}
		else
		{
			set<string> prevSet = generateParens(remaining - 1);
			for (auto &x : prevSet)
			{
				for (int i = 0; i < x.size(); ++i)
				{
					if (x[i] == '(')
					{
						string s = insertInside(x, i);
						ss.insert(s);
					}
				}
				ss.insert("()" + x);
			}
		}
		return ss;
	}

	vector<string> generateParensOptimized(int remaining)
	{
		vector<string> vec;
		string str(remaining * 2, ' ');
		addParens(vec, remaining, remaining, str, 0);
		return vec;
	}
private:
	void addParens(vector<string> &vec, int leftRemaining, int rightRemaining, string str, int count)
	{
		if (leftRemaining < 0 || rightRemaining < leftRemaining)
			return;	//Invalid state

		if (leftRemaining == 0 && rightRemaining == 0)
		{
			vec.push_back(str);
		}
		else
		{
			if (leftRemaining > 0)
			{
				str[count] = '(';
				addParens(vec, leftRemaining - 1, rightRemaining, str, count + 1);
			}

			if (rightRemaining > 0)
			{
				str[count] = ')';
				addParens(vec, leftRemaining, rightRemaining - 1, str, count + 1);
			}
		}
	}
};

int main()
{
	Solution sol;
	int n = 3;
	set<string> ss = sol.generateParens(n);

	cout << "For n = " << n << ", solution via unefficient algo \n";
	for (auto &x : ss)
	{
		cout << x << endl;
	}

	cout << "\nFor n = " << n << ", solution via efficient algo \n";
	vector<string> vec = sol.generateParensOptimized(n);
	for (auto &x : vec)
	{
		cout << x << endl;
	}
	return 0;
}

