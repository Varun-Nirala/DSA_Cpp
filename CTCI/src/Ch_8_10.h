#pragma once

/*
	Paint fill :		Implement the "paint fill" function that one might see on many image editing programs. That is, given
					a screen (represented by a 2-D array of colors), a point, and a new color, fill in the surrounding area
					until the color changes from the original color.
*/


#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

enum Color { Black, White, Red, Yellow, Green };
class Solution
{
	bool paintFillUtil(vector<vector<Color>> &screen, int r, int c, Color toChnage, Color changeTo)
	{
		if (r < 0 || r >= screen.size() || c < 0 || c >= screen[0].size())
		{
			return false;
		}

		if (screen[r][c] == toChnage)
		{
			screen[r][c] = changeTo;
			paintFillUtil(screen, r - 1, c, toChnage, changeTo);
			paintFillUtil(screen, r + 1, c, toChnage, changeTo);
			paintFillUtil(screen, r, c - 1, toChnage, changeTo);
			paintFillUtil(screen, r, c + 1, toChnage, changeTo);
		}
		return true;
	}
public:
	bool paintFill(vector<vector<Color>> &screen, int r, int c, Color ncolor)
	{
		if (screen[r][c] == ncolor)
			return false;
		return paintFillUtil(screen, r, c, screen[r][c], ncolor);
	}
};

string getName(Color c)
{
	string s;
	switch (c)
	{
	case Black:
		s = "Black";
		break;
	case White:
		s = "White";
		break;
	case Red:
		s = "Red";
		break;
	case Yellow:
		s = "Yellow";
		break;
	case Green:
		s = "Green";
		break;
	}
	return s;
}

void printScreen(vector<vector<Color>> &screen)
{
	for (auto &vec : screen)
	{
		for (auto x : vec)
		{
			cout << getName(x) << ", ";
		}
		cout << endl;
	}
}

int main()
{
	Solution sol;

	vector<vector<Color>> screen{
		{ Green, Black, Black, Black, Black },
		{ Black, Black, Green, Black, Green },
		{ Black, Green, Green, Green, Black },
		{ Black, Green, Green, Green, Black },
		{ Black, Black, Black, Black, Green },
		{ Black, Black, Black, Black, Black },
	};

	cout << "Original screen \n";
	printScreen(screen);


	int r = 2;
	int c = 2;
	Color changeColor = Yellow;
	cout << "\n\nAfter modifing " << getName(screen[r][c]) << " -> " << getName(changeColor) << endl;

	sol.paintFill(screen, r, c, changeColor);
	printScreen(screen);

	return 0;
}
