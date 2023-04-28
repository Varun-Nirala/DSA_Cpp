#pragma once

/*
	Bisect Squares :	Given two squares on a 2D plane, find a line that would cut these two squares in half.
						Assume that the top andbottom sides of the square run parallel to the x-axis.
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "ds_ponitAndLine.h"

using namespace std;

class Square
{
	double		left;
	double		right;
	double		top;
	double		bottom;

	double		size;
public:
	Square(double l, double r, double t, double b)
		: left(l)
		, right(r)
		, top(t)
		, bottom(b)
	{
		size = abs(right - left);
	}

	Point middle()
	{
		return Point((left + right) / 2.0, (top + bottom) / 2.0);
	}

	/*	Return the point where the lin segement onnecting mid1 and mid2 intercepts the edge of square
	*	1. That is, draaw a line from the mid2 to mid1, and continue it until the edge of the square.
	*/
	Point extend(Point mid1, Point mid2, double inSize)
	{
		/* Find what direction the line mid2 -> mid1 goes */
		double xDir = mid1.x < mid2.x ? -1 : 1;
		double yDir = mid1.y < mid2.y ? -1 : 1;

		/*	If mid1 and mid2 have the same x value, then the slope calculation will throw a divide bye 0 exception.
		*	So, we compute this specially.
		*/
		if (mid1.x == mid2.x)
		{
			return Point(mid1.x, mid1.y + yDir * inSize / 2.0);
		}

		double slope = (mid1.y - mid2.y) / (mid1.x - mid2.x);	// mid2 is start and mid1 is end
		double x1 = 0;
		double y1 = 0;

		/*	Calculate slope.
		*	Note:
		*		if the slope is "steep" (>1) then the end of the line segement will hit size / 2 units away from the
		*			middle on the Y-axis.
		*		if the slope is "shallow" (<1) then the end of the line segement will hit size / 2 units away from the
		*			middle on the X-axis.
		*/

		if (abs(slope) == 1)
		{
			x1 = mid1.x + xDir * inSize / 2.0;
			y1 = mid1.y + yDir * inSize / 2.0;
		}
		else if (abs(slope) < 1)    // Shallow
		{
			x1 = mid1.x + xDir * inSize / 2.0;
			y1 = slope * (x1 - mid1.x) + mid1.y;
		}
		else    // Steep
		{

			x1 = (y1 - mid1.y) / slope + mid1.x;
			y1 = mid1.y + yDir * inSize / 2.0;
		}
		return Point(x1, y1);
	}

	Line cut(Square other)
	{
		/* calculate where a line between each middle would collide with the edhe of the sqaure */
		Point p1 = extend(middle(), other.middle(), size);
		Point p2 = extend(middle(), other.middle(), -1 * size);
		Point p3 = extend(other.middle(), middle(), other.size);
		Point p4 = extend(other.middle(), middle(), -1 * other.size);

		/*	Of above points, find start and end of lines. Start is farthest left (with top most as a tie breaker)
		*	and end is farthest right (with right most as a tie breaker)
		*/
		Point start = p1;
		Point end = p1;
		vector<Point> points{ p2, p3, p4 };

		for (int i = 0; i < points.size(); ++i)
		{
			if (points[i].x < start.x || (points[i].x == start.x && points[i].y < start.y))
			{
				start = points[i];
			}
			else if (points[i].x > end.x || (points[i].x == end.x && points[i].y > end.y))
			{
				end = points[i];
			}
		}
		return Line(start, end);
	}
};

class Solution_16_13
{
public:
	Line bisectSquares(Square a, Square b)
	{
		return a.cut(b);
	}
};

void test_Ch_16_13()
{
	Square squareA(1, 4, 5, 8);
	Square squareB(2, 5, 6, 9);
	Solution_16_13 sol;

	Line line = sol.bisectSquares(squareA, squareB);

	cout << "Slope = " << line.slope << ", Y Intercept = " << line.yIntercept << endl;
	cout << "Start Point  = (" << line.pstart.x << ", " << line.pstart.y << endl;
	cout << "End   Point  = (" << line.pend.x << ", " << line.pend.y << endl;
}