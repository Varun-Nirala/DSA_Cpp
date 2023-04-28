#pragma once

/*
	Intersection :	Given two straight line segments (represnted as a start point and an end point). Compute the point of
					intersection if any.

					Approach :
						Equation of Line => y = mx + c;
						m = slope = gradient = tangent = (y2- y1) / (x2 - x1) 
						if m > 0 : Line going up from left to right
						if m < 0 : Line going down from left to right
						if m == 0 : Line is parallel to x

					How to find interception point;
						Consider two lines 
							y1 = ax + c;		Eq 1
							y2 = bx + d;		Eq 2

						For these two line to intercept at new point, at that point y should be same so we can solve for that
							ax + c = bx + d
							ax - bx = d - c
							x = (d - c) / (a - x)

							to find y substitue x in any of two equations Eq 1 or Eq 2
							We take Eq 1
							X = (d - c) / (a - x)
							Y = a * X + c
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#include "ds_ponitAndLine.h"

using namespace std;

class Solution_16_3
{
public:
	Point* intersection(Point &start1, Point &end1, Point &start2, Point &end2)
	{
		/* START Rearranging these so that, in order of x values: start is before end and point1 is before point 2.*/
		if (start1.x > end1.x)
		{
			swap(start1, end1);
		}

		if (start2.x > end2.x)
		{
			swap(start2, end2);
		}

		if (start1.x > start2.x)
		{
			swap(start1, start2);
			swap(end1, end2);
		}
		/* END Rearranging these so that, in order of x values: start is before end and point1 is before point 2.*/

		/* Now computes lines */
		Line line1(start1, end1);
		Line line2(start2, end2);

		/*Check if thsese are parallel line */
		if (line1.slope == line2.slope)
		{
			if (line1.yIntercept == line2.yIntercept
				&& isBetween(start1, start2, end1))
			{
				return new Point(start2);
			}
			return nullptr;
		}

		/* Get intersect coordinates */
		double x = (line2.yIntercept - line1.yIntercept) / (line1.slope - line2.slope);
		double y = x * line1.slope + line1.yIntercept;

		Point *intersectionPoint = new Point(x, y);

		if (isBetween(start1, *intersectionPoint, end1) && isBetween(start2, *intersectionPoint, end2))
		{
			return intersectionPoint;
		}
		delete intersectionPoint;
		return nullptr;
	}
};

void test_Ch_16_3()
{
	Solution_16_3 sol;

	Point start1(0, 0);
	Point end1(5, 5);
	Point start2(0, 1);
	Point end2(10, 4);

	Point *pPoint = sol.intersection(start1, end1, start2, end2);

	pPoint->print();
}
