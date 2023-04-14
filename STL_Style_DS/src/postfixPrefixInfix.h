#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stack>

bool isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '/' || ch == '*');
}

int evaluateVal(int left, int right, char operand)
{
	switch (operand)
	{
		case '+':
			return left + right;
			break;
		case '-':
			return left - right;
			break;
		case '/':
			return left / right;
			break;
		case '*':
			return left * right;
			break;
		default:
			break;
	}
}

//"231*+9-"
int evaluatePostfix(const std::string& postfix)
{
	std::stack<int> ss;

	for (int i = 0; i < postfix.size(); ++i)
	{
		char ch = postfix[i];

		if (isOperator(ch))
		{
			int right = ss.top();
			ss.pop();
			int left = ss.top();
			ss.pop();

			ss.push(evaluateVal(left, right, ch));
		}
		else
		{
			ss.push(ch - '0');
		}
	}
	return ss.top();
}

//"-+8/632"
int evaluatePrefix(const std::string& prefix)
{
	std::stack<int> ss;

	for (int i = prefix.size() - 1; i >=0 ; --i)
	{
		char ch = prefix[i];

		if (isOperator(ch))
		{
			int left = ss.top();
			ss.pop();
			int right = ss.top();
			ss.pop();

			ss.push(evaluateVal(left, right, ch));
		}
		else
		{
			ss.push(ch - '0');
		}
	}
	return ss.top();
}
